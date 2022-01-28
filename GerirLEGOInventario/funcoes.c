/**
 * @file funcoes.c
 * @author Pedro Simões / João Apresentaçao
 * @email: a21140@alunos.ipca.pt / a21152@alunos.ipca.pt
 * @brief Ficheiro .c que contem as funcoes necessarias para correr o programa
 * @version 0.1
 * @date 2021-03-29
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "funcoes.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * @brief Region que contém funcoes de inserçao de nodos em listas
 * 
 * @param list 
 * @return Parts* 
 */
#pragma region leituras

/**
 * @brief Funcao que le o ficheiro parts.tsv e guarda seus dados em memoria
 * 
 * @param list 
 * @return Parts* 
 */
Parts* lerParts(Parts *list){
    FILE* parts = fopen("parts.tsv", "r");

    char buffer[60];

    Parts *aux = (Parts*) malloc(sizeof(Parts));
    aux->name = malloc(200);
    aux->part_num = malloc(50);
    aux->class = malloc(50);

    fscanf(parts,"%[^\n]", buffer);

    //enquanto nao chega ao fim da file (incrementa uma linha)
    while(!feof(parts)){
        fscanf(parts, "\n%[^\t]\t%[^\t]\t%[^\t]\t%d", aux->part_num, aux->name, aux->class, &aux->stock);
        list = head_insert_parts(list, aux);
    }

    free(aux);
    fclose(parts);
    //retorna cabeca
    return list;
}

/**
 * @brief Funcao que le o ficheiro parts_sets.tsv e guarda seus dados em memoria
 * 
 * @param list 
 * @return Parts_Sets* 
 */
Parts_Sets* lerPartsSets(Parts_Sets *list){
    FILE* part_sets = fopen("parts_sets.tsv", "r");
    char buffer[60];
    
    //aux para ser usado para percorrer array e "guardar" posicoes para manipular next e previous
    //new_node junta-se à lista
    Parts_Sets *aux = (Parts_Sets*) malloc(sizeof(Parts_Sets));
    aux->part_num = malloc(50);
    aux->set_num = malloc(50);

    //Caso dê erro a abrir o ficheiro
    fscanf(part_sets, "%[^\n]", buffer);

    //enquanto nao chega ao fim da file (incrementa uma linha)
    while(!feof(part_sets)){
        fscanf(part_sets, "\n%[^\t]\t%d\t%[^\n]", aux->set_num , &aux->quantity, aux->part_num);
        list = head_insert_partsSets(list, aux);
    }

    free(aux);
    fclose(part_sets);
    //retorna cabeca
    return list;
}

/**
 * @brief Funcao que le o ficheiro sets.tsv e guarda seus dados em memoria
 * 
 * @param list 
 * @return Sets* 
 */
Sets* lerSets(Sets *list){
    FILE* sets = fopen("sets.tsv", "r");

    //buffer para a primeira linha
    char buffer[60];
    
    Sets *aux = (Sets*) malloc(sizeof(Sets));
    aux->name = malloc(85);
    aux->set_num = malloc(50);
    aux->theme = malloc(50);

    //Caso dê erro a abrir o ficheiro
    if (!sets)
    {
        printf("Erro em leitura de ficheiro/os\n");
        return list;
    }

    fscanf(sets, "%[^\n]", buffer);

    //enquanto nao chega ao fim da file (incrementa uma linha)
    while(!feof(sets)){
            fscanf(sets, "\n%[^\t]\t%[^\t]\t%d\t%[^\n]", aux->set_num, aux->name, &aux->year, aux->theme);
            list = head_insert_sets(list, aux);
    }

    
    free(aux);
    fclose(sets);
    //retorna cabeca
    return list;
}

#pragma endregion

/**
 * @brief Região que contem funcoes de inserçao à cabeça de cada lista
 * 
 */
#pragma region inserts

/**
 * @brief Funcao que insere um nodo na lista a partir da cabeça (Lista Parts)
 * 
 * @param list 
 * @param aux -> novo nodo
 * @return Parts* 
 */
