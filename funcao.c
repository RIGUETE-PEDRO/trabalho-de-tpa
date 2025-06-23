#include "prototipo.h"

// função para limpar o terminal no sistemas operacionais linux e windows
void limparTela()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear")
#endif
}
// função para exibir o menu
void menu()
{
    puts("\n_______MENU___________");
    puts("1-cadastrar produto");
    puts("2-exclusao de produto");
    puts("3-listagem ordenada");
    puts("4-busca de produto");
    puts("0-encerrar programa");
    puts("_________________________");
}
// função para processar a opção escolhida pelo usuário
void processar_opcao(int *opcao, int *id, Lista *lista)
{
    char nome[100];
    char descricao[200];
    float preco = 0;
    // Preencher vetores com os dados da lista
    int vetor_id[*id];
    float vetor_preco[*id];
    char *vetor_nome[*id];
    int criterio;

    switch (*opcao)
    {
    case 1:
        // cadastro
        puts("___________cadastrar_____________");
        // preenche a produtos
        printf("Digite o nome do produto: ");
        scanf(" %99[^\n]", nome);
        // verifica se existe o produto
        if (existeProduto(lista, nome))
        {
            printf("Produto com nome \"%s\" ja existe!\n", nome);
            break;
        }
        // Incrementa o ID seve como indentificador unico de produto
        (*id)++;
        printf("Digite a descricao do produto: ");
        scanf(" %199[^\n]", descricao);
        printf("Digite o preco do produto: ");
        scanf(" %f", &preco);
        // Cria o item para cadastra na lista
        Item *item = criaItem(*id, nome, descricao, preco);
        // aqui ele monta a celula inserindo o item
        cadastrar(lista, item);

        break;

    case 2:
        // exclusão
        puts("_____________excluir_____________");
        if ((*id) == 0)
        {
            // limpa a tela e informa que não há produtos cadastrados se nao existir nenhum
            limparTela();
            printf("\nvoce ainda nao inseriu nada na lista\n");
            printf("estamos te redirecionando para o menu.....\n\n");
            return;
        }
        // se passa nos if ele tenta busca produtos
        buscar(lista, nome);
        break;
    case 3:
        // ordenar();
        puts("_____________ordenar_____________");
        // chama a função ordenar e mostrar
        ordenar_e_mostrar(lista);
        break;
    case 4:
    {
        // buscar
        int id_buscador = 0;
        if ((*id) == 0)
        {
            limparTela();
            printf("\nvoce ainda nao inseriu nada na lista\n");
            printf("estamos te redirecionando para o menu.....\n\n");
            return;
        }

        puts("___________buscar________________");
        if (lista == NULL || lista->prim == NULL)
        {
            limparTela();
            printf("A lista esta vazia.\n\n");
            return;
        }

        puts("digite o ID do produto que voce precisa buscar");
        scanf("%i", &id_buscador);
        vetor_statico(id_buscador, lista, *id, criterio);
    }

    break;

    case 0:
        // sair do programa
        puts("SAINDO ............");
        // libera a memoria alocada para a lista
        liberando(lista);
        // encerra o programa
        exit(1);
        break;

    default:
        // caso a opcoes seja diferente de 1,2,3,4 ou 0
        puts("opcao invalida");
        break;
    }
}
// cria o item para dps ser alocado a lista
Item *criaItem(int id, char *nome, char *descricao, float preco)
{
    // aloca memoria para um item
    Item *item = (Item *)malloc(sizeof(Item));
    if (item == NULL)
    {
        puts("Erro ao alocar memoria para item");
        exit(1);
    }

    item->id = id;                       // recebe o id ao item
    item->nome = strdup(nome);           // aloca memoria para o nome e copia o conteudo
    item->descricao = strdup(descricao); // aloca memoria para a descricao e copia o conteudo
    item->preco = preco;                 // recebe o preco ao item

    return item; // retorna o item
}

