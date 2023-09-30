#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

/* FUNÇÕES DE MANIPULAÇÃO DE PFILA

Fila* CriaFila()  CRIA A FILA

int VaziaFila (Fila* f) VERIFICA SE A FILA ESTÁ VAIZA

void InsereFila (Fila* f, int v) INSERÇÃO

int RetiraFila (Fila* f) REMOÇÃO

Fila* liberaFila (Fila* f) LIBERA A FILA

void imprimeFila (Fila* f)IMPRIME A FILA
*/
typedef struct data
{
    int dia;
    int mes;
    int ano;
} Data;

typedef struct tarefa
{
    int codigo;
    char nome[30];
    char nomeprojeto[30];
    Data inicio;
    Data termino;
    int status;
} Tarefa;


typedef struct nos
{
    Tarefa info;
    struct nos *prox;
}No;

typedef struct fila
{
    No * ini;
    No * fim;
} Fila;

typedef struct listaConcluidas
{
    Tarefa info2;
    struct listaConcluidas* prox2;
} ListaConcluidas;

ListaConcluidas* criaListaConcluida()
{
    return NULL;
}

ListaConcluidas* insereListaConcluida(Tarefa t, ListaConcluidas* l)
{
    ListaConcluidas* aux = (ListaConcluidas*) malloc (sizeof(ListaConcluidas));

    if (aux != NULL)
    {
        aux->info2 = t;
        aux->prox2 = l;
    }
    return aux;
}

int VaziaFila (Fila* f)
{
    if (f->ini==NULL) return 1;
    return 0;

}


Fila* CriaFila ()
{
    Fila* f = (Fila*) malloc(sizeof(Fila));
    f->ini = f->fim = NULL;
    return f;
}

No* ins_fim (No* fim, Tarefa A)
{
    No* p = (No*) malloc(sizeof(No));
    p->info = A;
    p->prox = NULL;
    if (fim != NULL) /* verifica se lista não estava vazia */
    fim->prox = p;
    return p;
}

void InsereTarefa(Fila* f, int codigo, const char* nome, const char* nomeprojeto, Data inicio, Data termino, int status)
{
    Tarefa t;
    t.codigo = codigo;
    strncpy(t.nome, nome, sizeof(t.nome));
    strncpy(t.nomeprojeto, nomeprojeto, sizeof(t.nomeprojeto));
    t.inicio = inicio;
    t.termino = termino;
    t.status = status;

    f->fim = ins_fim(f->fim, t);
    if (f->ini == NULL) /* fila antes vazia? */
        f->ini = f->fim;
}


No* retira_ini (No* ini)
{
    No* p = ini->prox;
    free(ini);
    return p;
}

Tarefa RetiraTarefa(Fila* f)
{
    Tarefa t;
    if (VaziaFila(f))
    {
        printf("Fila vazia.\n");
        exit(0); /* aborta o programa */
    }
    t = f->ini->info;
    f->ini = retira_ini(f->ini);
    if (f->ini == NULL) /* fila ficou vazia? */
        f->fim = NULL;
    return t;
}

void imprimeFila(Fila* f)
{
    No* q;
    printf("\n\t\t");
    for (q = f->ini; q != NULL; q = q->prox)
    {
        printf("Codigo: %d\n", q->info.codigo);
        printf("Nome: %s\n", q->info.nome);
        printf("Nome do Projeto: %s\n", q->info.nomeprojeto);
        printf("Data de Início: %d/%d/%d\n", q->info.inicio.dia, q->info.inicio.mes, q->info.inicio.ano);
        printf("Data de Término: %d/%d/%d\n", q->info.termino.dia, q->info.termino.mes, q->info.termino.ano);
        printf("Status: %d\n", q->info.status);
        printf("\n");
    }
    printf("\n");
}



Fila* liberaFila (Fila* f)
{
    No* q = f->ini;
    while (q!=NULL)
    {
        No* t = q->prox;
        free(q);
        q = t;
    }
    free(f);
    return NULL;
}

#endif // FILA_H_INCLUDED
