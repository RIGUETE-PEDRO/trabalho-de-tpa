
#include "prototipo.h"

//limpar o terminal
void limpar()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear")
#endif
}

int main(int argc, char const *argv[])
{
    int id = 0;
    int opcao = 0;

    //cria estrututra ao iniciar a main
    Lista* lista =criar_estrutura();
    
    //limpa o terminal
    limpar();
    do
    {
        //exibe menu
        menu();
        
        //pega a opcao desejada
        scanf("%i",&opcao);

        //analisa qual sera a funçao que sera chamada para atender a necessidade da pessoa
        processar_opcao(&opcao,&id,lista);

        // ate que seja diferente de zero
    } while (opcao!=0);
    
    return 0;
}


