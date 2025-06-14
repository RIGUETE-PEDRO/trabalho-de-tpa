#ifndef FUNCAO_H
#define FUNCAO_H



// Definições de structs
typedef struct item Item;
typedef struct celula Celula;
typedef struct lista Lista;

struct item
{
    int id;
    char *nome;
    char *descricao;
    float preco;
};

struct celula
{
    Celula *ant;
    Celula *prox;
    Item *item;
};

struct lista
{
    Celula *prim;
    Celula *ult;
};

// Protótipos das funções
void menu();
void processar_opcao(int *opcao, int *id, Lista *lista);
Item *criaItem(int id, char *nome, char *descricao, float preco);
void cadastrar(Lista *lista, Item *item);
Lista *criar_estrutura();
void vetor_statico(int id_buscador, Lista* lista, int id);
void buscar(Lista *lista,int*id,char* nome);
void buscar_por_id(Lista * lista,int id);
void buscar_por_nome(Lista* lista,char* nome_buscado);
char confirmacao_de_exclusao();
void excluir(Lista *lista, Celula *excluir);
void exibir_e_excluir(Celula *atual,int *controller,int id,char *nome_buscado,Celula *endereco_excluir,Lista *lista);
int busca_binaria(int vetor[], int tamanho, int alvo);
#endif // FUNCAO_H
