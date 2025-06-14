#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototipo.h"
#include "funcao.h"

int main(int argc, char const *argv[])
{
    int id = 0;
    int opcao = 0;

    Lista* lista =criar_estrutura();
    
    system("cls");
    do
    {
        menu();
        
        scanf("%i",&opcao);
        processar_opcao(&opcao,&id,lista);
    } while (opcao!=0);
    
    return 0;
}