void cadastrar(Lista *lista, Item *item)
{
    // cria a celula para anexar o item
    Celula *nova = (Celula *)malloc(sizeof(Celula));
    // celula nova recebe o item criado
    nova->item = item;
    nova->prox = NULL;
    nova->ant = lista->ult;
    // verifica se e o primeira celula se nao for vai adicionar no fim da lista
    if (lista->prim == NULL)
    {
        lista->prim = nova;
    }
    else
    {
        lista->ult->prox = nova;
    }
    lista->ult = nova;
    limparTela();
    printf("produto cadastrado com sucesso\n\n");
}
// cria a estrutura da lista
Lista *criar_estrutura()
{
    // aloca memoria para a lista
    // e inicializa os ponteiros prim e ult como NULL
    Lista *lista = (Lista *)malloc(sizeof(Lista));
    lista->prim = NULL;
    lista->ult = NULL;
    // retorna a lista criada
    return lista;
};

// cria vetor estatico para percorrer mais rapido a lista
//  e fazer a busca binaria
void vetor_statico(int id_buscador, Lista *lista, int id_total, int criterio)
{
    // verifica se tem produtos na lista
    if (id_total == 0)
    {
        printf("Você ainda nao inseriu nada na lista.\n");
        return;
    }
    int vetor_id[id_total];      // vetor estático de IDs
    float vetor_preco[id_total]; // vetor estático de preços
    char *vetor_nomes[id_total]; // vetor estático de ponteiros para nomes

    Celula *atual = lista->prim;
    // percorre a lista e preenche os vetores
    int contador_id = 0;

    // passa em toda lista ate chegar ao final

    while (atual != NULL)
    {
        // e preenche os vetores com os dados dos produtos
        vetor_id[contador_id] = atual->item->id;
        vetor_preco[contador_id] = atual->item->preco;
        vetor_nomes[contador_id] = atual->item->nome;
        // para para a proxima posicao do vetor
        contador_id++;
        // passa para o proximo elemento
        atual = atual->prox;
    }

    // tenho que chamar a função de ordernar

    // ultiliz o metodo de ordenação merge sort logo apos aplico uma busca binaria para encontrar o produto ultilizando o vetor
    merge_sort(vetor_id, vetor_nomes, vetor_preco, 0, id_total - 1, criterio);
    busca_binaria(vetor_id, vetor_nomes, vetor_preco, id_total, id_buscador);
}

// função de busca ultilizada na função excluir para achar o produto que deseja deletar
void buscar(Lista *lista, char *nome)
{
    // Verifica se a lista está vazia
    if (lista == NULL || lista->prim == NULL)
    {
        limparTela();
        printf("A lista esta vazia.\n\n");
        return;
    }

    int opcao_buscar = 0;
    int opcao_selecionada = 0;
    // verificação se vai excluir ou nao
    while (opcao_buscar == 0)
    {
        // exibe opcoes
        printf("voce deseja como excluir seu produto");
        printf("\n1-id\n");
        printf("2-nome\n");
        scanf("%i", &opcao_selecionada);
        // se selecionar 2 iremos pelo caminho de nome
        if (opcao_selecionada == 2)
        {
            // inclementamos para corta o loop na proxima verificaçao
            opcao_buscar++;
            char nome_escolhido[100];

            // Limpa o buffer antes de ler
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
                // pega o nome para busca
                printf("Digite o nome do produto para buscar: ");
            fgets(nome_escolhido, sizeof(nome_escolhido), stdin);

            // Remove o '\n' que o fgets captura
            nome_escolhido[strcspn(nome_escolhido, "\n")] = 0;
            // chama a busca por nome
            buscar_por_nome(lista, nome_escolhido);
        }
        // se for selecionado 1 vamos pelo id
        if (opcao_selecionada == 1)
        {
            // corta o while
            opcao_buscar++;
            // pegamos o id escolhido
            int id_escolhido = 0;
            printf("\nqual o id =");
            scanf("%i", &id_escolhido);
            // buscamos pelo id
            buscar_por_id(lista, id_escolhido);
        }
        // verifica se a opcao atende o requisito de 1 ou 2 se nao o loop se repete ate atender
        if (opcao_selecionada != 1 && opcao_selecionada != 2)
        {
            printf("opcao invalida\n");
        }
    }
}

