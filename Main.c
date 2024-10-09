#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <locale.h>
#include <time.h>
#include <math.h>
#include "FILA.h"
#include "UTILITIES.h"


int main() {

    setlocale(LC_ALL, "Portuguese");
    char input[10];    //String que vai registrar a seed

    printf("\n\tDigite a seed desejada para gera��o dos numeros: ");    //Leitura da seed
    fgets(input, sizeof(input), stdin);

    unsigned int seed = string_to_seed(input);  //Transforma a string em um int
    srand(seed);   // Inicializa a seed

    Fila *emergencia = NULL;        //Cria��o das filas
    emergencia = criaFila();

    Fila *normal = NULL;
    normal = criaFila();

    Fila *pouso = NULL;
    pouso = criaFila();

    Horario horarioSistema;         //Cria��o do horario local
    horarioSistema.hora = randomInteger(23,1);      //Gera um horario local aleatorio 
    horarioSistema.minuto = randomInteger(59,1);
    
    char opcao[3];
    int opcaoNum = 0;

    Horario horaEsperada;
    char codVoo[5];
    int numPassageiros;
    int optEmergencia;
    int minutos;

    char inputMinutos[5];

    while (opcaoNum != 7) {
        do{
            system("cls");
            printf("\n\tHor�rio atual: %.2d:%.2d\n", horarioSistema.hora, horarioSistema.minuto);
            printf("\n\t\t1. Inserir uma aeronave � fila de espera para o pouso\n");
            printf("\t\t2. Autorizar uma aeronave a pousar\n");
            printf("\t\t3. Imprimir um Relat�rio com as aeronaves na fila para pouso\n");
            printf("\t\t4. Imprimir a pr�xima aeronave que ser� autorizada a pousar\n");
            printf("\t\t5. Imprimir todos os voos que j� pousaram\n");
            printf("\t\t6. Simular o processamento de pouso\n");
            printf("\t\t7. Finalizar o sistema\n");
            printf("\n\tOp��o: ");
            fflush(stdin);
            fgets(opcao, sizeof(opcao), stdin);
            opcaoNum = atoi(opcao);
            if(!digitCheck(opcao) || outOfRange(opcaoNum,8,0))    printf("\n\n\tErro! \t Digite um n�mero!\n\n");
        }while(!digitCheck(opcao) || outOfRange(opcaoNum,8,0));


        system("cls");
        switch (opcaoNum) {
            case 1:
                randomAlphaNumeric(codVoo);
                printf("\tVoo %s\n\n",codVoo);
                horaEsperada = passTime(horarioSistema, randomInteger(100, -100));
                printf("\t\tHor�rio de chegada esperado: %.2d:%.2d\n", horaEsperada.hora, horaEsperada.minuto);
                numPassageiros = randomInteger(200, 50);
                printf("\t\tN�mero de passageiros: %d\n", numPassageiros);
                optEmergencia = randomInteger(10, 0)<4 ? 1 : 0;
                printf("\t\tVoo de emerg�ncia? %s\n", optEmergencia ? "Sim" : "N�o");

                if(optEmergencia)  insereFila(emergencia,codVoo,horaEsperada,numPassageiros, -2);
                else {
                    insereFila(normal,codVoo,horaEsperada,numPassageiros, -2);
                }
                system("pause");
                break;

            case 2:
                if (!vaziaFila(emergencia)) {
                    No* aux = retiraFila(emergencia);
                    aux->checkHora = -1;
                    insereFila(pouso, aux->codigo, aux->horario, aux->numPassageiros, aux->checkHora);
                    horarioSistema = passTime(horarioSistema, 10);
                } else if (!vaziaFila(normal)) {
                    No* aux = retiraFila(normal);
                    if(comparaHorario(passTime(horarioSistema, 15), aux->horario)) aux->checkHora = 1;
                    else aux->checkHora = 0;
                    insereFila(pouso, aux->codigo, aux->horario, aux->numPassageiros, aux->checkHora);
                    horarioSistema = passTime(horarioSistema, 10);
                } else {
                    printf("\n\tN�o h� voos previstos");
                }
                break;

            case 3:
                printf("\t \t LISTA DE VOOS DE EMERG�NCIA \n");
                if(!vaziaFila(emergencia))
                {
                    imprimeFila(emergencia);
                }
                else
                {
                    printf("\n\t\tNenhum voo de emerg�ncia em espera\n\n\n");
                }
                printf("\t \t LISTA DE VOOS \n");
                if(!vaziaFila(normal))
                {
                    imprimeFila(normal);
                }
                else
                {
                    printf("\n\t Nenhum voo em espera\n\n\n");
                }
                system("pause");
                break;

            case 4:
                ProximoVooPrint(emergencia,normal);
                system("pause");
                break;
            case 5:
                imprimeFilaComCheckHora(pouso);
                system("pause");
                break;
            case 6:
                do {
                    printf("\n\n\tInsira o tempo a avan�ar (em minutos): ");
                    fflush(stdin);
                    fgets(inputMinutos, sizeof(inputMinutos), stdin);
                    minutos = atoi(inputMinutos);
                    if (outOfRange(minutos,999,1) || !digitCheck(inputMinutos))     printf("\n\n\tO n�mero de minuto tem que ser no m�nimo 1 e no m�ximo 999!\n\n");
                } while(outOfRange(minutos,999,1) || !digitCheck(inputMinutos));

                Horario horarioFinal = passTime(horarioSistema, minutos);
                Horario horarioSimulado = horarioSistema;

                Fila* aux = criaFila();
                No* aux1 = emergencia->ini;
                while(aux1 != NULL && comparaHorario(horarioSimulado, horarioFinal)) {
                    printf("\n\n\tHor�rio de autoriza��o: %.2d:%.2d", horarioSimulado.hora, horarioSimulado.minuto);
                    aux1->checkHora = -1;
                    insereFila(aux, aux1->codigo, aux1->horario, aux1->numPassageiros, aux1->checkHora);
                    horarioSimulado = passTime (horarioSimulado, 10);
                    aux1 = aux1->prox;
                }
                aux1 = normal->ini;
                while(aux1 != NULL && comparaHorario(horarioSimulado, horarioFinal)) {
                    printf("\n\n\tHor�rio de autoriza��o: %.2d:%.2d", horarioSimulado.hora, horarioSimulado.minuto);
                    if(comparaHorario(passTime(aux1->horario, 15), horarioSimulado)) aux1->checkHora = 1;
                    else aux1->checkHora = 0;
                    insereFila(aux, aux1->codigo, aux1->horario, aux1->numPassageiros, aux1->checkHora);
                    horarioSimulado = passTime(horarioSimulado, 10);
                    aux1 = aux1->prox;
                }
                imprimeFilaComCheckHora(aux);
                aux = liberaFila(aux);
                free(aux);
                system("pause");
                break;
            case 8:
                printf("FILA NORMAL\n");
                imprimeFilaComCheckHora(normal);
                printf("FILA EMERG�NCIA\n");
                imprimeFilaComCheckHora(emergencia);
                printf("FILA POUSADOS\n");
                imprimeFilaComCheckHora(pouso);
                system("pause");
                break;
            default:
                printf("\n\n\t Digite uma op��o v�lida\n\n");
                system("pause");
                break;
        }
    }
    return 0;
}