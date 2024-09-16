#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

/* FUNCOES DE MANIPULACAO DE FILA

Fila* CriaFila()  CRIA A FILA

int VaziaFila (Fila* f) VERIFICA SE A FILA ESTA VAIZA

void InsereFila (Fila* f, int v) INSERSAO

int RetiraFila (Fila* f) REMOCAO

Fila* liberaFila (Fila* f) LIBERA A FILA

void imprimeFila (Fila* f) IMPRIME A FILA

*/

typedef struct Horario {
    int hora;
    int minuto;
} Horario;

typedef struct No {
    char codigo[4];
    Horario horario;
    int numPassageiros;
    int checkHora;
    struct No *prox;
} No;

typedef struct fila {
    No * ini;
    No * fim;
} Fila;


int VaziaFila (Fila* f) {
    if (f->ini == NULL) return 1;
    return 0;
}

Fila* CriaFila () {
    Fila* f = (Fila*) malloc(sizeof(Fila));
    f->ini = f->fim = NULL;
    return f;
}

No* ins_fim (No *fim, char codigo[4], Horario horario, int numPassageiros) {
    No *p = (No*)malloc(sizeof(No));
    strcpy(codigo, p->codigo);
    p->horario = horario;
    p->numPassageiros = numPassageiros;
    p->prox = NULL;
    if (fim != NULL) /* verifica se lista nao estava vazia */
    fim->prox = p;
    return p;
}

void InsereFila (Fila* f, char codigo[4], Horario horario, int numPassageiros) {
    f->fim = ins_fim(f->fim, codigo, horario, numPassageiros);
    if (f->ini==NULL) /* fila antes vazia? */
    f->ini = f->fim;
}

No* retira_ini (No* ini) {
    No* p = ini->prox;
    free(ini);            //TODO: passar pra outra fila
    return p;
}

void RetiraFila (Fila* f) {
    char codigo[4];
    Horario horario;
    int numPassageiros;
    if (VaziaFila(f))
    {
        printf("Fila vazia.\n");
        exit(0); /* aborta programa */
    }
    strcpy(codigo, f->ini->codigo);
    horario = f->ini->horario;
    numPassageiros = f->ini->numPassageiros;
    f->ini = retira_ini(f->ini);
    if (f->ini == NULL) /* fila ficou vazia? */
    f->fim = NULL;
    return;
}

void imprimeFila (Fila* f)
{
    No* q;
    printf("\n\t\t");
    for (q=f->ini; q!=NULL; q=q->prox)
    {
        printf("%s\t%d:%d\t%d\n",q->codigo, q->horario.hora, q->horario.minuto, q->numPassageiros);
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

int vaziaFila(Fila *f)
{
    if (f->ini==NULL)
    {
        return 1; //fila vazia
    }
    return 0;
}


int tamanhoFila(Fila* f) {
    int count = 0;
    for (No* aux = f->ini; aux != NULL; aux = aux->prox) {
        count++;
    }
    return count;
}


#endif // FILA_H_INCLUDED