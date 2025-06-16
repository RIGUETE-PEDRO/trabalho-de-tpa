void menu()
{

    puts("1-cadastrar produto");
    puts("2-exclusao de produto");
    puts("3-listagem ordenada");
    puts("4-busca de produto");
    puts("0-encerrar programa");
}

void processar_opcao(int *opcao, int *id, Lista *lista)
{
    char nome[100];
    char descricao[200];
    float preco = 0;

    switch (*opcao)
    {
    case 1:
        // cadastro
        puts("___________cadastrar_____________");
        (*id)++;
        printf("Digite o nome do produto: ");
        scanf(" %99[^\n]", nome);
        printf("Digite a descricao do produto: ");
        scanf(" %99[^\n]", descricao);
        printf("Digite o preco do produto: ");
        scanf(" %f", &preco);
        Item *item = criaItem(*id, nome, descricao, preco);
        cadastrar(lista, item);

        break;
    case 2:
        // exclusão
        puts("_____________excluir_____________");
        buscar(lista, id, nome);
        break;
    case 3:
        // ordenar();
        puts("_____________ordenar_____________");
        if ((*id) == 0)
        {
            // limpa terminal
            system("cls");
            printf("\nvoce ainda nao inseriu nada na lista\n");
            printf("estamos te redirecionando para o menu.....\n\n");
            return;
        }
        int opcao_a_ordenar = 0;

        do
        {
            puts("Como deseja ordenar?");
            puts("1 - ID");
            puts("2 - Nome");
            puts("3 - Preco");
            scanf("%d", &opcao_a_ordenar);
            if (opcao_a_ordenar != 1 && opcao_a_ordenar != 2 && opcao_a_ordenar != 3)
                puts("opcao invalida ");

        } while (opcao_a_ordenar != 1 && opcao_a_ordenar != 2 && opcao_a_ordenar != 3);

        break;
    case 4:
    {
        // buscar
        int id_buscador = 0;
        if ((*id) == 0)
        {
            system("cls");
            printf("\nvoce ainda nao inseriu nada na lista\n");
            printf("estamos te redirecionando para o menu.....\n\n");
            return;
        }

        puts("___________buscar________________");
        if (lista == NULL || lista->prim == NULL)
        {
            system("cls");
            printf("A lista esta vazia.\n\n");
            return;
        }

        puts("digite o ID do produto que voce precisa buscar");
        scanf("%i", &id_buscador);
        vetor_statico(id_buscador, lista, *id);
    }

    break;

    case 0:
        puts("SAINDO ............");
        liberando(lista);
        exit(1);
        break;

    default:
        puts("opcao invalida");
        break;
    }
}

Item *criaItem(int id, char *nome, char *descricao, float preco)
{
    Item *item = (Item *)malloc(sizeof(Item));
    if (item == NULL)
    {
        perror("Erro ao alocar memoria para item");
        exit(1);
    }

    item->id = id;
    item->nome = strdup(nome);
    item->descricao = strdup(descricao);
    item->preco = preco;

    return item;
}

void cadastrar(Lista *lista, Item *item)
{
    Celula *nova = (Celula *)malloc(sizeof(Celula));

    nova->item = item;
    nova->prox = NULL;
    nova->ant = lista->ult;

    if (lista->prim == NULL)
    {
        lista->prim = nova;
    }
    else
    {
        lista->ult->prox = nova;
    }
    lista->ult = nova;
    system("cls");
    printf("produto cadastrado com sucesso\n\n");
}

Lista *criar_estrutura()
{
    Lista *lista = (Lista *)malloc(sizeof(Lista));
    lista->prim = NULL;
    lista->ult = NULL;
    return lista;
};

