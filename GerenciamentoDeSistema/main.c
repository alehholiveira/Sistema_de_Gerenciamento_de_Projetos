#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "FILA.h"

void menu()
{
    system("cls");
    printf("\t\tBEM-VINDO AO SISTEMA DE GERENCIAMENTO DE PROJETOS\n");
    printf(" QUAL OPCAO DESEJA UTILZAR?: \n");
    printf("   [1] Adicionar Tarefa\n");
    printf("   [2] Modificar uma tarefa\n");
    printf("   [3] Concluir uma tarefa\n");
    printf("   [4] Atualizar status de uma tarefa\n");
    printf("   [5] Listar tarefas pendentes\n");
    printf("   [6] Listar tarefas concluidas\n");
    printf("   [7] Listar tarefas concluidas com ou sem atrasos\n");
    printf("   [8] Sair do programa");
    printf("\n\n Digite aqui sua opcao: ");
}

Tarefa LerTarefa()
{
    Tarefa t;

    printf("Digite o código da tarefa: ");
    scanf("%d", &t.codigo);

    printf("Digite o nome da tarefa: ");
    scanf("%s", t.nome); // Use scanf com %s para ler strings

    printf("Digite o nome do projeto: ");
    scanf("%s", t.nomeprojeto); // Use scanf com %s para ler strings

    printf("Digite a data de início (dia mes ano): ");
    scanf("%d %d %d", &t.inicio.dia, &t.inicio.mes, &t.inicio.ano);

    printf("Digite a data de término (dia mes ano): ");
    scanf("%d %d %d", &t.termino.dia, &t.termino.mes, &t.termino.ano);

    printf("Digite o status (0 para pendente, 1 para concluída): ");
    scanf("%d", &t.status);

    return t;
}

int main()
{
    int opcao;
    Fila* minhaFila = CriaFila();

    menu();
    imprimeFila(minhaFila);
    scanf("%d",&opcao);
    switch(opcao)
    {
    case 1:
        break;

    case 2:
        break;

    case 3:
        break;

    case 4:
        break;

    case 5:
        break;

    case 6:
        break;

    case 7:
        break;

    case 8:
        break;

    default:
        printf("Opcao Invalida");
    }
    return 0;
}