Parts* head_insert_parts(Parts *list, Parts* aux){
    //allocar memoria para novo nodo
    Parts *new_aux = (Parts*) malloc(sizeof(Parts));

    //Passar a informacao do aux para o novo nodo
    new_aux->part_num = strdup(aux->part_num);
    new_aux->name = strdup(aux->name);
    new_aux->class = strdup(aux->class);
    new_aux->stock = aux->stock;

    //apontador next do novo nodo liga-se à lista
    new_aux->next = list;
    
    //Se nao for nulo
    if (new_aux->next)
        //O anterior do proximo aponta para o atual novo node
        new_aux->next->previous = new_aux;

    new_aux->previous = NULL;
    
    //Retorna nova cabeca
    return new_aux;
}

/**
 * @brief Funcao que insere um nodo na lista a partir da cabeça (Lista Parts_Sets)
 * 
 * @param list 
 * @param aux 
 * @return Parts_Sets* 
 */
Parts_Sets* head_insert_partsSets(Parts_Sets *list, Parts_Sets* aux){
    Parts_Sets *new_aux = (Parts_Sets*) malloc(sizeof(Parts_Sets));

    new_aux->part_num = strdup(aux->part_num);
    new_aux->set_num = strdup(aux->set_num);
    new_aux->quantity = aux->quantity;

    //apontador next do novo nodo liga-se à lista
    new_aux->next = list;

    //Se nao for nulo
    if (new_aux->next)
        //O anterior do proximo aponta para o atual novo node
        new_aux->next->previous = new_aux;

    new_aux->previous = NULL;

    //Retorna nova cabeca
    return new_aux;
}

/**
 * @brief Funcao que insere um nodo na lista a partir da cabeça (Lista Sets)
 * 
 * @param list 
 * @param aux 
 * @return Sets* 
 */
Sets* head_insert_sets(Sets *list, Sets* aux){
    Sets *new_aux = (Sets*) malloc(sizeof(Sets));

    new_aux->name = strdup(aux->name);
    new_aux->theme = strdup(aux->theme);
    new_aux->set_num = strdup(aux->set_num);
    new_aux->year = aux->year;
    //apontador next do novo nodo liga-se à lista
    new_aux->next = list;

    //Se nao for nulo
    if (new_aux->next)
        //O anterior do proximo aponta para o atual novo node
        new_aux->next->previous = new_aux;

    new_aux->previous = NULL;

    //Retorna nova cabeca
    return new_aux;
}

/**
 * @brief Funcao que adiciona novo nodo à lista por ordem crescente do ano
 * 
 * @param list 
 * @param year 
 * @return Sets* 
 */
Sets *insert_ordemAno(Sets *new_list, Sets *aux)
{
    Sets *new_node = (Sets *)malloc(sizeof(Sets));

    new_node->name = strdup(aux->name);
    new_node->theme = strdup(aux->theme);
    new_node->set_num = strdup(aux->set_num);
    new_node->year = aux->year;
    new_node->next = new_node->previous = NULL;

    //Se a lista estiver vazia ou o nodo atual tiver um ano maior que o ano da referencia
    if (!new_list || new_list->year < aux->year)
    {
        new_node->next = new_list;
        new_list = new_node;
        if (new_list->next)
        {
            new_list->next->previous = new_list;
        }
    }
    //Se nao for o caso (ser o maior da lista inteira, será o ultimo)
    else
    {
        Sets *aux = new_list;
        for(;aux->next && aux->next->year > aux->year; aux = aux->next){}
        new_node->next = aux->next;
        new_node->previous = aux;
        aux->next = new_node;
        if (new_node->next)
        {
            new_node->next->previous = new_node;
        }
    }

    //retornar a cabeca da lista
    return new_list;
}

/**
 * @brief Funcao que insere nodos de forma crescente do part_num numa lista do tipo Parts_Sets
 * 
 * @param new_list 
 * @param aux 
 * @return Parts_Sets* 
 */
Parts_Sets* insert_ordemPartNum(Parts_Sets* new_list, Parts_Sets* aux){
    Parts_Sets* new_node = malloc(sizeof(Parts_Sets));

    new_node->set_num = strdup(aux->set_num);
    new_node->part_num = strdup(aux->part_num);
    new_node->quantity = aux->quantity;
    new_node->next = new_node->previous = NULL;

    if(!new_list || new_list->part_num < aux->part_num){
        new_node->next = new_list;
        new_list = new_node;
        if(new_list->next){
            new_list->next->previous = new_list;
        }
    }
    else{

        Parts_Sets *aux = new_list;

        for(;aux->next && aux->next->part_num > aux->part_num; aux = aux->next){}
        
        new_node->next = aux->next;
        new_node->previous = aux;
        aux->next = new_node;
        if (new_node->next)
        {
            new_node->next->previous = new_node;
        }
    }

    return new_list;
}