void vetor_statico(int id_buscador, Lista *lista, int id_total)
{
    if (id_total == 0)
    {
        printf("Você ainda nao inseriu nada na lista.\n");
        return;
    }
    int vetor_id[id_total];
    float vetor_preco[id_total];
    char *vetor_nomes[id_total]; // vetor estático de ponteiros para nomes

    Celula *atual = lista->prim;
    // vou usar essa variavel para controlar o while melhor
    int identificador_busca = 0;
    int contador_id = 0;

    while (atual != NULL)
    {
        vetor_id[contador_id] = atual->item->id;
        vetor_preco[contador_id] = atual->item->preco;
        vetor_nomes[contador_id] = atual->item->nome;
        contador_id++;
        atual = atual->prox;
    }

    // tenho que chamar a função de ordernar

    merge_sort(vetor_id, vetor_nomes, vetor_preco, 0, id_total - 1);
    busca_binaria(vetor_id, vetor_nomes, vetor_preco, id_total, id_buscador);
}

void buscar(Lista *lista, int *id, char *nome)
{
    if ((*id) == 0)
    {
        system("cls");
        printf("\nvoce ainda nao inseriu nada na lista\n");
        printf("estamos te redirecionando para o menu.....\n\n");
        return;
    }
    if (lista == NULL || lista->prim == NULL)
    {
        system("cls");
        printf("A lista esta vazia.\n\n");
        return;
    }

    int opcao_buscar = 0;
    int opcao_selecionada = 0;
    while (opcao_buscar == 0)
    {
        printf("voce deseja como excluir seu produto");
        printf("\n1-id\n");
        printf("2-nome\n");
        scanf("%i", &opcao_selecionada);
        if (opcao_selecionada == 2)
        {
            opcao_buscar++;
            char nome_escolhido[100];

            // Limpa o buffer antes de ler
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
                ;

            printf("Digite o nome do produto para buscar: ");
            fgets(nome_escolhido, sizeof(nome_escolhido), stdin);

            // Remove o '\n' que o fgets captura
            nome_escolhido[strcspn(nome_escolhido, "\n")] = 0;

            buscar_por_nome(lista, nome_escolhido);
        }

        if (opcao_selecionada == 1)
        {
            opcao_buscar++;
            int id_escolhido = 0;
            printf("\nqual o id =");
            scanf("%i", &id_escolhido);
            buscar_por_id(lista, id_escolhido);
        }
        if (opcao_selecionada != 1 && opcao_selecionada != 2)
        {
            printf("opcao invalida\n");
        }
    }
}

void buscar_por_nome(Lista *lista, char *nome_buscado)
{
    if (lista == NULL || lista->prim == NULL)
    {
        system("cls");
        printf("A lista esta vazia.\n\n");
        return;
    }

    int controller = 2;
    Celula *atual = lista->prim;
    Celula *endereco_excluir;
    int id;
    exibir_e_excluir(atual, &controller, id, nome_buscado, endereco_excluir, lista);
    if (controller == 2)
    {
        printf("Produto com nome '%s' nao encontrado.\n\n", nome_buscado);
    }
}
void buscar_por_id(Lista *lista, int id)
{

    int controller = 3;
    char *nome_buscado;
    Celula *atual = lista->prim;
    Celula *endereco_excluir;
    if (lista == NULL || lista->prim == NULL)
    {
        printf("A lista está vazia.\n");
        return;
    }

    exibir_e_excluir(atual, &controller, id, nome_buscado, endereco_excluir, lista);
    if (controller == 3)
    {

        printf("produto nao encontrado\n");
    }
}

int confirmacao_de_exclusao()
{
    char entrada[100];
    int confirmacao;

    do
    {
        printf("Deseja realmente excluir?\n");
        printf("1 - Sim\n");
        printf("2 - Nao\n");
        printf("Escolha: ");

        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF)
            ; // Limpa o buffer

        if (fgets(entrada, sizeof(entrada), stdin))
        {
            // Remove newline '\n' se presente
            entrada[strcspn(entrada, "\n")] = 0;

            if (sscanf(entrada, "%d", &confirmacao) == 1 && (confirmacao == 1 || confirmacao == 2))
            {
                break;
            }
            else
            {
                printf("Opcao invalida. Tente novamente.\n");
            }
        }
        else
        {
            printf("Erro de leitura. Tente novamente.\n");
        }

    } while (1);

    return confirmacao;
}

