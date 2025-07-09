#include "symbol_table.h"
#include <iostream>
#include <algorithm>

void SymbolTable::enterScope() {
    currentScope++;
    scopeStack.push_back(currentScope);
}

void SymbolTable::exitScope() {
    if (scopeStack.size() > 1) {
        scopeStack.pop_back();
        currentScope = scopeStack.back();
    }
}

bool SymbolTable::insertSymbol(const std::string& name, SymbolType type, DataType dataType, int line) {
    // Check if symbol already exists in current scope
    if (symbolExists(name)) {
        auto existing = lookupSymbolInCurrentScope(name);
        if (existing) {
            return false; // Symbol already exists in current scope
        }
    }
    
    auto symbol = std::make_shared<Symbol>(name, type, dataType, currentScope, line);
    symbols[name].push_back(symbol);
    return true;
}

std::shared_ptr<Symbol> SymbolTable::lookupSymbol(const std::string& name) {
    auto it = symbols.find(name);
    if (it != symbols.end() && !it->second.empty()) {
        // Return the most recent symbol (closest scope)
        return it->second.back();
    }
    return nullptr;
}

std::shared_ptr<Symbol> SymbolTable::lookupSymbolInCurrentScope(const std::string& name) {
    auto it = symbols.find(name);
    if (it != symbols.end()) {
        for (auto it2 = it->second.rbegin(); it2 != it->second.rend(); ++it2) {
            if ((*it2)->scope == currentScope) {
                return *it2;
            }
        }
    }
    return nullptr;
}

bool SymbolTable::insertFunction(const std::string& name, DataType returnType, 
                                const std::vector<std::string>& params, int line) {
    // Check if function already exists
    if (functionExists(name)) {
        return false;
    }
    
    auto symbol = std::make_shared<Symbol>(name, SymbolType::FUNCTION, returnType, currentScope, line);
    symbol->parameters = params;
    symbols[name].push_back(symbol);
    return true;
}

void SymbolTable::printSymbolTable() const {
    std::cout << "\n=== SYMBOL TABLE ===" << std::endl;
    std::cout << "Current Scope: " << currentScope << std::endl;
    std::cout << "Scope Stack: ";
    for (int scope : scopeStack) {
        std::cout << scope << " ";
    }
    std::cout << std::endl;
    
    for (const auto& pair : symbols) {
        std::cout << "\nSymbol: " << pair.first << std::endl;
        for (const auto& symbol : pair.second) {
            std::cout << "  - Type: ";
            switch (symbol->type) {
                case SymbolType::VARIABLE: std::cout << "VARIABLE"; break;
                case SymbolType::FUNCTION: std::cout << "FUNCTION"; break;
                case SymbolType::PARAMETER: std::cout << "PARAMETER"; break;
                case SymbolType::CONSTANT: std::cout << "CONSTANT"; break;
            }
            std::cout << ", DataType: ";
            switch (symbol->dataType) {
                case DataType::INT: std::cout << "INT"; break;
                case DataType::VOID: std::cout << "VOID"; break;
                case DataType::UNKNOWN: std::cout << "UNKNOWN"; break;
            }
            std::cout << ", Scope: " << symbol->scope;
            std::cout << ", Line: " << symbol->line;
            if (!symbol->value.empty()) {
                std::cout << ", Value: " << symbol->value;
            }
            if (symbol->type == SymbolType::FUNCTION && !symbol->parameters.empty()) {
                std::cout << ", Parameters: ";
                for (size_t i = 0; i < symbol->parameters.size(); ++i) {
                    if (i > 0) std::cout << ", ";
                    std::cout << symbol->parameters[i];
                }
            }
            std::cout << std::endl;
        }
    }
    std::cout << "===================" << std::endl;
}

bool SymbolTable::symbolExists(const std::string& name) const {
    auto it = symbols.find(name);
    return it != symbols.end() && !it->second.empty();
}

bool SymbolTable::functionExists(const std::string& name) const {
    auto it = symbols.find(name);
    if (it != symbols.end()) {
        for (const auto& symbol : it->second) {
            if (symbol->type == SymbolType::FUNCTION) {
                return true;
            }
        }
    }
    return false;
} 