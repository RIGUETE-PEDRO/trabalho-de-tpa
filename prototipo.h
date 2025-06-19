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
void liberando(Lista *lista);
void processar_opcao(int *opcao, int *id, Lista *lista);
Item *criaItem(int id, char *nome, char *descricao, float preco);
void cadastrar(Lista *lista, Item *item);
Lista *criar_estrutura();
void merge(int vetor_id[], char *vetor_nome[], float vetor_preco[], int l, int m, int r,int criterio);
void merge_sort(int vetor_id[], char *vetor_nome[], float vetor_preco[], int l, int r,int criterio);
void vetor_statico(int id_buscador, Lista *lista, int id,int criterio);
void buscar(Lista *lista, char *nome);
void buscar_por_id(Lista *lista, int id);
void buscar_por_nome(Lista *lista, char *nome_buscado);
int confirmacao_de_exclusao();
void ordenar_e_mostrar(Lista * lista);
void excluir(Lista *lista, Celula *excluir);
void exibir_e_excluir(Celula *atual, int *controller, int id, char *nome_buscado, Celula *endereco_excluir, Lista *lista);
int existeProduto(Lista *lista, char *nome);
void busca_binaria(int vetor_id[], char *vetor_nomes[], float vetor_preco[], int tamanho, int id_buscador);
#endif // FUNCAO_H
