#include "tabela_slr.h"
#include <bits/stdc++.h>

using namespace std;

void initializeSLRTable() {
    vector<int> simbolos = {
        2, 1, 31, 29, 30, 27, 25, 26, 32, 33, 35, 28, 7, 10, 24, 14, 13, // tokens
        64, 65, 66, 67, 68, 69 // producoes
    }; 

    tuple<char, int> tupla_nula = make_tuple('\0', -1);

    // Inicializa toda a tabela com tuplas nulas
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < simbolos.size(); j++) {
            tabela[i][simbolos[j]] = tupla_nula;
        }
    }

    // Estado 0
    tabela[0][14] = make_tuple('E', 2);
    tabela[0][7] = make_tuple('R', 2);
    tabela[0][63] = make_tuple('V', 1);

    // Estado 1
    tabela[1][7] = make_tuple('E', 4);
    tabela[1][64] = make_tuple('V', 3);

    // Estado 2
    tabela[2][1] = make_tuple('E', 5);

    // Estado 3
    tabela[3][62] = make_tuple('A', 1); // acc

    // Estado 4
    tabela[4][1] = make_tuple('E', 7);
    tabela[4][14] = make_tuple('E', 8);
    tabela[4][17] = make_tuple('E', 9);
    tabela[4][13] = make_tuple('R', 7);
    tabela[4][65] = make_tuple('V', 6);

    // Estado 5
    tabela[5][26] = make_tuple('E', 10);

    // Estado 6
    tabela[6][13] = make_tuple('E', 11);

    // Estado 7
    tabela[7][27] = make_tuple('E', 12);

    // Estado 8
    tabela[8][1] = make_tuple('E', 18);
    tabela[8][18] = make_tuple('E', 17);
    tabela[8][19] = make_tuple('E', 19);
    tabela[8][66] = make_tuple('V', 13);
    tabela[8][67] = make_tuple('V', 14);
    tabela[8][68] = make_tuple('V', 15);
    tabela[8][69] = make_tuple('V', 16);

    // Estado 9
    tabela[9][1] = make_tuple('E', 18);
    tabela[9][18] = make_tuple('E', 17);
    tabela[9][19] = make_tuple('E', 19);
    tabela[9][66] = make_tuple('V', 20);
    tabela[9][67] = make_tuple('V', 14);
    tabela[9][68] = make_tuple('V', 15);
    tabela[9][69] = make_tuple('V', 16);

    // Estado 10
    tabela[10][14] = make_tuple('E', 2);
    tabela[10][7] = make_tuple('R', 2);
    tabela[10][63] = make_tuple('V', 21);

    // Estado 11
    tabela[11][63] = make_tuple('R', 3); // r3 em $

    // Estado 12
    tabela[12][1] = make_tuple('E', 18);
    tabela[12][18] = make_tuple('E', 17);
    tabela[12][19] = make_tuple('E', 19);
    tabela[12][67] = make_tuple('V', 22);
    tabela[12][68] = make_tuple('V', 15);
    tabela[12][69] = make_tuple('V', 16);

    // Estado 13
    tabela[13][1] = make_tuple('E', 7);
    tabela[13][14] = make_tuple('E', 8);
    tabela[13][17] = make_tuple('E', 9);
    tabela[13][13] = make_tuple('R', 7);
    tabela[13][65] = make_tuple('V', 23);

    // Estado 14
    tabela[14][20] = make_tuple('E', 24);
    tabela[14][21] = make_tuple('E', 25);
    tabela[14][29] = make_tuple('E', 26);
    tabela[14][30] = make_tuple('E', 27);
    tabela[14][22] = make_tuple('E', 28);
    tabela[14][23] = make_tuple('E', 29);

    // Estado 15 - Reduções R14
    tabela[15][1] = make_tuple('R', 14);
    tabela[15][26] = make_tuple('R', 14);
    tabela[15][13] = make_tuple('R', 14);
    tabela[15][14] = make_tuple('R', 14);
    tabela[15][17] = make_tuple('R', 14);
    tabela[15][20] = make_tuple('R', 14);
    tabela[15][21] = make_tuple('R', 14);
    tabela[15][29] = make_tuple('R', 14);
    tabela[15][30] = make_tuple('R', 14);
    tabela[15][22] = make_tuple('R', 14);
    tabela[15][24] = make_tuple('E', 30);
    tabela[15][25] = make_tuple('E', 31);
    tabela[15][23] = make_tuple('R', 14);
    tabela[15][19] = make_tuple('R', 14);

    // Estado 16 - Reduções R17
    tabela[16][1] = make_tuple('R', 17);
    tabela[16][26] = make_tuple('R', 17);
    tabela[16][13] = make_tuple('R', 17);
    tabela[16][14] = make_tuple('R', 17);
    tabela[16][17] = make_tuple('R', 17);
    tabela[16][20] = make_tuple('R', 17);
    tabela[16][21] = make_tuple('R', 17);
    tabela[16][29] = make_tuple('R', 17);
    tabela[16][30] = make_tuple('R', 17);
    tabela[16][22] = make_tuple('R', 17);
    tabela[16][24] = make_tuple('R', 17);
    tabela[16][25] = make_tuple('R', 17);
    tabela[16][23] = make_tuple('R', 17);
    tabela[16][19] = make_tuple('R', 17);

    // Estado 17
    tabela[17][1] = make_tuple('E', 18);
    tabela[17][18] = make_tuple('E', 17);
    tabela[17][2] = make_tuple('E', 19);
    tabela[17][67] = make_tuple('V', 32);
    tabela[17][68] = make_tuple('V', 15);
    tabela[17][69] = make_tuple('V', 16);

    // Estado 18 - Reduções R19
    tabela[18][1] = make_tuple('R', 19);
    tabela[18][26] = make_tuple('R', 19);
    tabela[18][13] = make_tuple('R', 19);
    tabela[18][14] = make_tuple('R', 19);
    tabela[18][17] = make_tuple('R', 19);
    tabela[18][20] = make_tuple('R', 19);
    tabela[18][21] = make_tuple('R', 19);
    tabela[18][29] = make_tuple('R', 19);
    tabela[18][30] = make_tuple('R', 19);
    tabela[18][22] = make_tuple('R', 19);
    tabela[18][24] = make_tuple('R', 19);
    tabela[18][25] = make_tuple('R', 19);
    tabela[18][23] = make_tuple('R', 19);
    tabela[18][19] = make_tuple('R', 19);

    // Estado 19 - Reduções R20
    tabela[19][1] = make_tuple('R', 20);
    tabela[19][26] = make_tuple('R', 20);
    tabela[19][13] = make_tuple('R', 20);
    tabela[19][14] = make_tuple('R', 20);
    tabela[19][17] = make_tuple('R', 20);
    tabela[19][20] = make_tuple('R', 20);
    tabela[19][21] = make_tuple('R', 20);
    tabela[19][29] = make_tuple('R', 20);
    tabela[19][30] = make_tuple('R', 20);
    tabela[19][22] = make_tuple('R', 20);
    tabela[19][24] = make_tuple('R', 20);
    tabela[19][25] = make_tuple('R', 20);
    tabela[19][23] = make_tuple('R', 20);
    tabela[19][19] = make_tuple('R', 20);

    // Estado 20
    tabela[20][1] = make_tuple('E', 7);
    tabela[20][14] = make_tuple('E', 8);
    tabela[20][17] = make_tuple('E', 9);
    tabela[20][13] = make_tuple('R', 7);
    tabela[20][65] = make_tuple('V', 33);

    // Estado 21
    tabela[21][7] = make_tuple('R', 1);

    // Estado 22
    tabela[22][26] = make_tuple('E', 34);
    tabela[22][22] = make_tuple('E', 28);
    tabela[22][23] = make_tuple('E', 29);

    // Estado 23
    tabela[23][13] = make_tuple('R', 5);

    // Estado 24
    tabela[24][1] = make_tuple('E', 18);
    tabela[24][18] = make_tuple('E', 17);
    tabela[24][2] = make_tuple('E', 19);
    tabela[24][67] = make_tuple('V', 35);
    tabela[24][68] = make_tuple('V', 15);
    tabela[24][69] = make_tuple('V', 16);

    // Estado 25
    tabela[25][1] = make_tuple('E', 18);
    tabela[25][18] = make_tuple('E', 17);
    tabela[25][2] = make_tuple('E', 19);
    tabela[25][67] = make_tuple('V', 36);
    tabela[25][68] = make_tuple('V', 15);
    tabela[25][69] = make_tuple('V', 16);

    // Estado 26
    tabela[26][1] = make_tuple('E', 18);
    tabela[26][18] = make_tuple('E', 17);
    tabela[26][2] = make_tuple('E', 19);
    tabela[26][67] = make_tuple('V', 37);
    tabela[26][68] = make_tuple('V', 15);
    tabela[26][69] = make_tuple('V', 16);

    // Estado 27
    tabela[27][1] = make_tuple('E', 18);
    tabela[27][18] = make_tuple('E', 17);
    tabela[27][2] = make_tuple('E', 19);
    tabela[27][67] = make_tuple('V', 38);
    tabela[27][68] = make_tuple('V', 15);
    tabela[27][69] = make_tuple('V', 16);

    // Estado 28
    tabela[28][1] = make_tuple('E', 18);
    tabela[28][18] = make_tuple('E', 17);
    tabela[28][2] = make_tuple('E', 19);
    tabela[28][68] = make_tuple('V', 39);
    tabela[28][69] = make_tuple('V', 16);

    // Estado 29
    tabela[29][1] = make_tuple('E', 18);
    tabela[29][18] = make_tuple('E', 17);
    tabela[29][2] = make_tuple('E', 19);
    tabela[29][68] = make_tuple('V', 40);
    tabela[29][69] = make_tuple('V', 16);

    // Estado 30
    tabela[30][1] = make_tuple('E', 18);
    tabela[30][18] = make_tuple('E', 17);
    tabela[30][2] = make_tuple('E', 19);
    tabela[30][69] = make_tuple('V', 41);

    // Estado 31
    tabela[31][1] = make_tuple('E', 18);
    tabela[31][18] = make_tuple('E', 17);
    tabela[31][2] = make_tuple('E', 19);
    tabela[31][69] = make_tuple('V', 42);

    // Estado 32
    tabela[32][22] = make_tuple('E', 28);
    tabela[32][23] = make_tuple('E', 29);
    tabela[32][19] = make_tuple('E', 43);

    // Estado 33
    tabela[33][13] = make_tuple('R', 6);

    // Estado 34
    tabela[34][1] = make_tuple('E', 7);
    tabela[34][14] = make_tuple('E', 8);
    tabela[34][17] = make_tuple('E', 9);
    tabela[34][13] = make_tuple('R', 7);
    tabela[34][65] = make_tuple('V', 44);

    // Estado 35
    tabela[35][1] = make_tuple('R', 8);
    tabela[35][13] = make_tuple('R', 8);
    tabela[35][14] = make_tuple('R', 8);
    tabela[35][17] = make_tuple('R', 8);
    tabela[35][22] = make_tuple('E', 28);
    tabela[35][23] = make_tuple('E', 29);

    // Estado 36
    tabela[36][1] = make_tuple('R', 9);
    tabela[36][13] = make_tuple('R', 9);
    tabela[36][14] = make_tuple('R', 9);
    tabela[36][17] = make_tuple('R', 9);
    tabela[36][22] = make_tuple('E', 28);
    tabela[36][23] = make_tuple('E', 29);

    // Estado 37
    tabela[37][1] = make_tuple('R', 10);
    tabela[37][13] = make_tuple('R', 10);
    tabela[37][14] = make_tuple('R', 10);
    tabela[37][17] = make_tuple('R', 10);
    tabela[37][22] = make_tuple('E', 28);
    tabela[37][23] = make_tuple('E', 29);

    // Estado 38
    tabela[38][1] = make_tuple('R', 11);
    tabela[38][13] = make_tuple('R', 11);
    tabela[38][14] = make_tuple('R', 11);
    tabela[38][17] = make_tuple('R', 11);
    tabela[38][22] = make_tuple('E', 28);
    tabela[38][23] = make_tuple('E', 29);

    // Estado 39 - Reduções R12
    tabela[39][1] = make_tuple('R', 12);
    tabela[39][26] = make_tuple('R', 12);
    tabela[39][13] = make_tuple('R', 12);
    tabela[39][14] = make_tuple('R', 12);
    tabela[39][17] = make_tuple('R', 12);
    tabela[39][20] = make_tuple('R', 12);
    tabela[39][21] = make_tuple('R', 12);
    tabela[39][29] = make_tuple('R', 12);
    tabela[39][30] = make_tuple('R', 12);
    tabela[39][22] = make_tuple('R', 12);
    tabela[39][24] = make_tuple('E', 30);
    tabela[39][25] = make_tuple('E', 31);
    tabela[39][23] = make_tuple('R', 12);
    tabela[39][19] = make_tuple('R', 12);

    // Estado 40 - Reduções R13
    tabela[40][1] = make_tuple('R', 13);
    tabela[40][26] = make_tuple('R', 13);
    tabela[40][13] = make_tuple('R', 13);
    tabela[40][14] = make_tuple('R', 13);
    tabela[40][17] = make_tuple('R', 13);
    tabela[40][20] = make_tuple('R', 13);
    tabela[40][21] = make_tuple('R', 13);
    tabela[40][29] = make_tuple('R', 13);
    tabela[40][30] = make_tuple('R', 13);
    tabela[40][22] = make_tuple('R', 13);
    tabela[40][24] = make_tuple('E', 30);
    tabela[40][25] = make_tuple('E', 31);
    tabela[40][23] = make_tuple('R', 13);
    tabela[40][19] = make_tuple('R', 13);

    // Estado 41 - Reduções R15
    tabela[41][1] = make_tuple('R', 15);
    tabela[41][26] = make_tuple('R', 15);
    tabela[41][13] = make_tuple('R', 15);
    tabela[41][14] = make_tuple('R', 15);
    tabela[41][17] = make_tuple('R', 15);
    tabela[41][20] = make_tuple('R', 15);
    tabela[41][21] = make_tuple('R', 15);
    tabela[41][29] = make_tuple('R', 15);
    tabela[41][30] = make_tuple('R', 15);
    tabela[41][22] = make_tuple('R', 15);
    tabela[41][24] = make_tuple('R', 16);
    tabela[41][25] = make_tuple('R', 16);
    tabela[41][23] = make_tuple('R', 15);
    tabela[41][19] = make_tuple('R', 15);

    // Estado 42 - Reduções R16
    tabela[42][1] = make_tuple('R', 16);
    tabela[42][26] = make_tuple('R', 16);
    tabela[42][13] = make_tuple('R', 16);
    tabela[42][14] = make_tuple('R', 16);
    tabela[42][17] = make_tuple('R', 16);
    tabela[42][20] = make_tuple('R', 16);
    tabela[42][21] = make_tuple('R', 16);
    tabela[42][29] = make_tuple('R', 16);
    tabela[42][30] = make_tuple('R', 16);
    tabela[42][22] = make_tuple('R', 16);
    tabela[42][24] = make_tuple('R', 16);
    tabela[42][25] = make_tuple('R', 16);
    tabela[42][23] = make_tuple('R', 16);
    tabela[42][19] = make_tuple('R', 16);

    // Estado 43 - Reduções R18
    tabela[43][1] = make_tuple('R', 18);
    tabela[43][26] = make_tuple('R', 18);
    tabela[43][13] = make_tuple('R', 18);
    tabela[43][14] = make_tuple('R', 18);
    tabela[43][17] = make_tuple('R', 18);
    tabela[43][20] = make_tuple('R', 18);
    tabela[43][21] = make_tuple('R', 18);
    tabela[43][29] = make_tuple('R', 18);
    tabela[43][30] = make_tuple('R', 18);
    tabela[43][22] = make_tuple('R', 18);
    tabela[43][24] = make_tuple('R', 18);
    tabela[43][25] = make_tuple('R', 18);
    tabela[43][23] = make_tuple('R', 18);
    tabela[43][19] = make_tuple('R', 18);

    // Estado 44
    tabela[44][13] = make_tuple('R', 4);
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