#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

/* FUNCOES DE MANIPULACAO DE FILA

Fila* criaFila()  CRIA A FILA

bool vaziaFila (Fila* f) VERIFICA SE A FILA ESTA VAIZA, RETORNA TRUE SE SIM

void insereFila (Fila* f, int v) INSERSAO

int retiraFila (Fila* f) REMOCAO

void imprimeFilaComCheckHora (Fila* f) IMPRIME A FILA COM A VARIAVEL CHECK_HORA

void imprimeFila (Fila* f) IMPRIME A FILA SEM A VARIAVEL CHECK_HORA

Fila* liberaFila (Fila* f) LIBERA A FILA

int tamanhoFila (Fila* f) RETORNA O TAMANHO DA FILA

*/

typedef struct Horario {
    int hora;
    int minuto;
    int dia;
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


Fila* criaFila () {
    Fila* f = (Fila*) malloc(sizeof(Fila));
    f->ini = f->fim = NULL;
    return f;
}

bool vaziaFila (Fila* f) {
    if (f->ini == NULL) return true;
    return false;
}

No* ins_fim (No *fim, char codigo[5], Horario horario, int numPassageiros, int checkHora) {
    No *p = (No*)malloc(sizeof(No));
    strcpy(p->codigo, codigo);
    p->horario = horario;
    p->numPassageiros = numPassageiros;
    p->checkHora = checkHora;
    p->prox = NULL;
    if (fim != NULL) /* verifica se lista nao estava vazia */
    fim->prox = p;
    return p;
}

void insereFila (Fila* f, char codigo[5], Horario horario, int numPassageiros, int checkHora) {
    f->fim = ins_fim(f->fim, codigo, horario, numPassageiros, checkHora);
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

void imprimeFilaComCheckHora (Fila* f) {
    system("cls");
    No* q;
    printf("\n\t\tCodigo\t\tHorario \tNumero de Passageiros\t\tCheck-Hora\n\n");
    for (q=f->ini; q!=NULL; q=q->prox)
    {
        if(q->checkHora == -1)  printf("\t\t%s\t\t%.2d:%.2d\t\t\t%d \t \t \t   %d\n\n",q->codigo, q->horario.hora, q->horario.minuto, q->numPassageiros, q->checkHora);
        else{
            printf("\t\t%s\t\t%.2d:%.2d\t\t\t%d \t \t \t    %d\n\n",q->codigo, q->horario.hora, q->horario.minuto, q->numPassageiros, q->checkHora);
        }
    }
    printf("\n\n");
}

void imprimeFila (Fila* f) {
    No* q;
    printf("\n\t\tCodigo\t\tHorario \tNumero de Passageiros\n\n");
    for (q=f->ini; q!=NULL; q=q->prox)
    {
        printf("\t\t%s\t\t%.2d:%.2d\t\t\t%d\n\n",q->codigo, q->horario.hora, q->horario.minuto, q->numPassageiros);
    }
    printf("\n\n");
}

Fila* liberaFila (Fila* f) {
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