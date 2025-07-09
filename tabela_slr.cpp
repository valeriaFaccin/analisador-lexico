#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <set>
#include "tabela_slr.h"

using namespace std;

Production::Production(string left, vector<string> right, int dot) 
    : lhs(left), rhs(right), dot_pos(dot) {}

string Production::toString() const {
    string result = lhs + " -> ";
    for (size_t i = 0; i < rhs.size(); i++) {
        if (i == dot_pos) result += ". ";
        result += rhs[i];
        if (i < rhs.size() - 1) result += " ";
    }
    if (dot_pos == rhs.size()) result += " .";
    return result;
}

SLRState::SLRState(int id, vector<Production> k, vector<Production> c) 
    : state_id(id), kernel(k), closure(c) {}

GotoTransition::GotoTransition(int from, string sym, int to) 
    : from_state(from), symbol(sym), to_state(to) {}

class SLRTable {
private:
    vector<SLRState> states;
    vector<GotoTransition> goto_transitions;
    
    vector<Production> grammar = {
        Production("S'", {"S"}),
        Production("S", {"DECLARATION"}),
        Production("S", {"C"}),
        Production("DECLARATION", {"declare", "VAR", "(", "PARAMS", ")", "BODY"}),
        Production("C", {"begin", "CMD", "end"}),
        Production("CMD", {"VAR", "=", "EXPR", ";", "CMD"}),
        Production("CMD", {"if", "COND", "CMD"}),
        Production("CMD", {"for", "COND", "CMD"}),
        Production("CMD", {"call", "VAR", ";", "CMD"}),
        Production("CMD", {";"}),
        Production("VAR", {"(a+e+i+o+u)+(a+e+i+o+u+0+1)*"}),
        Production("COND", {"EXPR", "<", "EXPR"}),
        Production("COND", {"EXPR", ">", "EXPR"}),
        Production("COND", {"EXPR", "==", "EXPR"}),
        Production("COND", {"EXPR", "!=", "EXPR"}),
        Production("EXPR", {"EXPR", "+", "TERM"}),
        Production("EXPR", {"EXPR", "-", "TERM"}),
        Production("EXPR", {"TERM"}),
        Production("TERM", {"TERM", "*", "FACT"}),
        Production("TERM", {"TERM", "/", "FACT"}),
        Production("TERM", {"FACT"}),
        Production("FACT", {"(", "EXPR", ")"}),
        Production("FACT", {"VAR"}),
        Production("FACT", {"NUM"}),
        Production("NUM", {"(0+1)+"}),
        Production("PARAMS", {"VARLIST"}),
        Production("PARAMS", {";"}),
        Production("VARLIST", {"VAR", ",", "VARLIST"}),
        Production("VARLIST", {"VAR"}),
        Production("BODY", {"D", "C"}),
        Production("D", {"int", "VAR", ";", "D"}),
        Production("D", {})
    };

public:
    SLRTable() {
        buildSLRTable();
    }
    
