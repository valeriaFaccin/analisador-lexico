#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <ctype.h>
#include <stack>
#include <queue>
#include <sstream>
#include "tabela_slr.h"

using namespace std;

void printEstadoVariaveis(stack<int>& pilha, queue<int>& fita);
void addPalavra(int *palavra, int *linha, int pLinha);

void slr(string fitaString, vector<tuple<vector<string>, string>> tabelafita) {
    stack<int> pilha;
    pilha.push(0);

    queue<int> fita;
    stringstream ss(fitaString);
    string token;
    while (ss >> token) {
        int tokenInt = stoi(token);
        // o token var valida no estado 8 e 11, convertendo para 1
        if (tokenInt == 8 || tokenInt == 11) tokenInt = 1;

        fita.push(tokenInt);
    }

    vector<tuple<int, int>> producoes = getProducoes();
    int indicePalavra = 0, indiceFrase = 0;
    initializeSLRTable();
    while (1) {
        printEstadoVariaveis(pilha, fita);
        int estado = pilha.top();
        int simbolo = fita.front();
        printf("Estado: %d, Simbolo: %d\n", estado, simbolo);
        if (get<0>(tabela[estado][simbolo]) == 'E') {
            int proximo_estado = get<1>(tabela[estado][simbolo]);
            pilha.push(simbolo);
            pilha.push(proximo_estado);
            fita.pop();
            
            continue;
        }

        if (get<0>(tabela[estado][simbolo]) == 'R') {
            int reduzProducao = get<1>(tabela[estado][simbolo]);
            tuple<int, int> producao = producoes[reduzProducao];
            
            int tamanho = get<1>(producao) * 2;
            for (int i = 0; i < tamanho; i++) {
                pilha.pop();
            }

            estado = pilha.top();
            int cabecaProducao = get<0>(producao);
            pilha.push(cabecaProducao);
            pilha.push(get<1>(tabela[estado][cabecaProducao]));

            continue;
        }

        if (get<0>(tabela[estado][simbolo]) == 'A') {
            printf("Aceito\n");
            return;
        }

        if (get<0>(tabela[estado][simbolo]) == '\0') {
            printf("Rejeitado na etapa léxica\n");
            return;
        } 
    }
}

void printEstadoVariaveis(stack<int>& pilha, queue<int>& fita) {
    printf("Fita: ");
    queue<int> temp = fita;
    while (!temp.empty()) {
        printf("%d ", temp.front());
        temp.pop();
    }
    printf("\n");

    printf("Pilha: ");
    stack<int> temp_pilha = pilha;
    while (!temp_pilha.empty()) {
        printf("%d ", temp_pilha.top());
        temp_pilha.pop();
    }
    printf("\n");
}

void addPalavra(int *palavra, int *linha, int pLinha){
    if (*palavra + 1 < plinha){
        *palavra++
        return ;
    } 

    *palavra++;
    *linha++;
    return;
}