#pragma endregion

/**
 * @brief Region que limpa listas da memoria
 * 
 */
#pragma region destroys

/**
 * @brief Liberta memoria ocupada antes por uma lista Parts
 * 
 * @param list 
 */
void destroyParts(Parts* list) {
    //Aux para guardar temporariamente apontadores
    Parts* aux = malloc(sizeof(Parts));

    //Limpar nodo a nodo até sobrar apenas o aux
    for(;list;list = aux){
        aux = list->next;
        free(list);
    }
    
    //Limpar aux
    free(aux);
}

/**
 * @brief Liberta memoria ocupada antes por uma lista Parts_Sets
 * 
 * @param list 
 */
void destroyPartsSets(Parts_Sets* list) {
    Parts_Sets* aux = malloc(sizeof(Parts_Sets));
    for(;list;list = aux){
        aux = list->next;
        free(list);
    }
    
    free(aux);
}

/**
 * @brief Liberta memoria ocupada antes por uma lista Sets
 * 
 * @param list 
 */
void destroySets(Sets* list) {
    Sets* aux = malloc(sizeof(Sets));
    for(;list;list = aux){
        aux = list->next;
        free(list);
    }
    
    free(aux);
}

/**
 * @brief Liberta a memora de todas as listas usadas
 * 
 * @param list1 
 * @param list2 
 * @param list3 
 */
void destroyAll(Parts* list1, Parts_Sets* list2, Sets* list3){
    destroyParts(list1);
    destroyPartsSets(list2);
    destroySets(list3);
}

#pragma endregion

/**
 * @brief region que contem os menus para a navegacao no programa, obtencao de selecao do utilizador e execucao de funcoes a partir de cada menu
 * 
 */
#pragma region MENUS

/**
 * @brief Mostra texto do menu principal
 * 
 */
void MenuTexto()
{
    system("cls");
    printf("------------------------------------------------------------------");
    printf("\nMENU:\n [1]-Menu stock\n [2]-Conjuntos de determinado tema\n [3]-Pecas de um tipo em um conjunto");
    printf("\n [4]-Quais pecas para determinado conjunto\n [5]-Total de pecas num conjunto\n [6]-Peca mais utilizada");
    printf("\n [7]-Lista de conjuntos possiveis de se construir com stock atual\n [8]-Mostrar Parts\n [9]-Mostrar PartSets\n [10]-Mostrar Sets\n [0]-SAIR");
    printf("\n------------------------------------------------------------------");
    printf("\n\nOPCAO ===> ");
}

/**
 * @brief Recebendo a opcao da funcao Menu(), executa a funcao respetiva a essa opcao
 * 
 * @param op 
 * @param listParts 
 * @param listPartsSets 
 * @param listSets 
 */
void Menu(Parts **listParts, Parts_Sets **listPartsSets, Sets **listSets)
{
    int op;

    MenuTexto();
    scanf("%d", &op);

    while(op != 0){

        switch (op)
        {
        case 0:
            break;
        case 1:
            system("cls");
            MenuStock(listParts, listPartsSets, listSets);
            break;

        case 2:
            system("cls");
            showSets_themeOrd_year(*listSets, getTheme(listSets));
            printf("\n\n(Pressione qualquer botao para sair)");
            getchar();
            break;

        case 3:
            system("cls");
            char *set_num = getSetNum(listSets);
            partsByClassInSets(*listParts, *listPartsSets, set_num, getClass(listParts));
            printf("\n\n(Pressione qualquer botao para sair)");
            getchar();
            break;

        case 4:
            system("cls");
            pecasConstroiSet(*listParts, *listPartsSets, getSetNum(listSets));
            printf("\n\n(Pressione qualquer botao para sair)");
            getchar();
            break;

        case 5:
            system("cls");
            printf("\nTotal de pecas neste conjunto: %d", totalPartsInSet(*listParts, *listPartsSets, getSetNum(listSets)));
            printf("\n\n(Pressione qualquer botao para sair)");
            getchar();
            break;

        case 6:
            system("cls");
            PecaMaisUsada(*listPartsSets, *listParts);
            getchar();
            printf("\n\n(Pressione qualquer botao para sair)");
            getchar();
            break;
            
        case 7:
            system("cls");
            setsPossiveis(*listParts, *listPartsSets, *listSets);
            getchar();
            printf("\n\n(Pressione qualquer botao para sair)");
            getchar();
            break;

        case 8:
            system("cls");
            mostraListaParts(*listParts);
            getchar();
            printf("\n\n(Pressione qualquer botao para sair)");
            getchar();
            break;
        case 9:
            system("cls");
            mostraListaPartsSets(*listPartsSets);
            getchar();
            printf("\n\n(Pressione qualquer botao para sair)");
            getchar();
            break;
        case 10:
            system("cls");
            mostraListaSets(*listSets);
            printf("\n\n(Pressione qualquer botao para sair)");
            fflush(stdin);
            getchar();
            getchar();
            break;
        default:
            printf("\nOpcao Invalida!\nIntroduza novamente!\n\n");
            break;
        }

        MenuTexto();
        scanf("%d", &op);
    }
    
}

