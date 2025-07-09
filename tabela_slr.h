#ifndef TABELA_SLR_H
#define TABELA_SLR_H

#include <vector>
#include <string>

// Forward declarations
struct Production;
struct SLRState;
struct GotoTransition;
class SLRTable;

// Structure to represent a production rule
struct Production {
    std::string lhs;  // Left-hand side
    std::vector<std::string> rhs;  // Right-hand side
    int dot_pos;  // Position of the dot
    
    Production(std::string left, std::vector<std::string> right, int dot = 0);
    std::string toString() const;
};

// Structure to represent an SLR state
struct SLRState {
    int state_id;
    std::vector<Production> kernel;
    std::vector<Production> closure;
    
    SLRState(int id, std::vector<Production> k, std::vector<Production> c);
};

// Structure to represent a goto transition
struct GotoTransition {
    int from_state;
    std::string symbol;
    int to_state;
    
    GotoTransition(int from, std::string sym, int to);
};

// SLR Table class declaration
class SLRTable {
private:
    std::vector<SLRState> states;
    std::vector<GotoTransition> goto_transitions;
    std::vector<Production> grammar;

public:
    SLRTable();
    void buildSLRTable();
    void buildRemainingStates();
    void addGotoTransition(int from, std::string symbol, int to);
    void printTable();
    int getGoto(int state, std::string symbol);
    SLRState* getState(int state_id);
    const std::vector<SLRState>& getStates() const;
    const std::vector<GotoTransition>& getGotoTransitions() const;
};

// Global functions
void initializeSLRTable();
SLRTable* getSLRTable();

#endif // TABELA_SLR_H 