/**
 * @file main.c
 * @author Pedro Simões / João Apresentaçao
 * @email: a21140@alunos.ipca.pt / a21152@alunos.ipca.pt
 * @brief Programa que gere pecas LEGO, tendo as funcionalidades de pesquisa de peças, contagem e mesmo
 * listagem das mesmas. Permite também apresentar alguns resultados estatisticos em relacao as peças e conjuntos presentes no inventario
 * @version 0.1
 * @date 2021-03-29
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

/**
 * @brief Funcao main
 * 
 * @return int 
 */
int main(){
    Parts *listParts = NULL;
    Parts_Sets *listPartsSets = NULL;
    Sets *listSets = NULL;

    listParts = lerParts(listParts);
    listPartsSets = lerPartsSets(listPartsSets);
    listSets = lerSets(listSets);

    Menu(&listParts, &listPartsSets, &listSets);
    destroyAll(listParts, listPartsSets, listSets);

    return 0;
}