/**
 * @brief Texto que aparece no menu secundario
 * 
 */
void MenuStockTexto()
{
    system("cls");
    printf("----------------------");
    printf("\nMENU STOCK:\n [1]-Alterar numero de pecas\n [2]-Adicionar com base no identificador de um conjunto\n [3]-Remover todas as pecas de uma classe");
    printf("\n [4]-Remover todos os sets de determinado tema\n [5]-Total de pecas\n [0]-RETROCEDER");
    printf("\n----------------------");
    printf("\n\nOPCAO ===> ");
}

/**
 * @brief Recebendo a opcao da funcao MenuStock(), executa a funcao respetiva à opcao
 * 
 * @param op 
 * @param listParts 
 * @param listPartsSets 
 * @param listSets 
 */
void MenuStock(Parts **listParts, Parts_Sets **listPartsSets, Sets **listSets)
{
    int op;

    MenuStockTexto();
    scanf("%d", &op);

    while (op != 0)
    {

        fflush(stdin);
        switch (op)
        {
        case 0:
            break;
        case 1:
            system("cls");
            changeStock(*listParts, getPartNum(listParts));
            printf("\n\nStock alterado com sucesso!");
            getchar();
            printf("\n\n(Pressione qualquer botao para sair)");
            getchar();
            break;

        case 2:
            system("cls");
            addFullSet(*listParts,*listPartsSets, getSetNum(listSets));
            printf("\n\nStock alterado com sucesso!");
            printf("\n\n(Pressione qualquer botao para sair)");
            getchar();
            break;

        case 3:
            system("cls");
            //Guarda '\n' inserido
            getchar();

            *listParts = removeAllPartsByClass(*listParts, getClass(listParts));
            printf("\n\n(Pressione qualquer botao para sair)");
            getchar();
            break;

        case 4:
            system("cls");
            *listSets = removeAllSetsByTheme(*listSets, listPartsSets, getTheme(listSets));
            printf("\n\n(Pressione qualquer botao para sair)");
            getchar();
            break;

        case 5:
            system("cls");
            printf("Numero total de pecas em stock: %d", totalParts(*listParts));
            getchar();
            printf("\n\n(Pressione qualquer botao para sair)");
            getchar();
            break;
        default:
            printf("\nOpcao Invalida!\nIntroduza novamente!\n\n");
            break;
        }

        MenuStockTexto();
        scanf("%d", &op);
    }
}

#pragma endregion

/**
 * @brief Region que mostra as listas completas
 * 
 */
#pragma region Listagens

/**
 * @brief Funcao que mostra lista do tipo Parts
 * 
 * @param list 
 */
void mostraListaParts(Parts* list){
    while (list)
    {
        printf("part_num: %s / name: %s / class: %s / stock: %d\n",list->part_num, list->name, list->class, list->stock);
        list = list->next;
        
    }
}

/**
 * @brief Funcao que mostra lista do tipo PartsSets
 * 
 * @param list 
 */
void mostraListaPartsSets(Parts_Sets* list){
    
    while (list)
    {
        printf("set_num: %s / quantity: %d /  part_num: %s\n", list->set_num, list->quantity, list->part_num);
        list = list->next;
    }
}

/**
 * @brief Funcao que mostra lista do tipo Sets
 * 
 * @param list 
 */