    void buildSLRTable() {
        
        vector<Production> kernel0 = {Production("S'", {"S"}, 0)};
        vector<Production> closure0 = {
            Production("S'", {"S"}, 0),
            Production("S", {"DECLARATION"}, 0),
            Production("S", {"C"}, 0),
            Production("DECLARATION", {"declare", "VAR", "(", "PARAMS", ")", "BODY"}, 0),
            Production("C", {"begin", "CMD", "end"}, 0)
        };
        states.push_back(SLRState(0, kernel0, closure0));
        
        
        vector<Production> kernel1 = {Production("S'", {"S"}, 1)};
        vector<Production> closure1 = {Production("S'", {"S"}, 1)};
        states.push_back(SLRState(1, kernel1, closure1));
        
        
        vector<Production> kernel2 = {Production("S", {"DECLARATION"}, 1)};
        vector<Production> closure2 = {Production("S", {"DECLARATION"}, 1)};
        states.push_back(SLRState(2, kernel2, closure2));
        
        
        vector<Production> kernel3 = {Production("S", {"C"}, 1)};
        vector<Production> closure3 = {Production("S", {"C"}, 1)};
        states.push_back(SLRState(3, kernel3, closure3));
        
        
        vector<Production> kernel4 = {Production("DECLARATION", {"declare", "VAR", "(", "PARAMS", ")", "BODY"}, 1)};
        vector<Production> closure4 = {
            Production("DECLARATION", {"declare", "VAR", "(", "PARAMS", ")", "BODY"}, 1),
            Production("VAR", {"(a+e+i+o+u)+(a+e+i+o+u+0+1)*"}, 0)
        };
        states.push_back(SLRState(4, kernel4, closure4));
        
        
        vector<Production> kernel5 = {Production("C", {"begin", "CMD", "end"}, 1)};
        vector<Production> closure5 = {
            Production("C", {"begin", "CMD", "end"}, 1),
            Production("CMD", {"VAR", "=", "EXPR", ";", "CMD"}, 0),
            Production("CMD", {"if", "COND", "CMD"}, 0),
            Production("CMD", {"for", "COND", "CMD"}, 0),
            Production("CMD", {"call", "VAR", ";", "CMD"}, 0),
            Production("CMD", {";"}, 0),
            Production("VAR", {"(a+e+i+o+u)+(a+e+i+o+u+0+1)*"}, 0)
        };
        states.push_back(SLRState(5, kernel5, closure5));
        
        addGotoTransition(0, "S", 1);
        addGotoTransition(0, "DECLARATION", 2);
        addGotoTransition(0, "C", 3);
        addGotoTransition(0, "declare", 4);
        addGotoTransition(0, "begin", 5);
        addGotoTransition(4, "VAR", 6);
        addGotoTransition(4, "(a+e+i+o+u)+(a+e+i+o+u+0+1)*", 7);
        addGotoTransition(5, "CMD", 8);
        addGotoTransition(5, "VAR", 9);
        addGotoTransition(5, "if", 10);
        addGotoTransition(5, "for", 11);
        addGotoTransition(5, "call", 12);
        addGotoTransition(5, "(a+e+i+o+u)+(a+e+i+o+u+0+1)*", 7);
        
        
        vector<Production> kernel6 = {Production("DECLARATION", {"declare", "VAR", "(", "PARAMS", ")", "BODY"}, 2)};
        vector<Production> closure6 = {Production("DECLARATION", {"declare", "VAR", "(", "PARAMS", ")", "BODY"}, 2)};
        states.push_back(SLRState(6, kernel6, closure6));
        
        
        vector<Production> kernel7 = {Production("VAR", {"(a+e+i+o+u)+(a+e+i+o+u+0+1)*"}, 1)};
        vector<Production> closure7 = {Production("VAR", {"(a+e+i+o+u)+(a+e+i+o+u+0+1)*"}, 1)};
        states.push_back(SLRState(7, kernel7, closure7));
        
        
        vector<Production> kernel8 = {Production("C", {"begin", "CMD", "end"}, 2)};
        vector<Production> closure8 = {Production("C", {"begin", "CMD", "end"}, 2)};
        states.push_back(SLRState(8, kernel8, closure8));
        
        
        vector<Production> kernel9 = {Production("CMD", {"VAR", "=", "EXPR", ";", "CMD"}, 1)};
        vector<Production> closure9 = {Production("CMD", {"VAR", "=", "EXPR", ";", "CMD"}, 1)};
        states.push_back(SLRState(9, kernel9, closure9));
        
        
        vector<Production> kernel10 = {Production("CMD", {"if", "COND", "CMD"}, 1)};
        vector<Production> closure10 = {
            Production("CMD", {"if", "COND", "CMD"}, 1),
            Production("COND", {"EXPR", "<", "EXPR"}, 0),
            Production("COND", {"EXPR", ">", "EXPR"}, 0),
            Production("COND", {"EXPR", "==", "EXPR"}, 0),
            Production("COND", {"EXPR", "!=", "EXPR"}, 0),
            Production("EXPR", {"EXPR", "+", "TERM"}, 0),
            Production("EXPR", {"EXPR", "-", "TERM"}, 0),
            Production("EXPR", {"TERM"}, 0),
            Production("TERM", {"TERM", "*", "FACT"}, 0),
            Production("TERM", {"TERM", "/", "FACT"}, 0),
            Production("TERM", {"FACT"}, 0),
            Production("FACT", {"(", "EXPR", ")"}, 0),
            Production("FACT", {"VAR"}, 0),
            Production("FACT", {"NUM"}, 0),
            Production("VAR", {"(a+e+i+o+u)+(a+e+i+o+u+0+1)*"}, 0),
            Production("NUM", {"(0+1)+"}, 0)
        };
        states.push_back(SLRState(10, kernel10, closure10));
        
       
        addGotoTransition(6, "(", 13);
        addGotoTransition(8, "end", 14);
        addGotoTransition(9, "=", 15);
        addGotoTransition(10, "COND", 16);
        addGotoTransition(10, "EXPR", 17);
        addGotoTransition(10, "TERM", 18);
        addGotoTransition(10, "FACT", 19);
        addGotoTransition(10, "(", 20);
        addGotoTransition(10, "VAR", 21);
        addGotoTransition(10, "NUM", 22);
        addGotoTransition(10, "(a+e+i+o+u)+(a+e+i+o+u+0+1)*", 7);
        addGotoTransition(10, "(0+1)+", 23);
        
        buildRemainingStates();
    }
    
