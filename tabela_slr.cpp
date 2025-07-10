#include "tabela_slr.h"
#include <bits/stdc++.h>

using namespace std;

void initializeSLRTable() {
    vector<int> simbolos = {
        2, 1, 31, 29, 30, 27, 25, 26, 32, 33, 35, 28, 7, 10, 24, 14, 13, // tokens
        64, 65, 66, 67, 68, 69 // producoes
    }; 

    tuple<char, int> tupla_nula = make_tuple('\0', -1);

    // TODO: Implement SLR table initialization
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < simbolos.size(); j++) {
            tabela[i][simbolos[j]] = tupla_nula;
        }
    }
}

vector getProducoes(){
    //0 - BODY -> D C
    //1 - D -> int VAR ; D
    //2 - D -> ''
    //3 - C -> begin CMD end
    //4 - CMD -> VAR = EXPR ; CMD
    //5 - CMD -> if COND CMD
    //6 - CMD -> for COND CMD
    //7 - CMD -> ''
    //8 - COND -> EXPR < EXPR
    //9 - COND -> EXPR > EXPR
    //10 - COND -> EXPR == EXPR
    //11 - COND -> EXPR != EXPR
    //12 - EXPR -> EXPR + TERM
    //13 - EXPR -> EXPR - TERM
    //14 - EXPR -> TERM
    //15 - TERM -> TERM * FACT
    //16 - TERM -> TERM / FACT
    //17 - TERM -> FACT
    //18 - FACT -> ( EXPR )
    //19 - FACT -> VAR
    //20 - FACT -> NUM

    // idProd - tamanho

    return vector<tuple<int, int>> {
        make_tuple(0, 2),
        make_tuple(1, 4),
        make_tuple(2, 0),
        make_tuple(3, 3),
        make_tuple(4, 5),
        make_tuple(5, 3),
        make_tuple(6, 3),
        make_tuple(7, 0),
        make_tuple(8, 3),
        make_tuple(9, 3),
        make_tuple(10, 3),
        make_tuple(11, 3),
        make_tuple(12, 3),
        make_tuple(13, 3),
        make_tuple(14, 1),
        make_tuple(15, 3),
        make_tuple(16, 3),
        make_tuple(17, 1),
        make_tuple(18, 3),
        make_tuple(19, 1),
        make_tuple(20, 1),
        
    };
}