// buscamos um produto por nome
void buscar_por_nome(Lista *lista, char *nome_buscado)
{
    // se a lista estiver vazia voltamos para o menu e exibi uma msg
    if (lista == NULL || lista->prim == NULL)
    {
        limparTela();
        printf("A lista esta vazia.\n\n");
        return;
    }
    // passamos o controler para que se ele nao mudar mostra que nao foi encontrado
    int controller = 2;
    // tambem passamos a primeira celuila e a que deseja excluir
    Celula *atual = lista->prim;
    Celula *endereco_excluir;
    int id;
    exibir_e_excluir(atual, &controller, id, nome_buscado, endereco_excluir, lista);
    if (controller == 2)
    {
        printf("Produto com nome '%s' nao encontrado.\n\n", nome_buscado);
    }
}

// nessa função buscamos por id
void buscar_por_id(Lista *lista, int id)
{

    int controller = 3;
    char *nome_buscado;
    // passamos o endereço atual e tambem o que vamos excluir
    Celula *atual = lista->prim;
    Celula *endereco_excluir;
    // exibe essa msg se a lista estiver vazia
    if (lista == NULL || lista->prim == NULL)
    {
        printf("A lista está vazia.\n");
        return;
    }
    // passasmos o controller com o intuito de achar o produto e alter ele na fução se for achado
    exibir_e_excluir(atual, &controller, id, nome_buscado, endereco_excluir, lista);
    if (controller == 3)
    {
        // se nao encontrado exibi essa msg
        printf("produto nao encontrado\n");
    }
}

// confirma a exclusao
int confirmacao_de_exclusao()
{
    //
    char entrada[100];
    int confirmacao;

    do
    {
        printf("Deseja realmente excluir?\n");
        printf("1 - Sim\n");
        printf("2 - Nao\n");
        printf("Escolha: ");

        if (fgets(entrada, sizeof(entrada), stdin))
        {
            // Remove o caractere de nova linha \n do final da string, que é adicionado automaticamente pelo fgets.
            entrada[strcspn(entrada, "\n")] = 0; // Remove o \n

            /*
             Tenta converter a string 'entrada' para um número inteiro e verifica se é 1 ou 2.
             A função sscanf retorna 1 se conseguiu ler exatamente um inteiro.
             A variável 'confirmacao' só é aceita se for 1 ou 2.
            */
            if (sscanf(entrada, "%d", &confirmacao) == 1 && (confirmacao == 1 || confirmacao == 2))
            {
                break;
            }
            else
            {
                // se nao converte trasforma em opcao invalida
                printf("Opcao invalida. Tente novamente.\n");
            }
        }
        else
        {
            // exibe erro de leitura se nao conseguir ler a entrada
            printf("Erro de leitura. Tente novamente.\n");
        }

    } while (1);
    // retorna a confirmaçao
    return confirmacao;
}

// responsavel por liberar memoria dos elemetos excluido
void excluir(Lista *lista, Celula *excluir)
{
    if (lista == NULL || excluir == NULL)
        return;

    // religa os ponteiros da lista:
    // se a célula a ser excluída NÃO é a primeira, ajusta o ponteiro do anterior
    if (excluir->ant != NULL)
        excluir->ant->prox = excluir->prox;

    // se não, ela é a primeira, então atualiza o ponteiro 'prim' da lista
    else
        lista->prim = excluir->prox;

    //  se a célula a ser excluída nao é a última, ajusta o ponteiro do próximo
    if (excluir->prox != NULL)
        excluir->prox->ant = excluir->ant;

    // Se não, ela é a última, então atualiza o ult
    else
        lista->ult = excluir->ant;

    // libera os campos internos do item (se foram alocados com malloc/strdup)
    if (excluir->item != NULL)
    {
        free(excluir->item->nome);
        free(excluir->item->descricao);
        free(excluir->item);
    }

    // Libera a célula
    free(excluir);
}

