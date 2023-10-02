#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "FILA.h"

void aguardarEnter() {
    printf("Pressione Enter para continuar...");
    while (getchar() != '\n'); // Aguarda o usuário pressionar Enter
}

void menu()
{
    system("cls");
    printf(" _______________________________________________________ \n");
    printf("| BEM-VINDO AO SISTEMA DE GERENCIAMENTO DE PROJETOS \t|\n");
    printf("| QUAL OPCAO DESEJA UTILZAR?:                        \t|      \n");
    printf("|   [1] Adicionar Tarefa                             \t|      \n");
    printf("|   [2] Modificar uma tarefa                         \t|      \n");
    printf("|   [3] Concluir uma tarefa                          \t|      \n");
    printf("|   [4] Atualizar status de uma tarefa               \t|      \n");
    printf("|   [5] Listar tarefas pendentes                     \t|      \n");
    printf("|   [6] Listar tarefas concluidas                    \t|      \n");
    printf("|   [7] Listar tarefas concluidas com ou sem atrasos \t|      \n");
    printf("|   [8] Sair do programa                             \t|      \n");
    printf(" ------------------------------------------------------- ");
    printf("\n\n -> Digite aqui sua opcao: ");
}

Tarefa LerTarefa()
{
    Tarefa t;

    printf("Digite o Codigo da tarefa: ");
    scanf("%d", &t.codigo);

    printf("Digite o nome da tarefa: ");
    scanf("%s", t.nome); // Use scanf com %s para ler strings

    printf("Digite o nome do projeto: ");
    scanf("%s", t.nomeprojeto); // Use scanf com %s para ler strings

    printf("Digite a data de Inicio (dia mes ano):\n ");
    scanf("%d %d %d", &t.inicio.dia, &t.inicio.mes, &t.inicio.ano);

    printf("Digite a data de termino (dia mes ano):\n ");
    scanf("%d %d %d", &t.termino.dia, &t.termino.mes, &t.termino.ano);

    time_t tempo_atual;
    struct tm* data_atual;
    time(&tempo_atual);
    data_atual = localtime(&tempo_atual);

    // Comparar a data de término com a data atual para definir o status
    if (t.termino.ano < (data_atual->tm_year + 1900) ||
        (t.termino.ano == (data_atual->tm_year + 1900) && t.termino.mes < (data_atual->tm_mon + 1)) ||
        (t.termino.ano == (data_atual->tm_year + 1900) && t.termino.mes == (data_atual->tm_mon + 1) &&
         t.termino.dia < data_atual->tm_mday)) {
        t.status = 1; // Tarefa concluída e atrasada
    } else {
        t.status = 0; // Tarefa pendente ou em dia
    }

    return t;
}

void modificarTarefa(Fila* minhaFila, int codigo) {
    No* temp = minhaFila->ini;

    // Encontrar a tarefa com o Codigo especificado
    while (temp != NULL) {
        if (temp->info.codigo == codigo) {
            // Tarefa encontrada, mostrar detalhes atuais
            printf("Detalhes da Tarefa:\n");
            printf("Codigo: %d\n", temp->info.codigo);
            printf("Nome: %s\n", temp->info.nome);
            printf("Nome do Projeto: %s\n", temp->info.nomeprojeto);
            printf("Data de Inicio: %d/%d/%d\n", temp->info.inicio.dia, temp->info.inicio.mes, temp->info.inicio.ano);
            printf("Data de termino: %d/%d/%d\n", temp->info.termino.dia, temp->info.termino.mes, temp->info.termino.ano);
            printf("Status: %d\n", temp->info.status);

            // Pedir ao usuário para modificar os campos
            printf("Digite o novo nome da tarefa: ");
            scanf("%s", temp->info.nome);

            printf("Digite o nome do projeto: ");
            scanf("%s", temp->info.nomeprojeto);

            printf("Digite a nova data de Inicio (dia mes ano): ");
            scanf("%d %d %d", &temp->info.inicio.dia, &temp->info.inicio.mes, &temp->info.inicio.ano);

            printf("Digite a nova data de termino (dia mes ano): ");
            scanf("%d %d %d", &temp->info.termino.dia, &temp->info.termino.mes, &temp->info.termino.ano);

            printf("Digite o novo status (0 para pendente, 1 para concluida): ");
            scanf("%d", &temp->info.status);

            printf("Tarefa modificada com sucesso!\n");
            printf("Detalhes da Tarefa:\n");
            printf("Codigo: %d\n", temp->info.codigo);
            printf("Nome: %s\n", temp->info.nome);
            printf("Nome do Projeto: %s\n", temp->info.nomeprojeto);
            printf("Data de Inicio: %d/%d/%d\n", temp->info.inicio.dia, temp->info.inicio.mes, temp->info.inicio.ano);
            printf("Data de termino: %d/%d/%d\n", temp->info.termino.dia, temp->info.termino.mes, temp->info.termino.ano);
            printf("Status: %d\n", temp->info.status);
            return;
        }
        temp = temp->prox;
    }

    // Se o Codigo da tarefa não foi encontrado
    printf("Tarefa com o codigo %d nao encontrada.\n", codigo);
}