void mostraListaSets(Sets *list)
{
    while (list)
    {
        printf("set_num: %s / name: %s / year: %d / theme: %s\n", list->set_num, list->name, list->year, list->theme);
        list = list->next;
    }
}

#pragma endregion

/**
 * @brief Region que contém funçoes que obtem dados do utilizador, pedidos pelo programa
 * 
 */
#pragma region LerInputUser

/**
 * @brief Obtem input do utilizador e verifica se o set_num inserido existe na lista
 * 
 * @param list 
 * @return char* 
 */
char* getSetNum(Sets** list){
    int valido = 1;
    char *buffer = malloc(200);
    //Para guardar apontador inicial
    Sets* cabeca = malloc(sizeof(Sets));
    //Guarda o '\n' das opcoes do menu ao pressionar Enter
    getchar();

    //Enquanto nao introduzir um set_num que esteja contido na lista, repetirá a pergunta
    do
    {
        cabeca = *list;
        printf("Insira o set_num pretendido: ");
        fgets(buffer, 200, stdin);
        buffer[strlen(buffer) - 1] = '\0';

        while (cabeca)
        {
            if(strcmp(buffer, cabeca->set_num) == 0){
                return buffer;
            }

            cabeca = cabeca->next;
        }
        printf("\nInseriu set_num errado!\n");
    } while(valido == 1);

    return NULL;
}

/**
 * @brief Obtem input do utilizador e verifica se a classe inserida existe na lista
 * 
 * @param list 
 * @return char* 
 */
char* getClass(Parts **list){
    int valido = 1;
    char *buffer = malloc(65);
    Parts* cabeca = malloc(sizeof(Parts));
    //Guarda o '\n' das opcoes do menu ao pressionar Enter
    
    do
    {
        cabeca = *list;
        printf("Insira a classe pretendida: ");
        fgets(buffer, 65, stdin);
        buffer[strlen(buffer) - 1] = '\0';

        while (cabeca)
        {
            if(strcmp(buffer, (cabeca)->class) == 0){
                return buffer;
            }

            cabeca = cabeca->next;
        }
        printf("\nInseriu uma classe inexistente!\n");
    }while(valido == 1);

    return NULL;
}

/**
 * @brief Obtem input do utilizador e verifica se o part_num inserido existe na lista
 * 
 * @param list 
 * @return char* 
 */
char* getPartNum(Parts** list){
    int valido = 1;
    char *buffer = malloc(30);
    Parts* cabeca = malloc(sizeof(Parts));
    //Guarda o '\n' das opcoes do menu ao pressionar Enter
    getchar();

    do    
    {
        cabeca = *list;
        printf("Insira o part_num pretendido: ");
        fgets(buffer, 30, stdin);
        buffer[strlen(buffer) - 1] = '\0';

        while (cabeca)
        {
            if(strcmp(buffer, (cabeca)->part_num) == 0){
                return buffer;
            }

            cabeca = cabeca->next;
        }
        printf("\nInseriu part_num errado!\n");
    }while(valido == 1);

    return NULL;
}

/**
 * @brief Obtem input do utilizador e verifica se o tema inserido existe na lista
 * 
 * @param list 
 * @return char* 
 */
char* getTheme(Sets** list){
    int valido = 1;
    char *buffer = malloc(150);
    Sets* cabeca = malloc(sizeof(Sets));
    //Guarda o '\n' das opcoes do menu ao pressionar Enter
    getchar();
    
    do
    {
        cabeca = *list;
        printf("Insira a tema pretendida: ");
        fgets(buffer, 150, stdin);
        buffer[strlen(buffer) - 1] = '\0';

        while (cabeca)
        {
            if(strcmp(buffer, (cabeca)->theme) == 0){
                return buffer;
            }

            cabeca = cabeca->next;
        }
        printf("\nInseriu um tema inexistente!\n");
    }while(valido == 1);

    return NULL;
}

#pragma endregion

/**
 * @brief Region que contem restantes funcoes com diversas funcionalidades de listagens e calculos
 * 
 */
#pragma region Funcoes

/**
 * @brief Mostrar todos os conjuntos de um certo tema (neste caso por ordem do ano acrescente)
 * 
 * @param list 
 * @param tema 
 */
