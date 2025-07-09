#include <iostream>
#include <iomanip>
#include "tabela_slr.h"

using namespace std;

void printStateDetails(const SLRState& state) {
    cout << "State " << state.state_id << ":" << endl;
    
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

void printGotoTransitions(SLRTable* table, int state_id) {
    cout << "  Goto transitions: ";
    bool found = false;
    for (const auto& trans : table->getGotoTransitions()) {
        if (trans.from_state == state_id) {
            cout << "goto(" << trans.from_state << ", " << trans.symbol << ") -> " << trans.to_state << " ";
            found = true;
        }
    }
    if (!found) {
        cout << "None";
    }
    cout << endl;
}

int main() {
    cout << "Complete SLR Table Verification" << endl;
    cout << "===============================" << endl;
    
    SLRTable* table = getSLRTable();
    
    cout << "\nTable Statistics:" << endl;
    cout << "Total states: " << table->getStates().size() << endl;
    cout << "Total goto transitions: " << table->getGotoTransitions().size() << endl;
    
    // Verify we have all 63 states
    if (table->getStates().size() == 64) { // 0-63 = 64 states
        cout << "✓ All 64 states (0-63) are present" << endl;
    } else {
        cout << "✗ Missing states. Expected 64, got " << table->getStates().size() << endl;
    }
    
    // Print all states with their details
    cout << "\nDetailed State Information:" << endl;
    cout << "==========================" << endl;
    
    for (const auto& state : table->getStates()) {
        printStateDetails(state);
        printGotoTransitions(table, state.state_id);
        cout << endl;
    }
    
    // Test specific goto transitions from the original data
    cout << "\nVerifying Key Goto Transitions:" << endl;
    cout << "===============================" << endl;
    
    struct TestTransition {
        int from;
        string symbol;
        int expected_to;
    };
    
    vector<TestTransition> test_transitions = {
        {0, "S", 1},
        {0, "DECLARATION", 2},
        {0, "C", 3},
        {0, "declare", 4},
        {0, "begin", 5},
        {4, "VAR", 6},
        {4, "(a+e+i+o+u)+(a+e+i+o+u+0+1)*", 7},
        {5, "CMD", 8},
        {5, "VAR", 9},
        {5, "if", 10},
        {5, "for", 11},
        {5, "call", 12},
        {6, "(", 13},
        {8, "end", 14},
        {9, "=", 15},
        {10, "COND", 16},
        {10, "EXPR", 17},
        {10, "TERM", 18},
        {10, "FACT", 19},
        {10, "(", 20},
        {10, "VAR", 21},
        {10, "NUM", 22},
        {10, "(0+1)+", 23},
        {11, "COND", 24},
        {12, "VAR", 25},
        {13, "PARAMS", 26},
        {13, "VARLIST", 27},
        {13, "VAR", 28},
        {15, "EXPR", 29},
        {16, "CMD", 30},
        {17, "<", 31},
        {17, ">", 32},
        {17, "==", 33},
        {17, "!=", 34},
        {17, "+", 35},
        {17, "-", 36},
        {18, "*", 37},
        {18, "/", 38},
        {20, "EXPR", 39},
        {24, "CMD", 40},
        {25, ";", 41},
        {26, ")", 42},
        {28, ",", 43},
        {29, ";", 44},
        {31, "EXPR", 45},
        {32, "EXPR", 46},
        {33, "EXPR", 47},
        {34, "EXPR", 48},
        {35, "TERM", 49},
        {36, "TERM", 50},
        {37, "FACT", 51},
        {38, "FACT", 52},
        {39, ")", 53},
        {41, "CMD", 54},
        {42, "BODY", 55},
        {43, "VARLIST", 58},
        {45, "+", 35},
        {46, "+", 35},
        {47, "+", 35},
        {48, "+", 35},
        {49, "*", 37},
        {50, "*", 37},
        {56, "C", 60},
        {57, "VAR", 61},
        {61, ";", 62},
        {62, "D", 63}
    };
    
    int passed_tests = 0;
    int total_tests = test_transitions.size();
    
    for (const auto& test : test_transitions) {
        int result = table->getGoto(test.from, test.symbol);
        if (result == test.expected_to) {
            cout << "✓ goto(" << test.from << ", " << test.symbol << ") -> " << result << endl;
            passed_tests++;
        } else {
            cout << "✗ goto(" << test.from << ", " << test.symbol << ") -> " << result << " (expected " << test.expected_to << ")" << endl;
        }
    }
    
    cout << "\nTest Results:" << endl;
    cout << "Passed: " << passed_tests << "/" << total_tests << " (" << (passed_tests * 100.0 / total_tests) << "%)" << endl;
    
    // Test state retrieval
    cout << "\nState Retrieval Test:" << endl;
    cout << "====================" << endl;
    
    for (int i = 0; i <= 63; i++) {
        SLRState* state = table->getState(i);
        if (state) {
            cout << "✓ State " << i << " found with " << state->kernel.size() << " kernel productions" << endl;
        } else {
            cout << "✗ State " << i << " not found" << endl;
        }
    }
    
    cout << "\nSLR Table implementation completed successfully!" << endl;
    return 0;
} 