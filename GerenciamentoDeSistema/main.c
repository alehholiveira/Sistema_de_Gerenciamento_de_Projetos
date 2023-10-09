#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "FILA.h"

// !!! ESTA É A VERSÃO AVANÇADA DO PROJETO !!!

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
/*FUNÇÃO QUE FARÁ A LEITURA DAS INFORMAÇÕES DE UMA NOVA TAREFA,
FAZ TAMBÉM A COMPARAÇÃO DE DATAS PARA DETERMINAR SE UMA TAREFA ESTÁ
ATRASADA OU EM DIA

PARÂMETROS: NENHUM;
RETORNO: t -> Tarefa;

*/
    Tarefa t;

    printf("Digite o Codigo da tarefa: ");
    scanf("%d", &t.codigo);

    printf("Digite o nome da tarefa: ");
    scanf("%s", t.nome);

    printf("Digite o nome do projeto: ");
    scanf("%s", t.nomeprojeto);

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
        t.status = 1; // Tarefa atrasada
    } else {
        t.status = 0; // Tarefa em dia
    }

    printf("Digite a prioridade desta tarefa (1 = alta, 2 = normal, 3 = baixa):\n ");
    scanf("%d", &t.prioridade);

    return t;
}

void modificarTarefa(Fila* minhaFilaA, Fila* minhaFilaB, Fila* minhaFilaC,int codigo)
{
/* FUNÇÃO UTILIZADA PARA MODIFICAR AS INFORMAÇÕES DE UMA TAREFA

   PARÂMETROS: minhaFila -> fila de tarefas utilizada para armazenar as informações
               codigo -> inteiro que será utilizado para procurar a tarefa a ser modificada

   RETORNO: NENHUM

*/
    No* temp1 = minhaFilaA->ini;
    No* temp2 = minhaFilaB->ini;
    No* temp3 = minhaFilaC->ini;

    time_t tempo_atual;
    struct tm* data_atual;
    time(&tempo_atual);
    data_atual = localtime(&tempo_atual);

    // LOOP PARA A FILA DE PRIORIDADE ALTA
    while (temp1 != NULL)
    {
        if (temp1->info.codigo == codigo)
            {
            printf("Detalhes da Tarefa:\n");
            printf("Codigo: %d\n", temp1->info.codigo);
            printf("Nome: %s\n", temp1->info.nome);
            printf("Nome do Projeto: %s\n", temp1->info.nomeprojeto);
            printf("Data de Inicio: %d/%d/%d\n", temp1->info.inicio.dia, temp1->info.inicio.mes, temp1->info.inicio.ano);
            printf("Data de termino: %d/%d/%d\n", temp1->info.termino.dia, temp1->info.termino.mes, temp1->info.termino.ano);
            printf("Status: %d\n", temp1->info.status);

            // Modificação dos dados da tarefa
            printf("Digite o novo nome da tarefa: ");
            scanf("%s", temp1->info.nome);

            printf("Digite o nome do projeto: ");
            scanf("%s", temp1->info.nomeprojeto);

            printf("Digite a nova data de Inicio (dia mes ano): ");
            scanf("%d %d %d", &temp1->info.inicio.dia, &temp1->info.inicio.mes, &temp1->info.inicio.ano);

            printf("Digite a nova data de termino (dia mes ano): ");
            scanf("%d %d %d", &temp1->info.termino.dia, &temp1->info.termino.mes, &temp1->info.termino.ano);

            if (temp1->info.termino.ano < (data_atual->tm_year + 1900) ||
                (temp1->info.termino.ano == (data_atual->tm_year + 1900) && temp1->info.termino.mes < (data_atual->tm_mon + 1)) ||
                (temp1->info.termino.ano == (data_atual->tm_year + 1900) && temp1->info.termino.mes == (data_atual->tm_mon + 1) &&
                temp1->info.termino.dia < data_atual->tm_mday)) {
                temp1->info.status = 1; // Tarefa atrasada
            } else {
                temp1->info.status = 0; // Tarefa em dia
            }

            printf("Tarefa modificada com sucesso!\n");
            printf("Detalhes da Tarefa:\n");
            printf("Codigo: %d\n", temp1->info.codigo);
            printf("Nome: %s\n", temp1->info.nome);
            printf("Nome do Projeto: %s\n", temp1->info.nomeprojeto);
            printf("Data de Inicio: %d/%d/%d\n", temp1->info.inicio.dia, temp1->info.inicio.mes, temp1->info.inicio.ano);
            printf("Data de termino: %d/%d/%d\n", temp1->info.termino.dia, temp1->info.termino.mes, temp1->info.termino.ano);
            printf("Status: %d\n", temp1->info.status);


            return;
        }
        temp1 = temp1->prox;
    }

    // LOOP PARA A FILA DE PRIORIDADE NORMAL
    while (temp2 != NULL)
    {
        if (temp2->info.codigo == codigo)
            {
            printf("Detalhes da Tarefa:\n");
            printf("Codigo: %d\n", temp2->info.codigo);
            printf("Nome: %s\n", temp2->info.nome);
            printf("Nome do Projeto: %s\n", temp2->info.nomeprojeto);
            printf("Data de Inicio: %d/%d/%d\n", temp2->info.inicio.dia, temp2->info.inicio.mes, temp2->info.inicio.ano);
            printf("Data de termino: %d/%d/%d\n", temp2->info.termino.dia, temp2->info.termino.mes, temp2->info.termino.ano);
            printf("Status: %d\n", temp2->info.status);

            // Modificação dos dados da tarefa
            printf("Digite o novo nome da tarefa: ");
            scanf("%s", temp2->info.nome);

            printf("Digite o nome do projeto: ");
            scanf("%s", temp2->info.nomeprojeto);

            printf("Digite a nova data de Inicio (dia mes ano): ");
            scanf("%d %d %d", &temp2->info.inicio.dia, &temp2->info.inicio.mes, &temp2->info.inicio.ano);

            printf("Digite a nova data de termino (dia mes ano): ");
            scanf("%d %d %d", &temp2->info.termino.dia, &temp2->info.termino.mes, &temp2->info.termino.ano);

            if (temp2->info.termino.ano < (data_atual->tm_year + 1900) ||
                (temp2->info.termino.ano == (data_atual->tm_year + 1900) && temp2->info.termino.mes < (data_atual->tm_mon + 1)) ||
                (temp2->info.termino.ano == (data_atual->tm_year + 1900) && temp2->info.termino.mes == (data_atual->tm_mon + 1) &&
                temp2->info.termino.dia < data_atual->tm_mday)) {
                temp2->info.status = 1; // Tarefa atrasada
            } else {
                temp2->info.status = 0; // Tarefa em dia
            }

            printf("Tarefa modificada com sucesso!\n");
            printf("Detalhes da Tarefa:\n");
            printf("Codigo: %d\n", temp2->info.codigo);
            printf("Nome: %s\n", temp2->info.nome);
            printf("Nome do Projeto: %s\n", temp2->info.nomeprojeto);
            printf("Data de Inicio: %d/%d/%d\n", temp2->info.inicio.dia, temp2->info.inicio.mes, temp2->info.inicio.ano);
            printf("Data de termino: %d/%d/%d\n", temp2->info.termino.dia, temp2->info.termino.mes, temp2->info.termino.ano);
            printf("Status: %d\n", temp2->info.status);
            return;
        }
        temp2 = temp2->prox;
    }

    // LOOP PARA A FILA DE PRIORIDADE BAIXA
    while (temp3 != NULL)
    {
        if (temp3->info.codigo == codigo)
            {
            printf("Detalhes da Tarefa:\n");
            printf("Codigo: %d\n", temp3->info.codigo);
            printf("Nome: %s\n", temp3->info.nome);
            printf("Nome do Projeto: %s\n", temp3->info.nomeprojeto);
            printf("Data de Inicio: %d/%d/%d\n", temp3->info.inicio.dia, temp3->info.inicio.mes, temp3->info.inicio.ano);
            printf("Data de termino: %d/%d/%d\n", temp3->info.termino.dia, temp3->info.termino.mes, temp3->info.termino.ano);
            printf("Status: %d\n", temp3->info.status);

            // Modificação dos dados da tarefa
            printf("Digite o novo nome da tarefa: ");
            scanf("%s", temp3->info.nome);

            printf("Digite o nome do projeto: ");
            scanf("%s", temp3->info.nomeprojeto);

            printf("Digite a nova data de Inicio (dia mes ano): ");
            scanf("%d %d %d", &temp3->info.inicio.dia, &temp3->info.inicio.mes, &temp3->info.inicio.ano);

            printf("Digite a nova data de termino (dia mes ano): ");
            scanf("%d %d %d", &temp3->info.termino.dia, &temp3->info.termino.mes, &temp3->info.termino.ano);

            if (temp3->info.termino.ano < (data_atual->tm_year + 1900) ||
                (temp3->info.termino.ano == (data_atual->tm_year + 1900) && temp3->info.termino.mes < (data_atual->tm_mon + 1)) ||
                (temp3->info.termino.ano == (data_atual->tm_year + 1900) && temp3->info.termino.mes == (data_atual->tm_mon + 1) &&
                temp3->info.termino.dia < data_atual->tm_mday)) {
                temp3->info.status = 1; // Tarefa atrasada
            } else {
                temp3->info.status = 0; // Tarefa em dia
            }

            printf("Tarefa modificada com sucesso!\n");
            printf("Detalhes da Tarefa:\n");
            printf("Codigo: %d\n", temp3->info.codigo);
            printf("Nome: %s\n", temp3->info.nome);
            printf("Nome do Projeto: %s\n", temp3->info.nomeprojeto);
            printf("Data de Inicio: %d/%d/%d\n", temp3->info.inicio.dia, temp3->info.inicio.mes, temp3->info.inicio.ano);
            printf("Data de termino: %d/%d/%d\n", temp3->info.termino.dia, temp3->info.termino.mes, temp3->info.termino.ano);
            printf("Status: %d\n", temp3->info.status);
            return;
        }
        temp3 = temp3->prox;
    }

    // Se o Codigo da tarefa não foi encontrado
    printf("Tarefa com o codigo %d nao encontrada.\n", codigo);
}

