#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <ctype.h>
#include <stack>
#include <queue>
#include <sstream>

#include "tabela_slr.h"
#include "AbstractSyntaxTree.h"
#include "ASTTypes.h"

using namespace std;

void printEstadoVariaveis(stack<int>& pilha, queue<int>& fita);
void addWord(int *word, int *row, int wrow);

void slr(string fitaString, vector<tuple<vector<string>, string>> tapeTable) {
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

    AbstractSyntaxTree ast;

    vector<tuple<int, int>> producoes = getProducoes();
    int wordIndex = 0, rowIndex = 0;
    initializeSLRTable();
    while (1) {
        // printEstadoVariaveis(pilha, fita);
        int estado = pilha.top();
        int simbolo = fita.front();
        if (get<0>(tabela[estado][simbolo]) == 'E') {
            int proximo_estado = get<1>(tabela[estado][simbolo]);
            pilha.push(simbolo);
            pilha.push(proximo_estado);
            fita.pop();
            
            string lexval = get<0>(tapeTable[rowIndex])[wordIndex];

            addWord(&wordIndex, &rowIndex, size(get<0>(tapeTable[rowIndex])));
            Lex l = {lexval};
            ast.MakeLeaf(l);
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

            ast.MakeNode(reduzProducao);
            continue;
        }

        if (get<0>(tabela[estado][simbolo]) == 'A') {
            printf("\033[1;32mPassed syntactic analysis\033[0m\n\n");
            break;
        }

        if (get<0>(tabela[estado][simbolo]) == '\0') {
            printf("\033[1;31mFailed syntactic analysis\033[0m\n\n");
            return;
        } 
    }

    ast.printResult();
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

void addWord(int *word, int *row, int wrow){
    if ((*word + 1) < wrow){
        (*word)++;
        return ;
    } 

    *word = 0;
    (*row)++;
    return;
}