#ifndef TABELA_SLR_H
#define TABELA_SLR_H

#include <string>
#include <tuple>
#include <vector>

// Global functions
extern std::vector<std::vector<std::tuple<char, int>>> tabela;
void initializeSLRTable();
std::vector<std::tuple<int, int>> getProducoes();

#endif // TABELA_SLR_H 

/*


*/