void ConcluiTarefa (Fila* minhaFilaA, Fila* minhaFilaB, Fila* minhaFilaC, ListaConcluidas** l)
{
/* FUNÇÃO QUE RETIRA UMA TAREFA DA FILA PARA INSERÍ-LA EM UMA
LISTA DE TAREFAS CONCLUIDAS, SEM ALTERAR O STATUS DE ATRASADA

   PARÂMETROS: f -> fila de tarefas
               l -> lista que irá receber as tarefas concluídas

   RETORNO: NENHUM
*/
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

            // Insere na nova lista de tarefas concluídas
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
/* FUNÇÃO PARA IMPRIMIR TODOS OS ELEMENTOS DE UMA LISTA

   PARÂMETROS: l -> lista de tarefas, tanto para concluidas como pendente

   RETORNO: NENHUM

*/
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
    int option;

    No *aux = f->ini;
    No *aux2 = NULL;

    ListaConcluidas *aux3 = *l;
    ListaConcluidas *aux4 = NULL;

    printf("Digite o codigo da tarefa em que deseja atualizar o status: ");
    scanf("%d", &codigo);

    while (aux != NULL) {
        if (aux->info.codigo == codigo) {
            printf("Qual sera o status dessa tarefa (0 para em dia, -1 para pendente): ");
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
                printf("Tarefa concluída e movida para a lista de tarefas pendentes.\n");
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

     while (aux3 != NULL) {
        if (aux3->info2.codigo == codigo) {
            printf("Deseja retornar esta tarefa para a fila de tarefas (1 para sim e 0 para nao): ");
            scanf("%d", &option);
            if (option == 1) {
                Tarefa tarefa_temporaria = aux3->info2;
                tarefa_temporaria.status = 0; // Defina o status como 0 (pendente)
                InsereTarefa(f, tarefa_temporaria.codigo, tarefa_temporaria.nome, tarefa_temporaria.nomeprojeto,
                             tarefa_temporaria.inicio, tarefa_temporaria.termino, tarefa_temporaria.status, tarefa_temporaria.prioridade);

                if (aux4 == NULL) {
                    // O elemento a ser removido é o primeiro da lista
                    *l = aux3->prox2;
                } else {
                    aux4->prox2 = aux3->prox2;
                }
                free(aux3);
            }
        }
        aux4 = aux3;
        aux3 = aux3->prox2;
    }
}

int main()
{
    int opcao;
    int codigo;
    Tarefa novaTarefa;

    Fila* minhaFilaAlta = CriaFila();
    Fila* minhaFilaNormal = CriaFila();
    Fila* minhaFilaBaixa = CriaFila();

    ListaConcluidas* concluida = criaListaConcluida();
    ListaConcluidas* pendente = criaListaConcluida();

    do{
    menu();
    imprimeFila(minhaFilaAlta);
    imprimeFila(minhaFilaNormal);
    imprimeFila(minhaFilaBaixa);


    scanf("%d",&opcao);
    fflush(stdin);


    switch(opcao)
    {
    //ADICIONAR TAREFAS
    case 1:
        novaTarefa = LerTarefa();
        if (novaTarefa.prioridade == 1)
        {
            InsereTarefa(minhaFilaAlta, novaTarefa.codigo, novaTarefa.nome, novaTarefa.nomeprojeto,
            novaTarefa.inicio, novaTarefa.termino, novaTarefa.status, novaTarefa.prioridade);
        }

        if (novaTarefa.prioridade == 2)
        {
            InsereTarefa(minhaFilaNormal, novaTarefa.codigo, novaTarefa.nome, novaTarefa.nomeprojeto,
            novaTarefa.inicio, novaTarefa.termino, novaTarefa.status, novaTarefa.prioridade);
        }

        if (novaTarefa.prioridade == 3)
        {
            InsereTarefa(minhaFilaBaixa, novaTarefa.codigo, novaTarefa.nome, novaTarefa.nomeprojeto,
            novaTarefa.inicio, novaTarefa.termino, novaTarefa.status, novaTarefa.prioridade);
        }
        break;

    //MODIFIICAR TAREFAS
    case 2:
        printf("Digite o codigo da tarefa que deseja modificar: ");
        scanf("%d", &codigo);
        modificarTarefa(minhaFilaAlta, minhaFilaNormal, minhaFilaBaixa, codigo);
        break;

    //CONCLUIR TAREFAS, COLOCAR NA LISTA CONCLUIDA
    case 3:
        ConcluiTarefa(minhaFilaAlta, minhaFilaNormal, minhaFilaBaixa, &concluida);
        break;

    //ATUALIZAR TAREFAS, COLOCAR NA LISTA PENDENTE DEPENDENDO DO STATUS
    case 4:
        atualizaTarefa(&pendente, minhaFila);
        break;

    //IMPRIMIR TODAS AS TAREFAS PENDENTES
    case 5:
        imprimeConcluida(pendente);
        aguardarEnter();
        break;

    //IMPRIMIR TODAS AS TAREFAS CONCLUIDAS
    case 6:
        imprimeConcluida(concluida);
        aguardarEnter();
        break;

    //IMPRIME DE FORMA SEPARADA AS TAREFAS CONCLUIDAS
    case 7:
        VerificaStatus(concluida);
        aguardarEnter();
        break;

    //FINALIZA O PROGRAMA
    case 8:
        break;

    default:
        printf("Opcao Invalida");
    }
    }while (opcao != 8);

    printf("\n Fim do Programa!!");
    return 0;
}