void exibir_e_excluir(Celula *atual, int *controller, int id, char *nome_buscado, Celula *endereco_excluir, Lista *lista)
{
    // Determina modo de busca
    int id_temporario = (*controller == 3) ? id : 0;
    char *nome_temporario = (*controller == 2) ? nome_buscado : NULL;

    // Percorre a lista buscando correspondência
    while (atual != NULL)
    {
        if ((*controller == 3 && atual->item->id == id_temporario) || (*controller == 2 && strcasecmp(atual->item->nome, nome_temporario) == 0))
        {
            (*controller)++; // sinaliza que encontrou
            printf("Produto encontrado:\n");
            printf("ID: %d\n", atual->item->id);
            printf("Nome: %s\n", atual->item->nome);
            printf("Descricao: %s\n", atual->item->descricao);
            printf("Preco: %.2f\n", atual->item->preco);

            // Lê confirmação
            int status = confirmacao_de_exclusao();

            // Guarda próximo antes de excluir
            Celula *prox = atual->prox;

            // se retona de confimação de exclusao 1 produto excluido
            if (status == 1)
            {
                excluir(lista, atual);
                limparTela(); // ou "clear" no Linux
                printf("\nProduto excluido com sucesso\n\n");
            }
            // se o valor for diferente de 1 significa que o produto não foi excluido
            else
            {
                limparTela();
                printf("\nO produto nao foi excluido\n\n");
            }

            // Avança para o próximo nó e continua (ou sai, se preferir parar após 1 remoção)
            atual = prox;
        }
        else
        {
            // Continua procurando
            atual = atual->prox;
        }
    }
}
// faz uma busca binaria ao item
void busca_binaria(int vetor_id[], char *vetor_nomes[], float vetor_preco[], int tamanho, int id_buscador)
{
    int inicio = 0;
    int fim = tamanho - 1;

    while (inicio <= fim)
    {
        int meio = (inicio + fim) / 2;

        if (vetor_id[meio] == id_buscador)
        {
            limparTela();
            printf("Produto encontrado!\n");
            printf("ID: %d\n", vetor_id[meio]);
            printf("Nome: %s\n", vetor_nomes[meio]);
            printf("Preco: R$ %.2f\n\n", vetor_preco[meio]);
            return;
        }
        else if (vetor_id[meio] < id_buscador)
        {
            inicio = meio + 1;
        }
        else
        {
            fim = meio - 1;
        }
    }

    printf("Produto com ID %d nao encontrado.\n", id_buscador);
}

void merge_sort(int vetor_id[], char *vetor_nome[], float vetor_preco[], int l, int r, int criterio)
{
    if (l < r)
    {
        //corta o vetor na metade
        //fiz essa atribuicao do m para evitar estourar o inteiro  entao dividimos tornando o valor menor dps  somamos com l 
        int m = l + (r - l) / 2;
        merge_sort(vetor_id, vetor_nome, vetor_preco, l, m, criterio);
        merge_sort(vetor_id, vetor_nome, vetor_preco, m + 1, r, criterio);
        merge(vetor_id, vetor_nome, vetor_preco, l, m, r, criterio);
    }
}

