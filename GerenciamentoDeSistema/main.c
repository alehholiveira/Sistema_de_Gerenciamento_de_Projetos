#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "FILA.h"

// !!! ESTA É A VERSÃO AVANÇADA DO PROJETO !!! ///

void aguardarEnter()
{
    printf("Pressione Enter para continuar...");
    while (getchar() != '\n'); // Aguarda o usuário pressionar Enter
}

int retornaprioridade(Fila* minhaFilaA, Fila* minhaFilaB, Fila* minhaFilaC, int code, ListaConcluidas* l)
{
    No* temp1 = minhaFilaA->ini;
    No* temp2 = minhaFilaB->ini;
    No* temp3 = minhaFilaC->ini;
    ListaConcluidas* temp4 = l;



    while (temp1 != NULL)
    {
        if (temp1->info.codigo == code)
        {
            return 1;
        }
        temp1 = temp1->prox; // Avança para o próximo elemento
    }

    while (temp2 != NULL)
    {
        if (temp2->info.codigo == code)
        {
            return 2;
        }
        temp2 = temp2->prox; // Avança para o próximo elemento
    }

    while (temp3 != NULL)
    {
        if (temp3->info.codigo == code)
        {
            return 3;
        }
        temp3 = temp3->prox; // Avança para o próximo elemento
    }

    while (temp4 != NULL)
    {
        if (temp4->info2.codigo == code)
        {
            return temp4->info2.prioridade;
        }
        temp4 = temp4->prox2; // Avança para o próximo elemento
    }

    return 0; // Se o código não for encontrado em nenhuma das filas
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
    printf("|   [8] Listar todas as tarefas                      \t|      \n");
    printf("|   [9] Sair do programa                             \t|      \n");
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
    getchar();
    fgets(t.nome, 30, stdin);
    t.nome[strlen(t.nome) - 1] = '\0';  // Remove o caractere de nova linha (\n)


    printf("Digite o nome do projeto: ");
    fgets(t.nomeprojeto, 30, stdin);
    t.nomeprojeto[strlen(t.nomeprojeto) - 1] = '\0';  // Remove o caractere de nova linha (\n)

    printf("Digite a data de Inicio (dia mes ano):\n");
    scanf("%d %d %d", &t.inicio.dia, &t.inicio.mes, &t.inicio.ano);

    printf("Digite a data de termino (dia mes ano):\n");
    scanf("%d %d %d", &t.termino.dia, &t.termino.mes, &t.termino.ano);

    time_t tempo_atual;
    struct tm* data_atual;
    time(&tempo_atual);
    data_atual = localtime(&tempo_atual);

    // Comparar a data de término com a data atual para definir o status
    if (t.termino.ano < (data_atual->tm_year + 1900) ||
            (t.termino.ano == (data_atual->tm_year + 1900) && t.termino.mes < (data_atual->tm_mon + 1)) ||
            (t.termino.ano == (data_atual->tm_year + 1900) && t.termino.mes == (data_atual->tm_mon + 1) &&
             t.termino.dia < data_atual->tm_mday))
    {
        t.status = 1; // Tarefa atrasada
    }
    else
    {
        t.status = 0; // Tarefa em dia
    }

    printf("Digite a prioridade desta tarefa (1 = alta, 2 = normal, 3 = baixa):\n");
    scanf("%d", &t.prioridade);

    return t;
}

