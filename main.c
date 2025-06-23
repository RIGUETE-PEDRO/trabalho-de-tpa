
#include "prototipo.h"

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

    Lista* lista =criar_estrutura();
    
    limpar();
    do
    {
        menu();
        
        scanf("%i",&opcao);
        processar_opcao(&opcao,&id,lista);
    } while (opcao!=0);
    
    return 0;
}


