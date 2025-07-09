#include <iostream>
#include "tabela_slr.h"

using namespace std;

int main() {
    cout << "SLR Table Test Program" << endl;
    cout << "======================" << endl;
    
    // Get the SLR table instance
    SLRTable* table = getSLRTable();
    
    // Print the table structure
    cout << "\nSLR Table Structure:" << endl;
    cout << "Number of states: " << table->getStates().size() << endl;
    cout << "Number of goto transitions: " << table->getGotoTransitions().size() << endl;
    
    // Print first few states as example
    cout << "\nFirst 10 States:" << endl;
    for (int i = 0; i < min(10, (int)table->getStates().size()); i++) {
        const SLRState& state = table->getStates()[i];
        cout << "\nState " << state.state_id << ":" << endl;
        
        cout << "  Kernel: ";
        for (const auto& prod : state.kernel) {
            cout << "{" << prod.toString() << "} ";
        }
        cout << endl;
        
        cout << "  Closure: ";
        for (const auto& prod : state.closure) {
            cout << "{" << prod.toString() << "} ";
        }
        cout << endl;
    }
    
    // Test goto transitions
    cout << "\nGoto Transitions Examples:" << endl;
    cout << "goto(0, S) = " << table->getGoto(0, "S") << endl;
    cout << "goto(0, DECLARATION) = " << table->getGoto(0, "DECLARATION") << endl;
    cout << "goto(0, C) = " << table->getGoto(0, "C") << endl;
    cout << "goto(4, VAR) = " << table->getGoto(4, "VAR") << endl;
    cout << "goto(5, CMD) = " << table->getGoto(5, "CMD") << endl;
    
    // Test getting a specific state
    cout << "\nState 5 Details:" << endl;
    SLRState* state5 = table->getState(5);
    if (state5) {
        cout << "State ID: " << state5->state_id << endl;
        cout << "Kernel productions: " << state5->kernel.size() << endl;
        cout << "Closure productions: " << state5->closure.size() << endl;
        
        cout << "Kernel: ";
        for (const auto& prod : state5->kernel) {
            cout << "{" << prod.toString() << "} ";
        }
        cout << endl;
    }
    
    cout << "\nTest completed successfully!" << endl;
    return 0;
} 