    void buildRemainingStates() {
        
        vector<Production> kernel11 = {Production("CMD", {"for", "COND", "CMD"}, 1)};
        vector<Production> closure11 = {
            Production("CMD", {"for", "COND", "CMD"}, 1),
            Production("COND", {"EXPR", "<", "EXPR"}, 0),
            Production("COND", {"EXPR", ">", "EXPR"}, 0),
            Production("COND", {"EXPR", "==", "EXPR"}, 0),
            Production("COND", {"EXPR", "!=", "EXPR"}, 0),
            Production("EXPR", {"EXPR", "+", "TERM"}, 0),
            Production("EXPR", {"EXPR", "-", "TERM"}, 0),
            Production("EXPR", {"TERM"}, 0),
            Production("TERM", {"TERM", "*", "FACT"}, 0),
            Production("TERM", {"TERM", "/", "FACT"}, 0),
            Production("TERM", {"FACT"}, 0),
            Production("FACT", {"(", "EXPR", ")"}, 0),
            Production("FACT", {"VAR"}, 0),
            Production("FACT", {"NUM"}, 0),
            Production("VAR", {"(a+e+i+o+u)+(a+e+i+o+u+0+1)*"}, 0),
            Production("NUM", {"(0+1)+"}, 0)
        };
        states.push_back(SLRState(11, kernel11, closure11));
        
        
        vector<Production> kernel12 = {Production("CMD", {"call", "VAR", ";", "CMD"}, 1)};
        vector<Production> closure12 = {
            Production("CMD", {"call", "VAR", ";", "CMD"}, 1),
            Production("VAR", {"(a+e+i+o+u)+(a+e+i+o+u+0+1)*"}, 0)
        };
        states.push_back(SLRState(12, kernel12, closure12));
        
        
        vector<Production> kernel13 = {Production("DECLARATION", {"declare", "VAR", "(", "PARAMS", ")", "BODY"}, 3)};
        vector<Production> closure13 = {
            Production("DECLARATION", {"declare", "VAR", "(", "PARAMS", ")", "BODY"}, 3),
            Production("PARAMS", {"VARLIST"}, 0),
            Production("PARAMS", {";"}, 0),
            Production("VARLIST", {"VAR", ",", "VARLIST"}, 0),
            Production("VARLIST", {"VAR"}, 0),
            Production("VAR", {"(a+e+i+o+u)+(a+e+i+o+u+0+1)*"}, 0)
        };
        states.push_back(SLRState(13, kernel13, closure13));
        
        
        vector<Production> kernel14 = {Production("C", {"begin", "CMD", "end"}, 3)};
        vector<Production> closure14 = {Production("C", {"begin", "CMD", "end"}, 3)};
        states.push_back(SLRState(14, kernel14, closure14));
        
        
        vector<Production> kernel15 = {Production("CMD", {"VAR", "=", "EXPR", ";", "CMD"}, 2)};
        vector<Production> closure15 = {
            Production("CMD", {"VAR", "=", "EXPR", ";", "CMD"}, 2),
            Production("EXPR", {"EXPR", "+", "TERM"}, 0),
            Production("EXPR", {"EXPR", "-", "TERM"}, 0),
            Production("EXPR", {"TERM"}, 0),
            Production("TERM", {"TERM", "*", "FACT"}, 0),
            Production("TERM", {"TERM", "/", "FACT"}, 0),
            Production("TERM", {"FACT"}, 0),
            Production("FACT", {"(", "EXPR", ")"}, 0),
            Production("FACT", {"VAR"}, 0),
            Production("FACT", {"NUM"}, 0),
            Production("VAR", {"(a+e+i+o+u)+(a+e+i+o+u+0+1)*"}, 0),
            Production("NUM", {"(0+1)+"}, 0)
        };
        states.push_back(SLRState(15, kernel15, closure15));
        
        
        vector<Production> kernel16 = {Production("CMD", {"if", "COND", "CMD"}, 2)};
        vector<Production> closure16 = {
            Production("CMD", {"if", "COND", "CMD"}, 2),
            Production("CMD", {"VAR", "=", "EXPR", ";", "CMD"}, 0),
            Production("CMD", {"if", "COND", "CMD"}, 0),
            Production("CMD", {"for", "COND", "CMD"}, 0),
            Production("CMD", {"call", "VAR", ";", "CMD"}, 0),
            Production("CMD", {";"}, 0),
            Production("VAR", {"(a+e+i+o+u)+(a+e+i+o+u+0+1)*"}, 0)
        };
        states.push_back(SLRState(16, kernel16, closure16));
        
        
        vector<Production> kernel17 = {
            Production("COND", {"EXPR", "<", "EXPR"}, 1),
            Production("COND", {"EXPR", ">", "EXPR"}, 1),
            Production("COND", {"EXPR", "==", "EXPR"}, 1),
            Production("COND", {"EXPR", "!=", "EXPR"}, 1),
            Production("EXPR", {"EXPR", "+", "TERM"}, 1),
            Production("EXPR", {"EXPR", "-", "TERM"}, 1)
        };
        vector<Production> closure17 = {
            Production("COND", {"EXPR", "<", "EXPR"}, 1),
            Production("COND", {"EXPR", ">", "EXPR"}, 1),
            Production("COND", {"EXPR", "==", "EXPR"}, 1),
            Production("COND", {"EXPR", "!=", "EXPR"}, 1),
            Production("EXPR", {"EXPR", "+", "TERM"}, 1),
            Production("EXPR", {"EXPR", "-", "TERM"}, 1)
        };
        states.push_back(SLRState(17, kernel17, closure17));
        
        
        vector<Production> kernel18 = {
            Production("EXPR", {"TERM"}, 1),
            Production("TERM", {"TERM", "*", "FACT"}, 1),
            Production("TERM", {"TERM", "/", "FACT"}, 1)
        };
        vector<Production> closure18 = {
            Production("EXPR", {"TERM"}, 1),
            Production("TERM", {"TERM", "*", "FACT"}, 1),
            Production("TERM", {"TERM", "/", "FACT"}, 1)
        };
        states.push_back(SLRState(18, kernel18, closure18));
        
        
        vector<Production> kernel19 = {Production("TERM", {"FACT"}, 1)};
        vector<Production> closure19 = {Production("TERM", {"FACT"}, 1)};
        states.push_back(SLRState(19, kernel19, closure19));
        
        
        vector<Production> kernel20 = {Production("FACT", {"(", "EXPR", ")"}, 1)};
        vector<Production> closure20 = {
            Production("FACT", {"(", "EXPR", ")"}, 1),
            Production("EXPR", {"EXPR", "+", "TERM"}, 0),
            Production("EXPR", {"EXPR", "-", "TERM"}, 0),
            Production("EXPR", {"TERM"}, 0),
            Production("TERM", {"TERM", "*", "FACT"}, 0),
            Production("TERM", {"TERM", "/", "FACT"}, 0),
            Production("TERM", {"FACT"}, 0),
            Production("FACT", {"(", "EXPR", ")"}, 0),
            Production("FACT", {"VAR"}, 0),
            Production("FACT", {"NUM"}, 0),
            Production("VAR", {"(a+e+i+o+u)+(a+e+i+o+u+0+1)*"}, 0),
            Production("NUM", {"(0+1)+"}, 0)
        };
        states.push_back(SLRState(20, kernel20, closure20));
        
        
        vector<Production> kernel21 = {Production("FACT", {"VAR"}, 1)};
        vector<Production> closure21 = {Production("FACT", {"VAR"}, 1)};
        states.push_back(SLRState(21, kernel21, closure21));
        
        
        vector<Production> kernel22 = {Production("FACT", {"NUM"}, 1)};
        vector<Production> closure22 = {Production("FACT", {"NUM"}, 1)};
        states.push_back(SLRState(22, kernel22, closure22));
        
        
        vector<Production> kernel23 = {Production("NUM", {"(0+1)+"}, 1)};
        vector<Production> closure23 = {Production("NUM", {"(0+1)+"}, 1)};
        states.push_back(SLRState(23, kernel23, closure23));
        
        
        vector<Production> kernel24 = {Production("CMD", {"for", "COND", "CMD"}, 2)};
        vector<Production> closure24 = {
            Production("CMD", {"for", "COND", "CMD"}, 2),
            Production("CMD", {"VAR", "=", "EXPR", ";", "CMD"}, 0),
            Production("CMD", {"if", "COND", "CMD"}, 0),
            Production("CMD", {"for", "COND", "CMD"}, 0),
            Production("CMD", {"call", "VAR", ";", "CMD"}, 0),
            Production("CMD", {";"}, 0),
            Production("VAR", {"(a+e+i+o+u)+(a+e+i+o+u+0+1)*"}, 0)
        };
        states.push_back(SLRState(24, kernel24, closure24));
        
        
        vector<Production> kernel25 = {Production("CMD", {"call", "VAR", ";", "CMD"}, 2)};
        vector<Production> closure25 = {Production("CMD", {"call", "VAR", ";", "CMD"}, 2)};
        states.push_back(SLRState(25, kernel25, closure25));
        
        addGotoTransition(11, "COND", 24);
        addGotoTransition(11, "EXPR", 17);
        addGotoTransition(11, "TERM", 18);
        addGotoTransition(11, "FACT", 19);
        addGotoTransition(11, "(", 20);
        addGotoTransition(11, "VAR", 21);
        addGotoTransition(11, "NUM", 22);
        addGotoTransition(11, "(a+e+i+o+u)+(a+e+i+o+u+0+1)*", 7);
        addGotoTransition(11, "(0+1)+", 23);
        addGotoTransition(12, "VAR", 25);
        addGotoTransition(12, "(a+e+i+o+u)+(a+e+i+o+u+0+1)*", 7);
        addGotoTransition(13, "PARAMS", 26);
        addGotoTransition(13, "VARLIST", 27);
        addGotoTransition(13, "VAR", 28);
        addGotoTransition(13, "(a+e+i+o+u)+(a+e+i+o+u+0+1)*", 7);
        addGotoTransition(15, "EXPR", 29);
        addGotoTransition(15, "TERM", 18);
        addGotoTransition(15, "FACT", 19);
        addGotoTransition(15, "(", 20);
        addGotoTransition(15, "VAR", 21);
        addGotoTransition(15, "NUM", 22);
        addGotoTransition(15, "(a+e+i+o+u)+(a+e+i+o+u+0+1)*", 7);
        addGotoTransition(15, "(0+1)+", 23);
        addGotoTransition(16, "CMD", 30);
        addGotoTransition(16, "VAR", 9);
        addGotoTransition(16, "if", 10);
        addGotoTransition(16, "for", 11);
        addGotoTransition(16, "call", 12);
        addGotoTransition(16, "(a+e+i+o+u)+(a+e+i+o+u+0+1)*", 7);
        addGotoTransition(17, "<", 31);
        addGotoTransition(17, ">", 32);
        addGotoTransition(17, "==", 33);
        addGotoTransition(17, "!=", 34);
        addGotoTransition(17, "+", 35);
        addGotoTransition(17, "-", 36);
        addGotoTransition(18, "*", 37);
        addGotoTransition(18, "/", 38);
        addGotoTransition(20, "EXPR", 39);
        addGotoTransition(20, "TERM", 18);
        addGotoTransition(20, "FACT", 19);
        addGotoTransition(20, "(", 20);
        addGotoTransition(20, "VAR", 21);
        addGotoTransition(20, "NUM", 22);
        addGotoTransition(20, "(a+e+i+o+u)+(a+e+i+o+u+0+1)*", 7);
        addGotoTransition(20, "(0+1)+", 23);
        addGotoTransition(24, "CMD", 40);
        addGotoTransition(24, "VAR", 9);
        addGotoTransition(24, "if", 10);
        addGotoTransition(24, "for", 11);
        addGotoTransition(24, "call", 12);
        addGotoTransition(24, "(a+e+i+o+u)+(a+e+i+o+u+0+1)*", 7);
        addGotoTransition(25, ";", 41);

        
        
        vector<Production> kernel26 = {Production("DECLARATION", {"declare", "VAR", "(", "PARAMS", ")", "BODY"}, 4)};
        vector<Production> closure26 = {Production("DECLARATION", {"declare", "VAR", "(", "PARAMS", ")", "BODY"}, 4)};
        states.push_back(SLRState(26, kernel26, closure26));
        
        
        vector<Production> kernel27 = {Production("PARAMS", {"VARLIST"}, 1)};
        vector<Production> closure27 = {Production("PARAMS", {"VARLIST"}, 1)};
        states.push_back(SLRState(27, kernel27, closure27));
        
        
        vector<Production> kernel28 = {
            Production("VARLIST", {"VAR", ",", "VARLIST"}, 1),
            Production("VARLIST", {"VAR"}, 1)
        };
        vector<Production> closure28 = {
            Production("VARLIST", {"VAR", ",", "VARLIST"}, 1),
            Production("VARLIST", {"VAR"}, 1)
        };
        states.push_back(SLRState(28, kernel28, closure28));
        
        
        vector<Production> kernel29 = {
            Production("CMD", {"VAR", "=", "EXPR", ";", "CMD"}, 3),
            Production("EXPR", {"EXPR", "+", "TERM"}, 2),
            Production("EXPR", {"EXPR", "-", "TERM"}, 2)
        };
        vector<Production> closure29 = {
            Production("CMD", {"VAR", "=", "EXPR", ";", "CMD"}, 3),
            Production("EXPR", {"EXPR", "+", "TERM"}, 2),
            Production("EXPR", {"EXPR", "-", "TERM"}, 2)
        };
        states.push_back(SLRState(29, kernel29, closure29));
        
        addGotoTransition(26, ")", 42);
        addGotoTransition(28, ",", 43);
        addGotoTransition(29, ";", 44);
        addGotoTransition(29, "+", 35);
        addGotoTransition(29, "-", 36);
        
        
        vector<Production> kernel30 = {Production("CMD", {"if", "COND", "CMD"}, 3)};
        vector<Production> closure30 = {Production("CMD", {"if", "COND", "CMD"}, 3)};
        states.push_back(SLRState(30, kernel30, closure30));
        
        
        vector<Production> kernel31 = {Production("COND", {"EXPR", "<", "EXPR"}, 2)};
        vector<Production> closure31 = {
            Production("COND", {"EXPR", "<", "EXPR"}, 2),
            Production("EXPR", {"EXPR", "+", "TERM"}, 0),
            Production("EXPR", {"EXPR", "-", "TERM"}, 0),
            Production("EXPR", {"TERM"}, 0),
            Production("TERM", {"TERM", "*", "FACT"}, 0),
            Production("TERM", {"TERM", "/", "FACT"}, 0),
            Production("TERM", {"FACT"}, 0),
            Production("FACT", {"(", "EXPR", ")"}, 0),
            Production("FACT", {"VAR"}, 0),
            Production("FACT", {"NUM"}, 0),
            Production("VAR", {"(a+e+i+o+u)+(a+e+i+o+u+0+1)*"}, 0),
            Production("NUM", {"(0+1)+"}, 0)
        };
        states.push_back(SLRState(31, kernel31, closure31));
        
        
        vector<Production> kernel32 = {Production("COND", {"EXPR", ">", "EXPR"}, 2)};
        vector<Production> closure32 = {
            Production("COND", {"EXPR", ">", "EXPR"}, 2),
            Production("EXPR", {"EXPR", "+", "TERM"}, 0),
            Production("EXPR", {"EXPR", "-", "TERM"}, 0),
            Production("EXPR", {"TERM"}, 0),
            Production("TERM", {"TERM", "*", "FACT"}, 0),
            Production("TERM", {"TERM", "/", "FACT"}, 0),
            Production("TERM", {"FACT"}, 0),
            Production("FACT", {"(", "EXPR", ")"}, 0),
            Production("FACT", {"VAR"}, 0),
            Production("FACT", {"NUM"}, 0),
            Production("VAR", {"(a+e+i+o+u)+(a+e+i+o+u+0+1)*"}, 0),
            Production("NUM", {"(0+1)+"}, 0)
        };
        states.push_back(SLRState(32, kernel32, closure32));
        
        
        vector<Production> kernel33 = {Production("COND", {"EXPR", "==", "EXPR"}, 2)};
        vector<Production> closure33 = {
            Production("COND", {"EXPR", "==", "EXPR"}, 2),
            Production("EXPR", {"EXPR", "+", "TERM"}, 0),
            Production("EXPR", {"EXPR", "-", "TERM"}, 0),
            Production("EXPR", {"TERM"}, 0),
            Production("TERM", {"TERM", "*", "FACT"}, 0),
            Production("TERM", {"TERM", "/", "FACT"}, 0),
            Production("TERM", {"FACT"}, 0),
            Production("FACT", {"(", "EXPR", ")"}, 0),
            Production("FACT", {"VAR"}, 0),
            Production("FACT", {"NUM"}, 0),
            Production("VAR", {"(a+e+i+o+u)+(a+e+i+o+u+0+1)*"}, 0),
            Production("NUM", {"(0+1)+"}, 0)
        };
        states.push_back(SLRState(33, kernel33, closure33));
        
        
        vector<Production> kernel34 = {Production("COND", {"EXPR", "!=", "EXPR"}, 2)};
        vector<Production> closure34 = {
            Production("COND", {"EXPR", "!=", "EXPR"}, 2),
            Production("EXPR", {"EXPR", "+", "TERM"}, 0),
            Production("EXPR", {"EXPR", "-", "TERM"}, 0),
            Production("EXPR", {"TERM"}, 0),
            Production("TERM", {"TERM", "*", "FACT"}, 0),
            Production("TERM", {"TERM", "/", "FACT"}, 0),
            Production("TERM", {"FACT"}, 0),
            Production("FACT", {"(", "EXPR", ")"}, 0),
            Production("FACT", {"VAR"}, 0),
            Production("FACT", {"NUM"}, 0),
            Production("VAR", {"(a+e+i+o+u)+(a+e+i+o+u+0+1)*"}, 0),
            Production("NUM", {"(0+1)+"}, 0)
        };
        states.push_back(SLRState(34, kernel34, closure34));
        
        
        vector<Production> kernel35 = {Production("EXPR", {"EXPR", "+", "TERM"}, 2)};
        vector<Production> closure35 = {
            Production("EXPR", {"EXPR", "+", "TERM"}, 2),
            Production("TERM", {"TERM", "*", "FACT"}, 0),
            Production("TERM", {"TERM", "/", "FACT"}, 0),
            Production("TERM", {"FACT"}, 0),
            Production("FACT", {"(", "EXPR", ")"}, 0),
            Production("FACT", {"VAR"}, 0),
            Production("FACT", {"NUM"}, 0),
            Production("VAR", {"(a+e+i+o+u)+(a+e+i+o+u+0+1)*"}, 0),
            Production("NUM", {"(0+1)+"}, 0)
        };
        states.push_back(SLRState(35, kernel35, closure35));
        
        
        vector<Production> kernel36 = {Production("EXPR", {"EXPR", "-", "TERM"}, 2)};
        vector<Production> closure36 = {
            Production("EXPR", {"EXPR", "-", "TERM"}, 2),
            Production("TERM", {"TERM", "*", "FACT"}, 0),
            Production("TERM", {"TERM", "/", "FACT"}, 0),
            Production("TERM", {"FACT"}, 0),
            Production("FACT", {"(", "EXPR", ")"}, 0),
            Production("FACT", {"VAR"}, 0),
            Production("FACT", {"NUM"}, 0),
            Production("VAR", {"(a+e+i+o+u)+(a+e+i+o+u+0+1)*"}, 0),
            Production("NUM", {"(0+1)+"}, 0)
        };
        states.push_back(SLRState(36, kernel36, closure36));
        
        
        vector<Production> kernel37 = {Production("TERM", {"TERM", "*", "FACT"}, 2)};
        vector<Production> closure37 = {
            Production("TERM", {"TERM", "*", "FACT"}, 2),
            Production("FACT", {"(", "EXPR", ")"}, 0),
            Production("FACT", {"VAR"}, 0),
            Production("FACT", {"NUM"}, 0),
            Production("VAR", {"(a+e+i+o+u)+(a+e+i+o+u+0+1)*"}, 0),
            Production("NUM", {"(0+1)+"}, 0)
        };
        states.push_back(SLRState(37, kernel37, closure37));
        
        
        vector<Production> kernel38 = {Production("TERM", {"TERM", "/", "FACT"}, 2)};
        vector<Production> closure38 = {
            Production("TERM", {"TERM", "/", "FACT"}, 2),
            Production("FACT", {"(", "EXPR", ")"}, 0),
            Production("FACT", {"VAR"}, 0),
            Production("FACT", {"NUM"}, 0),
            Production("VAR", {"(a+e+i+o+u)+(a+e+i+o+u+0+1)*"}, 0),
            Production("NUM", {"(0+1)+"}, 0)
        };
        states.push_back(SLRState(38, kernel38, closure38));
        
        
        vector<Production> kernel39 = {
            Production("FACT", {"(", "EXPR", ")"}, 2),
            Production("EXPR", {"EXPR", "+", "TERM"}, 2),
            Production("EXPR", {"EXPR", "-", "TERM"}, 2)
        };
        vector<Production> closure39 = {
            Production("FACT", {"(", "EXPR", ")"}, 2),
            Production("EXPR", {"EXPR", "+", "TERM"}, 2),
            Production("EXPR", {"EXPR", "-", "TERM"}, 2)
        };
        states.push_back(SLRState(39, kernel39, closure39));
        
        
        vector<Production> kernel40 = {Production("CMD", {"for", "COND", "CMD"}, 3)};
        vector<Production> closure40 = {Production("CMD", {"for", "COND", "CMD"}, 3)};
        states.push_back(SLRState(40, kernel40, closure40));
        
        
        vector<Production> kernel41 = {Production("CMD", {"call", "VAR", ";", "CMD"}, 3)};
        vector<Production> closure41 = {
            Production("CMD", {"call", "VAR", ";", "CMD"}, 3),
            Production("CMD", {"VAR", "=", "EXPR", ";", "CMD"}, 0),
            Production("CMD", {"if", "COND", "CMD"}, 0),
            Production("CMD", {"for", "COND", "CMD"}, 0),
            Production("CMD", {"call", "VAR", ";", "CMD"}, 0),
            Production("CMD", {";"}, 0),
            Production("VAR", {"(a+e+i+o+u)+(a+e+i+o+u+0+1)*"}, 0)
        };
        states.push_back(SLRState(41, kernel41, closure41));
        
        
        vector<Production> kernel42 = {Production("DECLARATION", {"declare", "VAR", "(", "PARAMS", ")", "BODY"}, 5)};
        vector<Production> closure42 = {
            Production("DECLARATION", {"declare", "VAR", "(", "PARAMS", ")", "BODY"}, 5),
            Production("BODY", {"D", "C"}, 0),
            Production("D", {"int", "VAR", ";", "D"}, 0),
            Production("D", {})
        };
        states.push_back(SLRState(42, kernel42, closure42));
        
       
        vector<Production> kernel43 = {Production("VARLIST", {"VAR", ",", "VARLIST"}, 2)};
        vector<Production> closure43 = {
            Production("VARLIST", {"VAR", ",", "VARLIST"}, 2),
            Production("VARLIST", {"VAR", ",", "VARLIST"}, 0),
            Production("VARLIST", {"VAR"}, 0),
            Production("VAR", {"(a+e+i+o+u)+(a+e+i+o+u+0+1)*"}, 0)
        };
        states.push_back(SLRState(43, kernel43, closure43));
        
        
        vector<Production> kernel44 = {Production("CMD", {"VAR", "=", "EXPR", ";", "CMD"}, 4)};
        vector<Production> closure44 = {
            Production("CMD", {"VAR", "=", "EXPR", ";", "CMD"}, 4),
            Production("CMD", {"VAR", "=", "EXPR", ";", "CMD"}, 0),
            Production("CMD", {"if", "COND", "CMD"}, 0),
            Production("CMD", {"for", "COND", "CMD"}, 0),
            Production("CMD", {"call", "VAR", ";", "CMD"}, 0),
            Production("CMD", {";"}, 0),
            Production("VAR", {"(a+e+i+o+u)+(a+e+i+o+u+0+1)*"}, 0)
        };
        states.push_back(SLRState(44, kernel44, closure44));
        
        
        vector<Production> kernel45 = {
            Production("COND", {"EXPR", "<", "EXPR"}, 3),
            Production("EXPR", {"EXPR", "+", "TERM"}, 2),
            Production("EXPR", {"EXPR", "-", "TERM"}, 2)
        };
        vector<Production> closure45 = {
            Production("COND", {"EXPR", "<", "EXPR"}, 3),
            Production("EXPR", {"EXPR", "+", "TERM"}, 2),
            Production("EXPR", {"EXPR", "-", "TERM"}, 2)
        };
        states.push_back(SLRState(45, kernel45, closure45));
        
        
        vector<Production> kernel46 = {
            Production("COND", {"EXPR", ">", "EXPR"}, 3),
            Production("EXPR", {"EXPR", "+", "TERM"}, 2),
            Production("EXPR", {"EXPR", "-", "TERM"}, 2)
        };
        vector<Production> closure46 = {
            Production("COND", {"EXPR", ">", "EXPR"}, 3),
            Production("EXPR", {"EXPR", "+", "TERM"}, 2),
            Production("EXPR", {"EXPR", "-", "TERM"}, 2)
        };
        states.push_back(SLRState(46, kernel46, closure46));
        
       
        vector<Production> kernel47 = {
            Production("COND", {"EXPR", "==", "EXPR"}, 3),
            Production("EXPR", {"EXPR", "+", "TERM"}, 2),
            Production("EXPR", {"EXPR", "-", "TERM"}, 2)
        };
        vector<Production> closure47 = {
            Production("COND", {"EXPR", "==", "EXPR"}, 3),
            Production("EXPR", {"EXPR", "+", "TERM"}, 2),
            Production("EXPR", {"EXPR", "-", "TERM"}, 2)
        };
        states.push_back(SLRState(47, kernel47, closure47));
        
        
        vector<Production> kernel48 = {
            Production("COND", {"EXPR", "!=", "EXPR"}, 3),
            Production("EXPR", {"EXPR", "+", "TERM"}, 2),
            Production("EXPR", {"EXPR", "-", "TERM"}, 2)
        };
        vector<Production> closure48 = {
            Production("COND", {"EXPR", "!=", "EXPR"}, 3),
            Production("EXPR", {"EXPR", "+", "TERM"}, 2),
            Production("EXPR", {"EXPR", "-", "TERM"}, 2)
        };
        states.push_back(SLRState(48, kernel48, closure48));
        
    
        vector<Production> kernel49 = {
            Production("EXPR", {"EXPR", "+", "TERM"}, 3),
            Production("TERM", {"TERM", "*", "FACT"}, 2),
            Production("TERM", {"TERM", "/", "FACT"}, 2)
        };
        vector<Production> closure49 = {
            Production("EXPR", {"EXPR", "+", "TERM"}, 3),
            Production("TERM", {"TERM", "*", "FACT"}, 2),
            Production("TERM", {"TERM", "/", "FACT"}, 2)
        };
        states.push_back(SLRState(49, kernel49, closure49));
        
        
        vector<Production> kernel50 = {
            Production("EXPR", {"EXPR", "-", "TERM"}, 3),
            Production("TERM", {"TERM", "*", "FACT"}, 2),
            Production("TERM", {"TERM", "/", "FACT"}, 2)
        };
        vector<Production> closure50 = {
            Production("EXPR", {"EXPR", "-", "TERM"}, 3),
            Production("TERM", {"TERM", "*", "FACT"}, 2),
            Production("TERM", {"TERM", "/", "FACT"}, 2)
        };
        states.push_back(SLRState(50, kernel50, closure50));
        
       
        vector<Production> kernel51 = {Production("TERM", {"TERM", "*", "FACT"}, 3)};
        vector<Production> closure51 = {Production("TERM", {"TERM", "*", "FACT"}, 3)};
        states.push_back(SLRState(51, kernel51, closure51));
        
        
        vector<Production> kernel52 = {Production("TERM", {"TERM", "/", "FACT"}, 3)};
        vector<Production> closure52 = {Production("TERM", {"TERM", "/", "FACT"}, 3)};
        states.push_back(SLRState(52, kernel52, closure52));
        
        
        vector<Production> kernel53 = {Production("FACT", {"(", "EXPR", ")"}, 3)};
        vector<Production> closure53 = {Production("FACT", {"(", "EXPR", ")"}, 3)};
        states.push_back(SLRState(53, kernel53, closure53));
        
        
        vector<Production> kernel54 = {Production("CMD", {"call", "VAR", ";", "CMD"}, 4)};
        vector<Production> closure54 = {Production("CMD", {"call", "VAR", ";", "CMD"}, 4)};
        states.push_back(SLRState(54, kernel54, closure54));
        
        
        vector<Production> kernel55 = {Production("DECLARATION", {"declare", "VAR", "(", "PARAMS", ")", "BODY"}, 6)};
        vector<Production> closure55 = {Production("DECLARATION", {"declare", "VAR", "(", "PARAMS", ")", "BODY"}, 6)};
        states.push_back(SLRState(55, kernel55, closure55));
        
       
        vector<Production> kernel56 = {Production("BODY", {"D", "C"}, 1)};
        vector<Production> closure56 = {
            Production("BODY", {"D", "C"}, 1),
            Production("C", {"begin", "CMD", "end"}, 0)
        };
        states.push_back(SLRState(56, kernel56, closure56));
        
        
        vector<Production> kernel57 = {Production("D", {"int", "VAR", ";", "D"}, 1)};
        vector<Production> closure57 = {
            Production("D", {"int", "VAR", ";", "D"}, 1),
            Production("VAR", {"(a+e+i+o+u)+(a+e+i+o+u+0+1)*"}, 0)
        };
        states.push_back(SLRState(57, kernel57, closure57));
        
        
        vector<Production> kernel58 = {Production("VARLIST", {"VAR", ",", "VARLIST"}, 3)};
        vector<Production> closure58 = {Production("VARLIST", {"VAR", ",", "VARLIST"}, 3)};
        states.push_back(SLRState(58, kernel58, closure58));
        
       
        vector<Production> kernel59 = {Production("CMD", {"VAR", "=", "EXPR", ";", "CMD"}, 5)};
        vector<Production> closure59 = {Production("CMD", {"VAR", "=", "EXPR", ";", "CMD"}, 5)};
        states.push_back(SLRState(59, kernel59, closure59));
        
        
        vector<Production> kernel60 = {Production("BODY", {"D", "C"}, 2)};
        vector<Production> closure60 = {Production("BODY", {"D", "C"}, 2)};
        states.push_back(SLRState(60, kernel60, closure60));
        
        
        vector<Production> kernel61 = {Production("D", {"int", "VAR", ";", "D"}, 2)};
        vector<Production> closure61 = {Production("D", {"int", "VAR", ";", "D"}, 2)};
        states.push_back(SLRState(61, kernel61, closure61));
        
        
        vector<Production> kernel62 = {Production("D", {"int", "VAR", ";", "D"}, 3)};
        vector<Production> closure62 = {
            Production("D", {"int", "VAR", ";", "D"}, 3),
            Production("D", {"int", "VAR", ";", "D"}, 0),
            Production("D", {})
        };
        states.push_back(SLRState(62, kernel62, closure62));
        
        
        vector<Production> kernel63 = {Production("D", {"int", "VAR", ";", "D"}, 4)};
        vector<Production> closure63 = {Production("D", {"int", "VAR", ";", "D"}, 4)};
        states.push_back(SLRState(63, kernel63, closure63));
        
        
        addGotoTransition(30, "CMD", 30);
        addGotoTransition(30, "VAR", 9);
        addGotoTransition(30, "if", 10);
        addGotoTransition(30, "for", 11);
        addGotoTransition(30, "call", 12);
        addGotoTransition(30, "(a+e+i+o+u)+(a+e+i+o+u+0+1)*", 7);
        addGotoTransition(31, "EXPR", 45);
        addGotoTransition(31, "TERM", 18);
        addGotoTransition(31, "FACT", 19);
        addGotoTransition(31, "(", 20);
        addGotoTransition(31, "VAR", 21);
        addGotoTransition(31, "NUM", 22);
        addGotoTransition(31, "(a+e+i+o+u)+(a+e+i+o+u+0+1)*", 7);
        addGotoTransition(31, "(0+1)+", 23);
        addGotoTransition(32, "EXPR", 46);
        addGotoTransition(32, "TERM", 18);
        addGotoTransition(32, "FACT", 19);
        addGotoTransition(32, "(", 20);
        addGotoTransition(32, "VAR", 21);
        addGotoTransition(32, "NUM", 22);
        addGotoTransition(32, "(a+e+i+o+u)+(a+e+i+o+u+0+1)*", 7);
        addGotoTransition(32, "(0+1)+", 23);
        addGotoTransition(33, "EXPR", 47);
        addGotoTransition(33, "TERM", 18);
        addGotoTransition(33, "FACT", 19);
        addGotoTransition(33, "(", 20);
        addGotoTransition(33, "VAR", 21);
        addGotoTransition(33, "NUM", 22);
        addGotoTransition(33, "(a+e+i+o+u)+(a+e+i+o+u+0+1)*", 7);
        addGotoTransition(33, "(0+1)+", 23);
        addGotoTransition(34, "EXPR", 48);
        addGotoTransition(34, "TERM", 18);
        addGotoTransition(34, "FACT", 19);
        addGotoTransition(34, "(", 20);
        addGotoTransition(34, "VAR", 21);
        addGotoTransition(34, "NUM", 22);
        addGotoTransition(34, "(a+e+i+o+u)+(a+e+i+o+u+0+1)*", 7);
        addGotoTransition(34, "(0+1)+", 23);
        addGotoTransition(35, "TERM", 49);
        addGotoTransition(35, "FACT", 19);
        addGotoTransition(35, "(", 20);
        addGotoTransition(35, "VAR", 21);
        addGotoTransition(35, "NUM", 22);
        addGotoTransition(35, "(a+e+i+o+u)+(a+e+i+o+u+0+1)*", 7);
        addGotoTransition(35, "(0+1)+", 23);
        addGotoTransition(36, "TERM", 50);
        addGotoTransition(36, "FACT", 19);
        addGotoTransition(36, "(", 20);
        addGotoTransition(36, "VAR", 21);
        addGotoTransition(36, "NUM", 22);
        addGotoTransition(36, "(a+e+i+o+u)+(a+e+i+o+u+0+1)*", 7);
        addGotoTransition(36, "(0+1)+", 23);
        addGotoTransition(37, "FACT", 51);
        addGotoTransition(37, "(", 20);
        addGotoTransition(37, "VAR", 21);
        addGotoTransition(37, "NUM", 22);
        addGotoTransition(37, "(a+e+i+o+u)+(a+e+i+o+u+0+1)*", 7);
        addGotoTransition(37, "(0+1)+", 23);
        addGotoTransition(38, "FACT", 52);
        addGotoTransition(38, "(", 20);
        addGotoTransition(38, "VAR", 21);
        addGotoTransition(38, "NUM", 22);
        addGotoTransition(38, "(a+e+i+o+u)+(a+e+i+o+u+0+1)*", 7);
        addGotoTransition(38, "(0+1)+", 23);
        addGotoTransition(39, ")", 53);
        addGotoTransition(39, "+", 35);
        addGotoTransition(39, "-", 36);
        addGotoTransition(41, "CMD", 54);
        addGotoTransition(41, "VAR", 9);
        addGotoTransition(41, "if", 10);
        addGotoTransition(41, "for", 11);
        addGotoTransition(41, "call", 12);
        addGotoTransition(41, "(a+e+i+o+u)+(a+e+i+o+u+0+1)*", 7);
        addGotoTransition(42, "BODY", 55);
        addGotoTransition(42, "D", 56);
        addGotoTransition(42, "int", 57);
        addGotoTransition(43, "VARLIST", 58);
        addGotoTransition(43, "VAR", 28);
        addGotoTransition(43, "(a+e+i+o+u)+(a+e+i+o+u+0+1)*", 7);
        addGotoTransition(45, "+", 35);
        addGotoTransition(45, "-", 36);
        addGotoTransition(46, "+", 35);
        addGotoTransition(46, "-", 36);
        addGotoTransition(47, "+", 35);
        addGotoTransition(47, "-", 36);
        addGotoTransition(48, "+", 35);
        addGotoTransition(48, "-", 36);
        addGotoTransition(49, "*", 37);
        addGotoTransition(49, "/", 38);
        addGotoTransition(50, "*", 37);
        addGotoTransition(50, "/", 38);
        addGotoTransition(56, "C", 60);
        addGotoTransition(56, "begin", 5);
        addGotoTransition(57, "VAR", 61);
        addGotoTransition(57, "(a+e+i+o+u)+(a+e+i+o+u+0+1)*", 7);
        addGotoTransition(61, ";", 62);
        addGotoTransition(62, "D", 63);
        addGotoTransition(62, "int", 57);
    }
    