void showSets_themeOrd_year(Sets *list, char tema[])
{
    //Nova lista que armazena todos os conjuntos de certo tema e seus dados
    Sets *new_listSets = NULL, *aux = (Sets*) malloc(sizeof(Sets));
    aux->name = malloc(85);
    aux->set_num = malloc(50);
    aux->theme = malloc(50);
    
    //Enquanto lista nao acabar (rever strcmp se esta correto)
    while (list)
    {   
        //Se tema for encontrado
        if (strcmp(list->theme, tema) == 0)
        {           
            strcpy(aux->name, list->name);
            strcpy(aux->theme, list->theme);
            strcpy(aux->set_num, list->set_num);
            aux->year = list->year;
            
            //Inserir conjunto na lista de forma ordenada por ano
            new_listSets = insert_ordemAno(new_listSets, aux);
        }
        
        //Avancar na lista
        list = list->next;
    }

    free(aux);
    //Mostrar lista nova com todos os conjuntos do tema pedido
    mostraListaSets(new_listSets);
    destroySets(new_listSets);
}

/**
 * @brief Funcao que mostra as peças de uma determinada classe que estao contidas num determinado conjunto
 * 
 * @param listParts 
 * @param listPartsSets 
 * @param set_num 
 */
void partsByClassInSets(Parts *listParts, Parts_Sets *listPartsSets, char set_num[], char class[]){
    int counter = 0, quebraParts = 0;
    
    //Correr lista PartsSets
    for(;listPartsSets && quebraParts == 0; listPartsSets = listPartsSets->next)
    {
        //Set_Num compativel com o inserido
        if(strcmp(set_num, listPartsSets->set_num) == 0){
            //Correr lista Parts
            for(;listParts && quebraParts == 0; listParts = listParts->next){
                //Part_num compativel com o pertencente ao conjunto
                if(strcmp(listParts->part_num, listPartsSets->part_num) == 0){
                    //verificar se a classe dessa peça é igual à classe inserida
                    if(strcmp(listParts->class, class) == 0){
                        //Lista informacao da peça
                        counter++;
                        if(counter == 1){
                            printf("\n\nPecas da class inserida deste conjunto: ");
                            printf("\n\npart_num: %s / name: %s / class: %s / stock: %d\n",listParts->part_num, listParts->name, listParts->class, listParts->stock);
                        }
                        else{
                            printf("part_num: %s / name: %s / class: %s / stock: %d\n",listParts->part_num, listParts->name, listParts->class, listParts->stock);
                        }
                        //Para de percorrer lista Parts
                        quebraParts = 1;
                    }
                }
            }
        }
    }

    //Caso nao haja uma peça dessa classe do conjunto inserido
    if(counter == 0) printf("\nNenhum resultado encontrado!");
}

/**
 * @brief Funcao que lista peças necessarias para construir um conjunto inserido
 * 
 * @param listParts 
 * @param listPartsSets 
 * @param set_num 
 */
void pecasConstroiSet(Parts* listParts, Parts_Sets *listPartsSets, char set_num[]){
    int counter = 0, quebraParts = 0;

    //Corre lista Parts_Sets
    for(;listPartsSets; listPartsSets = listPartsSets->next)
    {
        //Set_Num compativel com o inserido
        if(strcmp(set_num, listPartsSets->set_num) == 0){
            //Corre lista Parts
            for(;listParts && quebraParts == 0; listParts = listParts->next){
                //Part_num compativel com o pertencente ao conjunto
                if(strcmp(listParts->part_num, listPartsSets->part_num) == 0){
                    counter++;
                    if(counter == 1){
                        printf("\n\nPecas necessarias para este conjunto: ");
                        printf("\n\npart_num: %s / name: %s / class: %s / stock: %d\n",listParts->part_num, listParts->name, listParts->class, listParts->stock);
                    }
                    else{
                        printf("part_num: %s / name: %s / class: %s / stock: %d\n",listParts->part_num, listParts->name, listParts->class, listParts->stock);
                    }

                    //Para de correr Parts
                    quebraParts = 1;
                }
            }
        }
    }

    //Caso conjunto nao tenha qualquer peça
    if(counter == 0) printf("\nO conjunto nao necessita de peças");
}

/**
 * @brief Funcao que retorna numero total de peças no inventário
 * 
 * @param list 
 * @return int 
 */
int totalParts(Parts* list)
{
    int counter = 0;

    while (list)
    {
        counter += list->stock;
        list = list->next;
    }
    if(counter == 0) printf("\n\nInventario vazio!");
    
    return counter;
}

