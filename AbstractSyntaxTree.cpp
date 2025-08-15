#include "AbstractSyntaxTree.h"
#include <stdio.h>
#include <iostream>

using namespace std;

template<typename T>
static inline T PopAs(stack<Node>& stack) {
    if (!holds_alternative<T>(stack.top())) throw bad_variant_access();
    
    T value = get<T>(stack.top());
    stack.pop();
    return value;
}

AbstractSyntaxTree::AbstractSyntaxTree() : temp(0) {

}

void AbstractSyntaxTree::MakeLeaf(Lex& lex){
    AST.push(Lex(lex));
}

void AbstractSyntaxTree::MakeNode(int state){
    string name;
    vector<string> cods;
    // 00 BODY -> D C           {}
    // 01 D -> int VAR ; D      {}    
    // 02 D -> ''               {}
    // 03 C -> begin CMD end    {}
    // 04 CMD -> VAR = EXPR ; CMD1 {CMD.name = VAR.digval; CMD.cods = EXPR.cods || genCode(CMD.name '=' EXPR.name) || CMD1.cods}
    // 05 CMD -> if COND CMD    {}
    // 06 CMD -> for COND CMD   {}
    // 07 CMD -> ''             {}
    // 08 COND -> EXPR < EXPR   {}
    // 09 COND -> EXPR > EXPR   {}
    // 10 COND -> EXPR == EXPR  {}
    // 11 COND -> EXPR != EXPR  {}
    // 12 EXPR -> EXPR1 + TERM  {EXPR.name = genTemp(); EXPR.cods = EXPR1.cods || TERM.cods || genCode(EXPR.nome '=' EXPR1.name '+' TERM.name)}
    // 13 EXPR -> EXPR1 - TERM  {EXPR.name = genTemp(); EXPR.cods = EXPR1.cods || TERM.cods || genCode(EXPR.nome '=' EXPR1.name '-' TERM.name)}
    // 14 EXPR -> TERM          {EXPR.name = TERM.name; EXPR.cods = TERM.cods}
    // 15 TERM -> TERM1 * FACT  {TERM.name = genTemp(); TERM.cods = TERM1.cods || FACT.cods || genCode(TERM.nome '=' TERM1.name '*' FACT.name)}
    // 16 TERM -> TERM1 / FACT  {TERM.name = genTemp(); TERM.cods = TERM1.cods || FACT.cods || genCode(TERM.nome '=' TERM1.name '/' FACT.name)}
    // 17 TERM -> FACT          {TERM.name = FACT.name; TERM.cods = FACT.cods}
    // 18 FACT -> ( EXPR )      {FACT.name = EXPR.name; FACT.cods = EXPR.cods}
    // 19 FACT -> VAR           {FACT.name = VAR.digval; FACT.cods = ""}
    // 20 FACT -> NUM           {FACT.name = VAR.digval; FACT.cods = ""}
    
    switch (state) {
        case 5:
        case 6:
        case 8:
        case 9:
        case 10: 
        case 11:
            // removing garbage (irrelevant token) from the stack
            // semantic actions not implemented yet
            AST.pop(); 
            break;
        case 1:     
            // same as above 
            AST.pop(); 
            AST.pop(); 
            AST.pop();
            break; 
        case 3: {  
            // removing garbage while preserving CMD
            AST.pop();  // end
            SemanticActions CMD = PopAs<SemanticActions>(AST);
            AST.pop(); // begin

            AST.push(CMD);
            break;
        }
        case 4: {
            // CMD1 can derive epsilon, but it might also be a valid expression.
            // Hence, the need for validation.
            bool cmdEplison = true;
            SemanticActions CMD1;
            if (holds_alternative<SemanticActions>(AST.top())){
                CMD1 = PopAs<SemanticActions>(AST);
                cmdEplison = false;
            }

            AST.pop(); // ;
            SemanticActions EXPR = PopAs<SemanticActions>(AST);
            AST.pop(); // =
            Lex var = PopAs<Lex>(AST);

            name = var.digVal;
            cods = EXPR.cods;
            cods.push_back(genCode(name, " = ", EXPR.name));
            if (!cmdEplison) cods.insert(cods.end(), CMD1.cods.begin(), CMD1.cods.end());

            SemanticActions action = {name, cods};
            AST.push(action);
            break;
        }
        case 12: {
            SemanticActions EXPR1 = PopAs<SemanticActions>(AST);
            AST.pop(); // '+'
            SemanticActions TERM = PopAs<SemanticActions>(AST);

            name = genTemp();

            if (EXPR1.cods[0] != ""){
                cods = EXPR1.cods;
                if (TERM.cods[0] != "") cods.insert(cods.end(), TERM.cods.begin(), TERM.cods.end());
            }

            cods.push_back(genCode(name, " = ", EXPR1.name, " + ", TERM.name));

            SemanticActions action = {name, cods};
            AST.push(action);
            break;
        }
        case 13: {
            SemanticActions EXPR1 = PopAs<SemanticActions>(AST);
            AST.pop(); // '-'
            SemanticActions TERM = PopAs<SemanticActions>(AST);

            name = genTemp();

            if(EXPR1.cods[0] != "") {
                cods = EXPR1.cods;
                if(TERM.cods[0] != "") cods.insert(cods.end(), TERM.cods.begin(), TERM.cods.end());
            }
            cods.push_back(genCode(name, " = ", EXPR1.name, " - ", TERM.name));

            SemanticActions action = {name, cods};
            AST.push(action);
            break;
        }
        case 15: {
            SemanticActions TERM1 = PopAs<SemanticActions>(AST);
            AST.pop(); // '*'
            SemanticActions FACT = PopAs<SemanticActions>(AST);

            name = genTemp();

            if(TERM1.cods[0] != "") {
                cods = TERM1.cods;
                if(FACT.cods[0] != "") cods.insert(cods.end(), FACT.cods.begin(), FACT.cods.end());
            }
            cods.push_back(genCode(name, " = ", TERM1.name, " * ", FACT.name));

            SemanticActions action = {name, cods};
            AST.push(action);
            break;
        }
        case 16: {
            SemanticActions TERM1 = PopAs<SemanticActions>(AST);
            AST.pop(); // '/'
            SemanticActions FACT = PopAs<SemanticActions>(AST);

            name = genTemp();

            if(TERM1.cods[0] != ""){
                cods = TERM1.cods;
                if(FACT.cods[0] != "") cods.insert(cods.end(), FACT.cods.begin(), FACT.cods.end());
            }

            cods.push_back(genCode(name, " = ", TERM1.name, " / ", FACT.name));

            SemanticActions action = {name, cods};
            AST.push(action);
            break;
        }
        case 14:
        case 17: {
            SemanticActions EorT = PopAs<SemanticActions>(AST);
            
            SemanticActions action = {EorT.name, EorT.cods};
            AST.push(action);
            break;
        }
        case 18: {
            AST.pop(); // )
            SemanticActions EXPR = PopAs<SemanticActions>(AST); // EXPR
            AST.pop(); // ( 

            SemanticActions action = {EXPR.name, EXPR.cods};
            AST.push(action);
            break;
        }
        case 19:
        case 20: {
            Lex l = PopAs<Lex>(AST);
            name = l.digVal;
            cods.push_back("");

            SemanticActions action = {name, cods};
            AST.push(action);
            break;
        }
        default:
            break;
    }
}

string AbstractSyntaxTree::genTemp() {
    return "$t" + to_string(++temp);
}

void AbstractSyntaxTree::printResult(){
    printf("\033[1mResult for Semantic Actions:\033[0m\n");
    SemanticActions sa;
    
    while (!AST.empty()){
        sa = PopAs<SemanticActions>(AST);
         for (int i = 0; i < sa.cods.size(); i++){
             cout << sa.cods[i] << endl;
        }
    }
}
// void AbstractSyntaxTree::printEstado() {
//     stack<Node> tempStack = AST;  // copia para não modificar a original
    
//     while (!tempStack.empty()) {
//         Node node = tempStack.top();
//         tempStack.pop();

//         visit([](auto&& arg) {
//             using T = decay_t<decltype(arg)>;
//             if constexpr (is_same_v<T, SemanticActions>) {
//                 cout << "SemanticActions: " << arg.name << "\n";
//                 cout << "Codes:\n";
//                 for (const auto& c : arg.cods) {
//                     cout << "  " << c << "\n";
//                 }
//             } else if constexpr (is_same_v<T, Lex>) {
//                 cout << "Lex: " << arg.digVal << "\n";
//             }
//         }, node);
        
//         cout << "-----------------\n";
//     }
// }