    void addGotoTransition(int from, string symbol, int to) {
        goto_transitions.push_back(GotoTransition(from, symbol, to));
    }
    
    void printTable() {
        cout << "SLR Closure Table" << endl;
        cout << "=================" << endl;
        cout << "Goto\t\tKernel\t\tState\tClosure" << endl;
        cout << "----\t\t------\t\t-----\t-------" << endl;
        
        for (const auto& state : states) {
            cout << "State " << state.state_id << ":" << endl;
            
            
            cout << "\tKernel: ";
            for (const auto& prod : state.kernel) {
                cout << "{" << prod.toString() << "} ";
            }
            cout << endl;
            
            
            cout << "\tClosure: ";
            for (const auto& prod : state.closure) {
                cout << "{" << prod.toString() << "} ";
            }
            cout << endl;
            
            
            cout << "\tGoto: ";
            for (const auto& trans : goto_transitions) {
                if (trans.from_state == state.state_id) {
                    cout << "goto(" << trans.from_state << ", " << trans.symbol << ") -> " << trans.to_state << " ";
                }
            }
            cout << endl << endl;
        }
    }
    
    int getGoto(int state, string symbol) {
        for (const auto& trans : goto_transitions) {
            if (trans.from_state == state && trans.symbol == symbol) {
                return trans.to_state;
            }
        }
        return -1;
    }
    
    SLRState* getState(int state_id) {
        for (auto& state : states) {
            if (state.state_id == state_id) {
                return &state;
            }
        }
        return nullptr;
    }
    
    const vector<SLRState>& getStates() const {
        return states;
    }
    
    const vector<GotoTransition>& getGotoTransitions() const {
        return goto_transitions;
    }
};

SLRTable slrTable;

void initializeSLRTable() {}

SLRTable* getSLRTable() {
    return &slrTable;
}
