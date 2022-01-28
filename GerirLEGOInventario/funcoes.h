typedef struct _parts
{
    char *part_num, *name, *class;
    int stock;
    struct _parts *next, *previous;
} Parts;

typedef struct _parts_sets
{
    char *set_num, *part_num;
    int quantity;
    struct _parts_sets *next, *previous;
} Parts_Sets;

typedef struct _sets
{
    char *set_num, *name, *theme;
    int year;
    struct _sets *next, *previous;
} Sets;

//Assinaturas
//Menus
void MenuTexto();
void Menu(Parts **listParts, Parts_Sets **listPartsSets, Sets **listSets);
void MenuStockTexto();
void MenuStock(Parts **listParts, Parts_Sets **listPartsSets, Sets **listSets);
//Destruicao listas
void destroyParts(Parts* list);
void destroyPartsSets(Parts_Sets* list);
void destroySets(Sets* list);
void destroyAll(Parts* list1, Parts_Sets* list2, Sets* list3);
//Remocao nodos
Parts* removeAllPartsByClass(Parts* list, char classe[]);
Sets* removeAllSetsByTheme(Sets* list, Parts_Sets** list2, char theme[]);
//Listar listas
void mostraListaParts(Parts* list);
void mostraListaPartsSets(Parts_Sets* list);
void mostraListaSets(Sets *list);
//Leitura/Escrita listas
void salvaDados(Parts** listParts, Parts_Sets** listPartsSets, Sets** listSets);
Sets* lerSets(Sets *list);
Parts_Sets* lerPartsSets(Parts_Sets *list);
Parts* lerParts(Parts *list);
//Inserts
Sets* head_insert_sets(Sets *list, Sets* aux);
Parts_Sets* head_insert_partsSets(Parts_Sets *list, Parts_Sets* aux);
Parts* head_insert_parts(Parts *list, Parts* aux);
Sets *insert_ordemAno(Sets *new_list, Sets *list);
Parts_Sets* insert_ordemPartNum(Parts_Sets* new_list, Parts_Sets* aux);
//Funcoes de obter input
char* getSetNum(Sets** list);
char* getClass(Parts **list);
char* getPartNum(Parts **list);
char* getTheme(Sets** list);
//Outras funcoes
void showSets_themeOrd_year(Sets *list, char tema[]);
void partsByClassInSets(Parts *listsParts, Parts_Sets *listPartsSets, char set_num[], char class[]);
void pecasConstroiSet(Parts* listParts, Parts_Sets *listPartsSets, char set_num[]);
int totalPartsInSet(Parts* listParts, Parts_Sets* listPartsSets, char set_num[]);
int totalParts(Parts* list);
void changeStock(Parts* list, char part_num[]);
void addFullSet(Parts *list, Parts_Sets *list2, char set_num[]);
void PecaMaisUsada(Parts_Sets *listPartsSets, Parts *listParts);
void setsPossiveis(Parts* listParts, Parts_Sets* listPartsSets, Sets* listSets);