void excluir(Lista *lista, Celula *excluir)
{
    if (lista == NULL || excluir == NULL)
        return;

    // Religa os ponteiros da lista
    if (excluir->ant != NULL)
        excluir->ant->prox = excluir->prox;
    else
        lista->prim = excluir->prox;

    if (excluir->prox != NULL)
        excluir->prox->ant = excluir->ant;
    else
        lista->ult = excluir->ant;

    // Libera os campos internos do item (se foram alocados com malloc/strdup)
    if (excluir->item != NULL) {
        free(excluir->item->nome);
        free(excluir->item->descricao);
        free(excluir->item);
    }

    // Libera a célula
    free(excluir);
}

void exibir_e_excluir(Celula *atual, int *controller, int id, char *nome_buscado, Celula *endereco_excluir, Lista *lista)
{
    int id_temporario = 0;
    char *nome_buscado_temporario = "limpar";
    // controladores para excluir por id e por nome
    if ((*controller) == 3)
    {
        id_temporario = id;
    }
    if ((*controller) == 2)
    {
        nome_buscado_temporario = nome_buscado;
    }
    // buscando produto para deletar
    while (atual != NULL)
    {
        if (atual->item->id == id_temporario || strcmp(atual->item->nome, nome_buscado_temporario) == 0)
        {
            ((*controller)++);
            printf("Produto encontrado:\n");
            printf("ID: %d\n", atual->item->id);
            printf("Nome: %s\n", atual->item->nome);
            printf("Descricao: %s\n", atual->item->descricao);
            printf("Preco: %.2f\n", atual->item->preco);

            int status = confirmacao_de_exclusao();
            Celula *prox = atual->prox;
            endereco_excluir = atual;

            if (status == 1)
            {
                excluir(lista, endereco_excluir);
                system("cls");
                printf("\nproduto excluido com sucesso\n\n");
            }

            if (status == 2)
            {
                system("cls");
                printf("\n o produto nao foi excluido\n\n");

                return;
            }

            atual = prox;
        }
        else
        {
            atual = atual->prox;
        }
    }
}

void busca_binaria(int vetor_id[], char *vetor_nomes[], float vetor_preco[], int tamanho, int id_buscador)
{
    int inicio = 0;
    int fim = tamanho - 1;

    while (inicio <= fim)
    {
        int meio = (inicio + fim) / 2;

        if (vetor_id[meio] == id_buscador)
        {
            system("cls");
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

void merge_sort(int vetor_id[], char *vetor_nome[], float vetor_preco[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        merge_sort(vetor_id, vetor_nome, vetor_preco, l, m);
        merge_sort(vetor_id, vetor_nome, vetor_preco, m + 1, r);
        merge(vetor_id, vetor_nome, vetor_preco, l, m, r);
    }
}

void merge(int vetor_id[], char *vetor_nome[], float vetor_preco[], int l, int m, int r)
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
        if (L_id[i] <= R_id[j])
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

void liberando(Lista *lista) {
    // Verifica se a lista ou o primeiro nó já são nulos
    if (lista == NULL || lista->prim == NULL) {
        free(lista);
        return; // Não há nada a fazer
    }

    Celula* atual = lista->prim; // Começa pelo primeiro nó
    Celula* proximo = NULL;

    // Percorre a lista até o fim
    while (atual != NULL) {
        // 1. Guarda o endereço do próximo nó antes de perder a referência
        proximo = atual->prox; 

        // 2. Libera a memória do item contido neste nó
        //    (Importante: só faça isso se o 'item' também foi alocado dinamicamente com malloc/calloc)
        if (atual->item != NULL) {
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
/// rodenar ,busca produto, encerrar