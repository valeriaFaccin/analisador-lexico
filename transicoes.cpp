#include <vector>
#include <unordered_map>
#include "transicoes.h"

using namespace std;
vector<unordered_map<char, int>> transicoes;

void inicializaTransicoes(){
    transicoes = vector<unordered_map<char, int>>(32);

    vector<char> caracteres = {'0', '1', 'a', 'b', 'd', 'e', 'f', 'g', 'i', 'n', 'o', 'r', 't', 'u', '<', '>', '+', '-', '*', '/', ';', '(', ')', '=', '!', ' ', '\n'};
    
    // Inicializa todas as transições para o estado de erro (31)
    for (char c : caracteres) {
        for (int i = 0; i < 32; i++) 
            transicoes[i][c] = 31;
    }

    // Estado S (0)
    transicoes[0]['0'] = 2;
    transicoes[0]['1'] = 2;
    transicoes[0]['a'] = 1;
    transicoes[0]['b'] = 3;
    transicoes[0]['e'] = 11;
    transicoes[0]['f'] = 15;
    transicoes[0]['i'] = 8;
    transicoes[0]['o'] = 1;
    transicoes[0]['u'] = 1;
    transicoes[0]['<'] = 20;
    transicoes[0]['>'] = 21;
    transicoes[0]['+'] = 22;
    transicoes[0]['-'] = 23;
    transicoes[0]['*'] = 24;
    transicoes[0]['/'] = 25;
    transicoes[0][';'] = 26;
    transicoes[0]['('] = 18;
    transicoes[0][')'] = 19;
    transicoes[0]['='] = 27;
    transicoes[0]['!'] = 28;
    transicoes[0][' '] = 0;
    transicoes[0]['\n'] = 0;

    // Estado 1 (estado de aceitação para identificadores)
    transicoes[1]['0'] = 1;
    transicoes[1]['1'] = 1;
    transicoes[1]['a'] = 1;
    transicoes[1]['e'] = 1;
    transicoes[1]['i'] = 1;
    transicoes[1]['o'] = 1;
    transicoes[1]['u'] = 1;

    // Estado 2 (estado de aceitação para números)
    transicoes[2]['0'] = 2;
    transicoes[2]['1'] = 2;

    // Estado 3 (começo de 'begin')
    transicoes[3]['e'] = 4;

    // Estado 4
    transicoes[4]['g'] = 5;

    // Estado 5
    transicoes[5]['i'] = 6;

    // Estado 6
    transicoes[6]['n'] = 7;

    // Estado 8 (começo de 'if' e 'int')
    transicoes[8]['0'] = 1;
    transicoes[8]['1'] = 1;
    transicoes[8]['a'] = 1;
    transicoes[8]['e'] = 1;
    transicoes[8]['f'] = 14;
    transicoes[8]['i'] = 1;
    transicoes[8]['n'] = 9;
    transicoes[8]['o'] = 1;
    transicoes[8]['u'] = 1;

    // Estado 9 (final de int)
    transicoes[9]['t'] = 10;

    // Estado 11 (começo de 'end')
    transicoes[11]['0'] = 1;
    transicoes[11]['1'] = 1;
    transicoes[11]['a'] = 1;
    transicoes[11]['e'] = 1;
    transicoes[11]['i'] = 1;
    transicoes[11]['n'] = 12;
    transicoes[11]['o'] = 1;
    transicoes[11]['u'] = 1;

    // Estado 12
    transicoes[12]['d'] = 13;

    // Estado 15 (começo de 'for')
    transicoes[15]['o'] = 16;

    // Estado 16
    transicoes[16]['r'] = 17;

    // Estado 27 (=)
    transicoes[27]['='] = 29;

    // Estado 28 (!)
    transicoes[28]['='] = 30;
}
