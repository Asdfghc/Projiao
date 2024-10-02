#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

/* FUNCOES DE MANIPULACAO DE FILA

Fila* criaFila()  CRIA A FILA

int vaziaFila (Fila* f) VERIFICA SE A FILA ESTA VAIZA

void insereFila (Fila* f, int v) INSERSAO

int retiraFila (Fila* f) REMOCAO

void imprimeFilaComCheckHora (Fila* f) IMPRIME A FILA COM O CHECK_HORA

void imprimeFila (Fila* f) IMPRIME A FILA

Fila* liberaFila (Fila* f) LIBERA A FILA

int tamanhoFila (Fila* f) RETORNA O TAMANHO DA FILA

*/

typedef struct Horario {
    int hora;
    int minuto;
} Horario;

typedef struct No {
    char codigo[5];
    Horario horario;
    int numPassageiros;
    int checkHora;
    struct No *prox;
} No;

typedef struct fila {
    No * ini;
    No * fim;
} Fila;


bool vaziaFila (Fila* f) {
    if (f->ini == NULL) return true;
    return false;
}

Fila* criaFila () {
    Fila* f = (Fila*) malloc(sizeof(Fila));
    f->ini = f->fim = NULL;
    return f;
}

No* ins_fim (No *fim, char codigo[5], Horario horario, int numPassageiros) {
    No *p = (No*)malloc(sizeof(No));
    strcpy(p->codigo, codigo);
    p->horario = horario;
    p->numPassageiros = numPassageiros;
    p->prox = NULL;
    if (fim != NULL) /* verifica se lista nao estava vazia */
    fim->prox = p;
    return p;
}

void insereFila (Fila* f, char codigo[5], Horario horario, int numPassageiros) {
    f->fim = ins_fim(f->fim, codigo, horario, numPassageiros);
    if (f->ini==NULL) /* fila antes vazia? */
    f->ini = f->fim;
}

No* retiraFila (Fila* f) {
    if (vaziaFila(f))
    {
        printf("Fila vazia.\n");
        exit(0); /* aborta programa */
    }
    No* aux = f->ini;
    f->ini = f->ini->prox;
    if (f->ini == NULL) /* fila ficou vazia? */
    f->fim = NULL;
    return aux;
}

void imprimeFilaComCheckHora (Fila* f)
{
    No* q;
    printf("\n\t\tCódigo\tHorário\t Número de Passageiros\n\n");
    for (q=f->ini; q!=NULL; q=q->prox)
    {
        printf("\t\t%s\t%.2d:%.2d\t%d\t%d\n",q->codigo, q->horario.hora, q->horario.minuto, q->numPassageiros, q->checkHora);
    }
    printf("\n");
}

void imprimeFila (Fila* f)
{
    No* q;
    printf("\n\t\tCódigo\tHorário\t Número de Passageiros\n\n");
    for (q=f->ini; q!=NULL; q=q->prox)
    {
        printf("\t\t%s\t%.2d:%.2d\t%d\n",q->codigo, q->horario.hora, q->horario.minuto, q->numPassageiros);
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

int tamanhoFila(Fila* f) {
    int count = 0;
    for (No* aux = f->ini; aux != NULL; aux = aux->prox) {
        count++;
    }
    return count;
}


#endif // FILA_H_INCLUDED