/**
 * @brief Funcao que retorna o numero total de peças necessarias para um conjunto inserido
 * 
 * @param listParts 
 * @param listPartsSets 
 * @param set_num 
 * @return int 
 */
int totalPartsInSet(Parts* listParts, Parts_Sets* listPartsSets, char set_num[])
{
    int counter = 0;

    for(;listPartsSets; listPartsSets = listPartsSets->next)
    {
        if(strcmp(set_num, listPartsSets->set_num) == 0){
            counter += listPartsSets->quantity;
        }
    }
    if(counter == 0) printf("\n\nEste conjunto nao tem pecas");

    return counter;
}

/**
 * @brief Modifica o stock de uma peça inserida pelo utilizador
 * 
 * @param list 
 * @param part_num 
 * @return int 
 */
void changeStock(Parts* list, char part_num[]){
    int pecas, quebra = 0;

    for(;list && quebra == 0;list = list->next){
        if(strcmp(part_num, list->part_num) == 0){
            printf("\n\nStock atual da peca %s: %d", list->name, list->stock);

            do{
                printf("\nAlterar stock para: ");
                scanf("%d", &pecas);
            } while(pecas < 0);

            list->stock = pecas;
            quebra = 1;
        }
    }
}

/**
 * @brief Adiciona 1 ao stock de cada peça necessaria para o conjunto seguinte
 * 
 * @param list 
 * @param partsSetslists 
 * @param set_num 
 */
void addFullSet(Parts *list, Parts_Sets *partsSetslists, char set_num[]){
    int quebraParts = 0;

    for(;partsSetslists; partsSetslists = partsSetslists->next){
        if(strcmp(partsSetslists->set_num, set_num) == 0){
            for(;list && quebraParts == 0;list = list->next){
                if(strcmp(list->part_num, partsSetslists->part_num) == 0)
                {
                    list->stock += partsSetslists->quantity;
                    quebraParts= 1;
                }
            }
        }
    }
}

/**
 * @brief Funcao que calcula a peça mais usada em sets diferentes
 * 
 * @param listPartsSets 
 * @param listParts 
 */
void PecaMaisUsada(Parts_Sets *listPartsSets, Parts *listParts)
{
    int maior = 0, counter;
    Parts_Sets* cabeca;
    Parts* aux = malloc(sizeof(Parts));

    //Percorrer lista de peças
    for(;listParts; listParts = listParts->next){
        counter = 0;

        //Percorrer lista de partsSets com o apontador cabeça
        for(cabeca = listPartsSets; cabeca; cabeca = cabeca->next){ 
            //Se achar a peça, se estiver no mesmo conjunto do next e caso nao se repita no mesmo conjunto, incrementa o contador
            if(cabeca->next && (strcmp(listParts->part_num, cabeca->part_num) == 0 && strcmp(cabeca->set_num, cabeca->next->set_num) == 0
                && strcmp(cabeca->part_num, cabeca->next->part_num) != 0))
                counter++;
        }

        //Verificacao de maior, caso seja, guardar dados dessa peça e o respetivo contador
        if (maior < counter){
            maior = counter;

            free(aux->name);
            free(aux->class);
            free(aux->part_num);

            aux->name = strdup(listParts->name);
            aux->class = strdup(listParts->class);
            aux->part_num = strdup(listParts->part_num);
            aux->stock = listParts->stock;
        }

    }

    printf("\n\nDados acerca da peca mais utilizada em conjuntos diferentes:\n\n");
    printf("part_num: %s / name: %s / class: %s / stock: %d\n", aux->part_num, aux->name, aux->class, aux->stock);

    free(aux);
}

/**
 * @brief Funcao que apresenta os conjuntos possiveis de serem construidos com o stock atual
 * 
 * @param listParts 
 * @param listPartsSets 
 * @param Sets 
 */
