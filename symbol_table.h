#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

enum class SymbolType {
    VARIABLE,
    FUNCTION,
    PARAMETER,
    CONSTANT
};

enum class DataType {
    INT,
    VOID,
    UNKNOWN
};

struct Symbol {
    std::string name;
    SymbolType type;
    DataType dataType;
    int scope;
    int line;
    std::string value;
    std::vector<std::string> parameters; // For functions
    
    Symbol(const std::string& n, SymbolType t, DataType dt, int s, int l)
        : name(n), type(t), dataType(dt), scope(s), line(l) {}
};

class SymbolTable {
private:
    std::unordered_map<std::string, std::vector<std::shared_ptr<Symbol>>> symbols;
    std::vector<int> scopeStack;
    int currentScope;
    
public:
    SymbolTable() : currentScope(0) {
        scopeStack.push_back(0); // Global scope
    }
    
    // Scope management
    void enterScope();
    void exitScope();
    int getCurrentScope() const { return currentScope; }
    
    // Symbol management
    bool insertSymbol(const std::string& name, SymbolType type, DataType dataType, int line);
    std::shared_ptr<Symbol> lookupSymbol(const std::string& name);
    std::shared_ptr<Symbol> lookupSymbolInCurrentScope(const std::string& name);
    
    // Function management
    bool insertFunction(const std::string& name, DataType returnType, 
                       const std::vector<std::string>& params, int line);
    
    // Utility functions
    void printSymbolTable() const;
    bool isInGlobalScope() const { return currentScope == 0; }
    
    // Error checking
    bool symbolExists(const std::string& name) const;
    bool functionExists(const std::string& name) const;
};

#endif // SYMBOL_TABLE_H 