void ConcluiTarefa (Fila* f, ListaConcluidas** l)
{
    time_t tempo_atual;
    struct tm data_atual;
    time(&tempo_atual);
    data_atual = *localtime(&tempo_atual);
    int codigo;

    printf("Digite o codigo da tarefa que deseja concluir: ");
    scanf("%d", &codigo);

    No *aux = f->ini;
    No *aux2 = NULL;

    while (aux != NULL) {
        if (aux->info.codigo == codigo) {
            // Atualizar a data de término da tarefa com a data atual
            aux->info.termino.dia = data_atual.tm_mday;
            aux->info.termino.mes = data_atual.tm_mon + 1;
            aux->info.termino.ano = data_atual.tm_year + 1900;

            // Remover a tarefa concluída da fila
            if (aux2 == NULL) {
                f->ini = aux->prox;
            } else {
                aux2->prox = aux->prox;
            }


            ListaConcluidas* novoConcluida = insereListaConcluida(aux->info, *l);
            if (novoConcluida != NULL)
            {
                novoConcluida->info2 = aux->info;
                novoConcluida->prox2 = *l;
                *l = novoConcluida;
                printf("Tarefa concluída e movida para a lista de tarefas concluídas.\n");

            }

            else
            {
                printf("Erro ao alocar memória para o novo nodo concluído.\n");
            }
        }
        aux2 = aux;
        aux = aux->prox;
    }

    printf("Tarefa com o código %d não encontrada na fila.\n", codigo);
}

void imprimeConcluida (ListaConcluidas* l)
{
    ListaConcluidas* q = l;
    printf("\n\t\t");
    printf("Lista pendente");
    while (q != NULL)
    {
        printf("Codigo: %d\n", q->info2.codigo);
        printf("Nome: %s\n", q->info2.nome);
        printf("Nome do Projeto: %s\n", q->info2.nomeprojeto);
        printf("Data de Início: %d/%d/%d\n", q->info2.inicio.dia, q->info2.inicio.mes, q->info2.inicio.ano);
        printf("Data de Término: %d/%d/%d\n", q->info2.termino.dia, q->info2.termino.mes, q->info2.termino.ano);
        printf("Status: %d\n", q->info2.status);
        printf("\n");
        q = q->prox2;
    }
    printf("\n");
}

void atualizaTarefa(ListaConcluidas** l, Fila* f)
{
    int codigo;
    No *aux = f->ini;
    No *aux2 = NULL;
    printf("Digite o codigo da tarefa em que deseja atualizar o status: ");
    scanf("%d", &codigo);

    while (aux != NULL) {
        if (aux->info.codigo == codigo) {
            printf("Qual sera o status dessa tarefa (0 para em dia, -1 para pendente: ");
            scanf("%d", &aux->info.status);
            if(aux->info.status == -1)
            {
                if (aux2 == NULL)
                {
                    f->ini = aux->prox;
                } else
                {
                    aux2->prox = aux->prox;
                }

            ListaConcluidas* novoPendente = insereListaConcluida(aux->info, *l);
            if (novoPendente != NULL)
            {
                novoPendente->info2 = aux->info;
                novoPendente->prox2 = *l;
                *l = novoPendente;
                printf("Tarefa concluída e movida para a lista de tarefas concluídas.\n");
            }
            else
            {
                printf("Erro ao alocar memória para o novo nodo concluído.\n");
            }
            }
        }
        aux2 = aux;
        aux = aux->prox;
    }
}

int main()
{
    int opcao;
    int codigo;
    Tarefa novaTarefa;
    Fila* minhaFila = CriaFila();
    ListaConcluidas* concluida = criaListaConcluida();
    ListaConcluidas* pendente = criaListaConcluida();

    do{
    menu();


    scanf("%d",&opcao);
    fflush(stdin);


    switch(opcao)
    {
    case 1:
        novaTarefa = LerTarefa();
        InsereTarefa(minhaFila, novaTarefa.codigo, novaTarefa.nome, novaTarefa.nomeprojeto,
        novaTarefa.inicio, novaTarefa.termino, novaTarefa.status);

        break;

    case 2:
        printf("Digite o codigo da tarefa que deseja modificar: ");
        scanf("%d", &codigo);
        modificarTarefa(minhaFila, codigo);
        break;

    case 3:
        ConcluiTarefa(minhaFila, &concluida);
        break;

    case 4:
        atualizaTarefa(&pendente, minhaFila);
        break;

    case 5:
        imprimeConcluida(pendente);
        aguardarEnter();
        break;

    case 6:
        imprimeConcluida(concluida);
        aguardarEnter();
        break;

    case 7:
        VerificaStatus(concluida);
        aguardarEnter();
        break;

    case 8:
        break;

    default:
        printf("Opcao Invalida");
    }
    }while (opcao != 8);

    printf("\n Fim do Programa!!");

    return 0;
}