void setsPossiveis(Parts* listParts, Parts_Sets* listPartsSets, Sets* listSets){
    Parts* auxParts;
    Sets* auxSets;

    char valido = 's', *conjuntoAnterior = listPartsSets->set_num;
    int count = 0, quebrarParts, quebrarSet, fimConjunto = 0;
    

    //Correr Parts_Sets
    while(listPartsSets){
        quebrarParts = 0;

        //validar se Set diferente
        if(strcmp(listPartsSets->set_num, conjuntoAnterior) != 0) {
            fimConjunto = 1;
        }

        //Se set é diferente e se for valido, procura-o na lista Set e printa-o
        if(fimConjunto == 1 && valido == 's'){
            quebrarSet = 0;

            //Sets->procurar->printar
            for (auxSets = listSets; auxSets && quebrarSet == 0; auxSets = auxSets->next)
            {
                if(strcmp(auxSets->set_num, conjuntoAnterior) == 0)
                {
                    printf("set_num: %s / name: %s / year: %d / theme: %s\n", auxSets->set_num, auxSets->name, auxSets->year, auxSets->theme);
                    quebrarSet = 1;
                }
            }

            fimConjunto = 0;
        }
        else if(valido == 'n')
        {
            //nao é mais valido, avaçar ate ao proximo conjunto
            for(;listPartsSets->next && strcmp(listPartsSets->set_num, listPartsSets->next->set_num) == 0; listPartsSets = listPartsSets->next){}
            
            if(listPartsSets->next){
                listPartsSets = listPartsSets->next;
            }

            fimConjunto = 0;
            valido = 's';
        }
        

        //Procura a peça e faz validacao da peca para o conjunto
        for (auxParts = listParts; auxParts && quebrarParts == 0; auxParts = auxParts->next)
        {
            if(strcmp(listPartsSets->part_num, auxParts->part_num) == 0){

                if(auxParts->stock < listPartsSets->quantity) valido = 'n';

                quebrarParts = 1;
            }

        }

        count++;
        if(count == 1) printf("Conjuntos possiveis de serem construidos com o stock existente:\n\n");

        conjuntoAnterior = listPartsSets->set_num;
        listPartsSets = listPartsSets->next;
    }

    //Para o ultimo nodo da lista (primeira linha da file)
    if(valido == 's'){
        quebrarSet = 0;

        //Sets->printar
        for (auxSets = listSets; auxSets && quebrarSet == 0; auxSets = auxSets->next)
        {
            if(strcmp(auxSets->set_num, conjuntoAnterior) == 0)
            {
                printf("set_num: %s / name: %s / year: %d / theme: %s\n", auxSets->set_num, auxSets->name, auxSets->year, auxSets->theme);
                quebrarSet = 1;
            }
        }

        fimConjunto = 0;
    }

}
#pragma endregion

/**
 * @brief Regiao que remove peças e conjuntos do inventario, perante o input do utilizador
 * 
 */
#pragma region REMOVEINVENTORY
/**
 * @brief Remove todas as peças de uma class introduzida pelo utilizador
 * 
 * @param list 
 * @return Parts* 
 */
Parts* removeAllPartsByClass(Parts* list, char class[]){
    //Nodo que queremos eliminar
    Parts* aux = malloc(sizeof(Parts));
    
    for(aux = list; aux; aux = aux->next){
        if(strcmp(aux->class, class) == 0){
            if(aux->next)
                aux->next->previous = aux->previous;
            if(aux->previous)
                aux->previous->next = aux->next;
            else
                list = aux->next;

            free(aux);
        }
    }

    return list;
}

/**
 * @brief Remove todos os conjuntos de um tema introduzido pelo utilizador
 * 
 * @param list 
 * @param theme 
 * @return Sets* 
 */
Sets* removeAllSetsByTheme(Sets* list, Parts_Sets** list2, char theme[]){
    Sets* aux = malloc(sizeof(Sets));
    Parts_Sets *aux2 = malloc(sizeof(Parts_Sets));

    for(aux = list; aux; aux = aux->next){
        if(strcmp(aux->theme, theme) == 0){

            //Remocao dos nodos de parts_Sets com Informacao dos nodos selecionados de Parts
            for(aux2 = *list2; aux2; aux2 = aux2->next){
                if(strcmp(aux2->set_num, aux->set_num) == 0){
                    if(aux2->next)
                        aux2->next->previous = aux2->previous;
                    if(aux2->previous)
                        aux2->previous->next = aux2->next;
                    else
                        *list2 = aux2->next;

                    free(aux2);
                }
            }

            if(aux->next)
                aux->next->previous = aux->previous;
            if(aux->previous)
                aux->previous->next = aux->next;
            else
                list = aux->next;

            free(aux);
        }
    }
    
    return list;
}

#pragma endregion