void modificarTarefa(Fila* minhaFilaA, int codigo)
{
    /* FUNÇÃO UTILIZADA PARA MODIFICAR AS INFORMAÇÕES DE UMA TAREFA

       PARÂMETROS: minhaFila -> fila de tarefas utilizada para armazenar as informações
                   codigo -> inteiro que será utilizado para procurar a tarefa a ser modificada

       RETORNO: NENHUM

    */

    No* temp1 = minhaFilaA->ini;

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
            getchar();
            fgets(temp1->info.nome, 30, stdin);
            temp1->info.nome[strlen(temp1->info.nome) - 1] = '\0';  // Remove o caractere de nova linha (\n)

            printf("Digite o nome do projeto: ");
            fgets(temp1->info.nomeprojeto, 30, stdin);
            temp1->info.nomeprojeto[strlen(temp1->info.nomeprojeto) - 1] = '\0';  // Remove o caractere de nova linha (\n)


            printf("Digite a nova data de Inicio (dia mes ano): ");
            scanf("%d %d %d", &temp1->info.inicio.dia, &temp1->info.inicio.mes, &temp1->info.inicio.ano);

            printf("Digite a nova data de termino (dia mes ano): ");
            scanf("%d %d %d", &temp1->info.termino.dia, &temp1->info.termino.mes, &temp1->info.termino.ano);

            if (temp1->info.termino.ano < (data_atual->tm_year + 1900) ||
                    (temp1->info.termino.ano == (data_atual->tm_year + 1900) && temp1->info.termino.mes < (data_atual->tm_mon + 1)) ||
                    (temp1->info.termino.ano == (data_atual->tm_year + 1900) && temp1->info.termino.mes == (data_atual->tm_mon + 1) &&
                     temp1->info.termino.dia < data_atual->tm_mday))
            {
                temp1->info.status = 1; // Tarefa atrasada
            }
            else
            {
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



    // Se o Codigo da tarefa não foi encontrado
    printf("Tarefa com o codigo %d nao encontrada.\n", codigo);
}

void ConcluiTarefa (Fila* minhaFilaA, ListaConcluidas** l, int codigo)
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




    No *aux1 = minhaFilaA->ini;
    No *aux2 = NULL;
    while (aux1 != NULL)
    {
        if (aux1->info.codigo == codigo)
        {
            // Atualizar a data de término da tarefa com a data atual
            aux1->info.termino.dia = data_atual.tm_mday;
            aux1->info.termino.mes = data_atual.tm_mon + 1;
            aux1->info.termino.ano = data_atual.tm_year + 1900;

            // Remover a tarefa concluída da fila
            if (aux2 == NULL)
            {
                minhaFilaA->ini = aux1->prox;
            }
            else
            {
                aux2->prox = aux1->prox;
            }

            // Insere na nova lista de tarefas concluídas
            ListaConcluidas* novoConcluida = insereListaConcluida(aux1->info, *l);
            if (novoConcluida != NULL)
            {
                novoConcluida->info2 = aux1->info;
                novoConcluida->prox2 = *l;
                *l = novoConcluida;
                printf("Tarefa concluida e movida para a lista de tarefas concluidas.\n");

            }

            else
            {
                printf("Erro ao alocar memoria para o novo nodo concluido.\n");
            }
        }
        aux2 = aux1;
        aux1 = aux1->prox;
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
    while (q != NULL)
    {
        printf("\nCodigo: %d\n", q->info2.codigo);
        printf("Nome: %s\n", q->info2.nome);
        printf("Nome do Projeto: %s\n", q->info2.nomeprojeto);
        printf("Data de Inicio: %d/%d/%d\n", q->info2.inicio.dia, q->info2.inicio.mes, q->info2.inicio.ano);
        printf("Data de Termino: %d/%d/%d\n", q->info2.termino.dia, q->info2.termino.mes, q->info2.termino.ano);
        printf("Status: %d\n", q->info2.status);
        printf("Prioridade: %d\n", q->info2.prioridade);
        printf("\n");
        q = q->prox2;
    }
    printf("\n");
}

void ordenarListaPorPrioridade(ListaConcluidas** l)
{
    ListaConcluidas* atual;
    int trocou;

    if (*l == NULL)
        return;

    do
    {
        trocou = 0;
        atual = *l;

        while (atual->prox2 != NULL)
        {
            if (atual->info2.prioridade > atual->prox2->info2.prioridade)
            {
                Tarefa temp = atual->info2;
                atual->info2 = atual->prox2->info2;
                atual->prox2->info2 = temp;
                trocou = 1;
            }
            atual = atual->prox2;
        }
    }
    while (trocou);
}

void atualizaTarefa(ListaConcluidas** l, Fila* f, int codigo)
{
    int option;
    No *aux = f->ini;
    No *aux2 = NULL;
    ListaConcluidas *aux3 = *l;
    ListaConcluidas *aux4 = NULL;

    while (aux != NULL)
    {
        if (aux->info.codigo == codigo)
        {
            printf("Qual sera o status dessa tarefa (0 para em dia, -1 para pendente): ");
            scanf("%d", &aux->info.status);
            if (aux->info.status == -1)
            {
                if (aux2 == NULL)
                {
                    f->ini = aux->prox;
                }
                else
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
                // Retorna após mover a tarefa
            }
        }
        aux2 = aux;
        aux = aux->prox;
    }

    while (aux3 != NULL)
    {
        if (aux3->info2.codigo == codigo)
        {
            printf("Deseja retornar esta tarefa para a fila de tarefas (1 para sim e 0 para nao): ");
            scanf("%d", &option);
            if (option == 1)
            {
                Tarefa tarefa_temporaria = aux3->info2;
                tarefa_temporaria.status = 0; // Defina o status como 0 (pendente)
                InsereTarefa(f, tarefa_temporaria.codigo, tarefa_temporaria.nome, tarefa_temporaria.nomeprojeto,
                             tarefa_temporaria.inicio, tarefa_temporaria.termino, tarefa_temporaria.status, tarefa_temporaria.prioridade);

                if (aux4 == NULL)
                {
                    // O elemento a ser removido o primeiro da lista
                    *l = aux3->prox2;
                }
                else
                {
                    aux4->prox2 = aux3->prox2;
                }
                free(aux3);
            }
        }
        aux4 = aux3;
        aux3 = aux3->prox2;
    }

    // Se a tarefa não foi encontrada em nenhum lugar
    printf("Tarefa com o código não encontrada em nenhuma lista.\n");
}

int main()
{
    int opcao;
    int codigo;
    int prioridade;
    Tarefa novaTarefa;

    Fila* minhaFilaAlta = CriaFila();
    Fila* minhaFilaNormal = CriaFila();
    Fila* minhaFilaBaixa = CriaFila();

    ListaConcluidas* concluida = criaListaConcluida();
    ListaConcluidas* pendente = criaListaConcluida();

    Data inicio1 = {11, 11, 2022};
    Data termino1 = {15, 4, 2023};
    Data inicio2 = {12, 12, 2022};
    Data termino2 = {15, 4, 2023};
    Data inicio3 = {13, 1, 2023};
    Data termino3 = {15, 4, 2023};
    Data inicio4 = {14, 2, 2023};
    Data termino4 = {15, 4, 2023};

    // Adicionar tarefas durante a inicialização
    InsereTarefa(minhaFilaAlta, 1, "Tarefa 1", "Projeto 1", inicio1, termino1, 0, 1);
    InsereTarefa(minhaFilaAlta, 2, "Tarefa 2", "Projeto 1", inicio2, termino2, 0, 1);
    InsereTarefa(minhaFilaNormal, 3, "Tarefa 3", "Projeto 2", inicio3, termino3, 0, 2);
    InsereTarefa(minhaFilaBaixa, 4, "Tarefa 4", "Projeto 2", inicio4, termino4, 0, 3);
    do
    {
        menu();



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
            prioridade = retornaprioridade(minhaFilaAlta, minhaFilaNormal, minhaFilaBaixa, codigo, pendente);
            if (prioridade == 1)
            {
                modificarTarefa(minhaFilaAlta, codigo);
            }

            if (prioridade == 2)
            {
                modificarTarefa(minhaFilaNormal, codigo);
            }

            if (prioridade == 3)
            {
                modificarTarefa(minhaFilaBaixa, codigo);
            }

            break;

        //CONCLUIR TAREFAS, COLOCAR NA LISTA CONCLUIDA
        case 3:
            printf("Digite o codigo da tarefa que deseja concluir: ");
            scanf("%d", &codigo);
            prioridade = retornaprioridade(minhaFilaAlta, minhaFilaNormal, minhaFilaBaixa, codigo, pendente);
            if (prioridade == 1)
            {
                ConcluiTarefa(minhaFilaAlta, &concluida, codigo);
            }

            if (prioridade == 2)
            {
                ConcluiTarefa(minhaFilaNormal, &concluida, codigo);
            }

            if (prioridade == 3)
            {
                ConcluiTarefa(minhaFilaBaixa, &concluida, codigo);
            }

            break;

        //ATUALIZAR TAREFAS, COLOCAR NA LISTA PENDENTE DEPENDENDO DO STATUS
        case 4:
            printf("Digite o codigo da tarefa que deseja atualizar o status: ");
            scanf("%d", &codigo);
            prioridade = retornaprioridade(minhaFilaAlta, minhaFilaNormal, minhaFilaBaixa, codigo, pendente);
            if (prioridade == 1)
            {
                atualizaTarefa(&pendente, minhaFilaAlta, codigo);
            }

            if (prioridade == 2)
            {
                atualizaTarefa(&pendente, minhaFilaNormal, codigo);
            }

            if (prioridade == 3)
            {
                atualizaTarefa(&pendente, minhaFilaBaixa, codigo);
            }
            ordenarListaPorPrioridade(&pendente);

            break;

        //IMPRIMIR TODAS AS TAREFAS PENDENTES
        case 5:
            printf("\n\t\t");
            printf("Lista pendente");
            imprimeConcluida(pendente);
            aguardarEnter();
            break;

        //IMPRIMIR TODAS AS TAREFAS CONCLUIDAS
        case 6:
            printf("\n\t\t");
            printf("Lista concluida");
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
            imprimeFila(minhaFilaAlta);
            imprimeFila(minhaFilaNormal);
            imprimeFila(minhaFilaBaixa);
            aguardarEnter();
            break;

        case 9:
            break;

        default:
            printf("Opcao Invalida");
        }
    }
    while (opcao != 9);

    printf("\n Fim do Programa!!");
    return 0;
}