void merge(int vetor_id[], char *vetor_nome[], float vetor_preco[], int l, int m, int r, int criterio)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    int L_id[n1], R_id[n2];
    float L_preco[n1], R_preco[n2];
    char *L_nome[n1], *R_nome[n2];

    for (int i = 0; i < n1; i++)
    {
        L_id[i] = vetor_id[l + i];
        L_nome[i] = vetor_nome[l + i];
        L_preco[i] = vetor_preco[l + i];
    }

    for (int j = 0; j < n2; j++)
    {
        R_id[j] = vetor_id[m + 1 + j];
        R_nome[j] = vetor_nome[m + 1 + j];
        R_preco[j] = vetor_preco[m + 1 + j];
    }

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2)
    {
        int condicao;

        if (criterio == 1)
            condicao = (L_id[i] <= R_id[j]);
        else if (criterio == 2)
            condicao = (strcmp(L_nome[i], R_nome[j]) <= 0);
        else
            condicao = (L_preco[i] <= R_preco[j]);

        if (condicao)
        {
            vetor_id[k] = L_id[i];
            vetor_nome[k] = L_nome[i];
            vetor_preco[k] = L_preco[i];
            i++;
        }
        else
        {
            vetor_id[k] = R_id[j];
            vetor_nome[k] = R_nome[j];
            vetor_preco[k] = R_preco[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        vetor_id[k] = L_id[i];
        vetor_nome[k] = L_nome[i];
        vetor_preco[k] = L_preco[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        vetor_id[k] = R_id[j];
        vetor_nome[k] = R_nome[j];
        vetor_preco[k] = R_preco[j];
        j++;
        k++;
    }
}

void liberando(Lista *lista)
{
    // Verifica se a lista ou o primeiro nó já são nulos
    if (lista == NULL || lista->prim == NULL)
    {
        free(lista);
        return; // Não há nada a fazer
    }

    Celula *atual = lista->prim; // Começa pelo primeiro nó
    Celula *proximo = NULL;

    // Percorre a lista até o fim
    while (atual != NULL)
    {
        // 1. Guarda o endereço do próximo nó antes de perder a referência
        proximo = atual->prox;

        // 2. Libera a memória do item contido neste nó
        //    (Importante: só faça isso se o 'item' também foi alocado dinamicamente com malloc/calloc)
        if (atual->item != NULL)
        {
            free(atual->item->nome);
            free(atual->item->descricao);
            free(atual->item);
        }

        // 3. Libera a memória do nó atual
        free(atual);

        // 4. Move para o próximo nó que foi salvo
        atual = proximo;
    }

    // 5. Ao final, ajusta os ponteiros da lista para indicar que ela está vazia
    lista->prim = NULL;
    lista->ult = NULL;

    free(lista);
}

// resposavel por ordena e mostra a lista
void ordenar_e_mostrar(Lista *lista)
{
    // se alista estiver pura
    if (lista->prim == NULL)
    {
        limparTela();
        // limpa e retorna a função menu
        printf("\nVoce ainda nao inseriu nada na lista\n");
        printf("Estamos te redirecionando para o menu.....\n\n");
        return;
    }
    // declarro o criterio para verificar pelo que prefere organizar
    int criterio;
    do
    {
        //opcoes do criterio
        puts("Como deseja ordenar?");
        puts("1 - ID");
        puts("2 - Nome");
        puts("3 - Preco");
        scanf("%d", &criterio);
        if (criterio != 1 && criterio != 2 && criterio != 3)
            puts("Opcao invalida");
    } while (criterio != 1 && criterio != 2 && criterio != 3);

    // Contar elementos reais da lista
    int tamanho = 0;
    Celula *atual = lista->prim;
    while (atual != NULL)
    {
        tamanho++;
        atual = atual->prox;
    }

    //cria vetores estaticos
    int vetor_id[tamanho];
    float vetor_preco[tamanho];
    char *vetor_nome[tamanho];

    atual = lista->prim;
    int i = 0;
    //atribui o valor do vetor para as possiçoes do vetor
    while (atual != NULL)
    {
        vetor_id[i] = atual->item->id;
        vetor_nome[i] = atual->item->nome;
        vetor_preco[i] = atual->item->preco;
        atual = atual->prox;
        //incrementa o controlador do while
        i++;
    }
    //mergia os item para colocar em ordem
    merge_sort(vetor_id, vetor_nome, vetor_preco, 0, tamanho - 1, criterio);

    //cabeçalho da ordenação
    puts("\n--- Lista ordenada ---");
    //loop responsavel por percorrere imprimindo os items 
    for (int j = 0; j < tamanho; j++)
    {
        printf("ID: %d | Nome: %s | Preco: %.2f\n", vetor_id[j], vetor_nome[j], vetor_preco[j]);
    }
}
//verifica se o item existe para nao ouver duplicidade
int existeProduto(Lista *lista, char *nome)
{
    //
    Celula *atual = lista->prim;
    while (atual != NULL)
    {
        //verifica se as letras sao iguais com a palavra strcmp ela retorna um numero diferente de 0 se for diferente
        if (strcmp(atual->item->nome, nome) == 0)
        {
            return 1; // já existe
        }
        atual = atual->prox;
    }
    return 0; // não existe
}