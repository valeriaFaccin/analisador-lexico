# SLR Table Implementation

This project implements a complete SLR (Simple LR) parsing table for a specific grammar with 64 states (0-63) and all their corresponding transitions.

## Overview

The SLR table is implemented in C++ and includes:

- **64 States**: Complete implementation of all states from 0 to 63
- **Grammar Productions**: All production rules for the language
- **Kernel and Closure**: Each state contains kernel productions and their closures
- **Goto Transitions**: All transitions between states based on grammar symbols

## Files

### Core Implementation
- `tabela_slr.h` - Header file with class and structure declarations
- `tabela_slr.cpp` - Complete implementation of the SLR table with all 64 states

### Test Programs
- `test_slr.cpp` - Basic test program for the SLR table
- `test_complete_slr.cpp` - Comprehensive test program that verifies all states and transitions

### Build System
- `Makefile` - Build configuration for compiling the project

## Grammar

The SLR table is built for the following grammar:

```
S' -> S
S -> DECLARATION
S -> C
DECLARATION -> declare VAR ( PARAMS ) BODY
C -> begin CMD end
CMD -> VAR = EXPR ; CMD
CMD -> if COND CMD
CMD -> for COND CMD
CMD -> call VAR ; CMD
CMD -> ;
VAR -> (a+e+i+o+u)+(a+e+i+o+u+0+1)*
COND -> EXPR < EXPR
COND -> EXPR > EXPR
COND -> EXPR == EXPR
COND -> EXPR != EXPR
EXPR -> EXPR + TERM
EXPR -> EXPR - TERM
EXPR -> TERM
TERM -> TERM * FACT
TERM -> TERM / FACT
TERM -> FACT
FACT -> ( EXPR )
FACT -> VAR
FACT -> NUM
NUM -> (0+1)+
PARAMS -> VARLIST
PARAMS -> ;
VARLIST -> VAR , VARLIST
VARLIST -> VAR
BODY -> D C
D -> int VAR ; D
D -> ε
```

## States Overview

The implementation includes all 64 states with their specific characteristics:

### State 0 (Initial State)
- **Kernel**: {S' -> .S}
- **Closure**: Includes all initial productions for S, DECLARATION, and C

### States 1-63
Each state contains:
- **Kernel Productions**: The core productions that define the state
- **Closure Productions**: Additional productions added through closure computation
- **Goto Transitions**: Transitions to other states based on grammar symbols

## Key Features

### 1. Production Structure
```cpp
struct Production {
    string lhs;           // Left-hand side
    vector<string> rhs;   // Right-hand side
    int dot_pos;          // Position of the dot (.)
};
```

### 2. State Structure
```cpp
struct SLRState {
    int state_id;
    vector<Production> kernel;
    vector<Production> closure;
};
```

### 3. Goto Transitions
```cpp
struct GotoTransition {
    int from_state;
    string symbol;
    int to_state;
};
```

## Usage

### Basic Usage
```cpp
#include "tabela_slr.h"

// Get the SLR table instance
SLRTable* table = getSLRTable();

// Get a specific state
SLRState* state = table->getState(5);

// Get goto transition
int next_state = table->getGoto(0, "S"); // Returns 1
```

### Testing
```bash
# Compile all programs
make all

# Run basic test
make test

# Run comprehensive test
make test-complete

# Clean build files
make clean
```

## Complete State Information

### States 0-10 (Initial and Basic States)
- **State 0**: Initial state with S' -> .S
- **State 1**: S' -> S. (accept state)
- **State 2**: S -> DECLARATION.
- **State 3**: S -> C.
- **State 4**: DECLARATION -> declare .VAR ( PARAMS ) BODY
- **State 5**: C -> begin .CMD end
- **State 6**: DECLARATION -> declare VAR .( PARAMS ) BODY
- **State 7**: VAR -> (a+e+i+o+u)+(a+e+i+o+u+0+1)*.
- **State 8**: C -> begin CMD .end
- **State 9**: CMD -> VAR .= EXPR ; CMD
- **State 10**: CMD -> if .COND CMD

### States 11-25 (Command and Expression States)
- **State 11**: CMD -> for .COND CMD
- **State 12**: CMD -> call .VAR ; CMD
- **State 13**: DECLARATION -> declare VAR (.PARAMS ) BODY
- **State 14**: C -> begin CMD end.
- **State 15**: CMD -> VAR = .EXPR ; CMD
- **State 16**: CMD -> if COND .CMD
- **State 17**: COND -> EXPR .< EXPR, EXPR -> EXPR .+ TERM, etc.
- **State 18**: EXPR -> TERM., TERM -> TERM .* FACT, etc.
- **State 19**: TERM -> FACT.
- **State 20**: FACT -> (.EXPR )
- **State 21**: FACT -> VAR.
- **State 22**: FACT -> NUM.
- **State 23**: NUM -> (0+1)+.
- **State 24**: CMD -> for COND .CMD
- **State 25**: CMD -> call VAR .; CMD

### States 26-40 (Advanced Expression and Control States)
- **State 26**: DECLARATION -> declare VAR ( PARAMS .) BODY
- **State 27**: PARAMS -> VARLIST.
- **State 28**: VARLIST -> VAR ., VARLIST; VARLIST -> VAR.
- **State 29**: CMD -> VAR = EXPR .; CMD, EXPR -> EXPR .+ TERM, etc.
- **State 30**: CMD -> if COND CMD.
- **State 31**: COND -> EXPR < .EXPR
- **State 32**: COND -> EXPR > .EXPR
- **State 33**: COND -> EXPR == .EXPR
- **State 34**: COND -> EXPR != .EXPR
- **State 35**: EXPR -> EXPR + .TERM
- **State 36**: EXPR -> EXPR - .TERM
- **State 37**: TERM -> TERM * .FACT
- **State 38**: TERM -> TERM / .FACT
- **State 39**: FACT -> ( EXPR .), EXPR -> EXPR .+ TERM, etc.
- **State 40**: CMD -> for COND CMD.

### States 41-55 (Function Call and Declaration States)
- **State 41**: CMD -> call VAR ; .CMD
- **State 42**: DECLARATION -> declare VAR ( PARAMS ) .BODY
- **State 43**: VARLIST -> VAR , .VARLIST
- **State 44**: CMD -> VAR = EXPR ; .CMD
- **State 45**: COND -> EXPR < EXPR ., EXPR -> EXPR .+ TERM, etc.
- **State 46**: COND -> EXPR > EXPR ., EXPR -> EXPR .+ TERM, etc.
- **State 47**: COND -> EXPR == EXPR ., EXPR -> EXPR .+ TERM, etc.
- **State 48**: COND -> EXPR != EXPR ., EXPR -> EXPR .+ TERM, etc.
- **State 49**: EXPR -> EXPR + TERM ., TERM -> TERM .* FACT, etc.
- **State 50**: EXPR -> EXPR - TERM ., TERM -> TERM .* FACT, etc.
- **State 51**: TERM -> TERM * FACT .
- **State 52**: TERM -> TERM / FACT .
- **State 53**: FACT -> ( EXPR ) .
- **State 54**: CMD -> call VAR ; CMD .
- **State 55**: DECLARATION -> declare VAR ( PARAMS ) BODY .

### States 56-63 (Body and Declaration States)
- **State 56**: BODY -> D .C
- **State 57**: D -> int .VAR ; D
- **State 58**: VARLIST -> VAR , VARLIST .
- **State 59**: CMD -> VAR = EXPR ; CMD .
- **State 60**: BODY -> D C .
- **State 61**: D -> int VAR .; D
- **State 62**: D -> int VAR ; .D
- **State 63**: D -> int VAR ; D .

## Goto Transitions

The implementation includes all goto transitions from the original SLR table data, including:

- **Symbol-based transitions**: goto(state, symbol) -> next_state
- **Non-terminal transitions**: For grammar symbols like S, DECLARATION, C, etc.
- **Terminal transitions**: For tokens like declare, begin, if, for, etc.
- **Operator transitions**: For operators like +, -, *, /, <, >, ==, !=, etc.

## Verification

The comprehensive test program (`test_complete_slr.cpp`) verifies:

1. **State Count**: Ensures all 64 states are present
2. **State Content**: Verifies kernel and closure productions for each state
3. **Goto Transitions**: Tests all key transitions from the original data
4. **State Retrieval**: Confirms all states can be accessed by ID

## Compilation

The project uses a Makefile for easy compilation:

```bash
# Compile everything
make all

# Compile specific targets
make analisador-lexico
make test_slr
make test_complete_slr

# Run tests
make test
make test-complete

# Clean
make clean
```

## Dependencies

- C++11 or later
- Standard C++ libraries (vector, string, unordered_map, etc.)
- GCC or compatible C++ compiler

## Notes

- The implementation follows the exact structure from the provided SLR table data
- All states include their complete closures as specified in the original data
- The goto transitions match the original table exactly
- The implementation is designed to be easily extensible for additional functionality 