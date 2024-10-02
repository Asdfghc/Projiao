#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <locale.h>
#include <time.h>
#include "FILA.h"
#include "UTILITIES.h"


int main() {

    setlocale(LC_ALL, "Portuguese");
    char input[10];    //String que vai registrar a seed

    printf("\n\tDigite a seed desejada para geração dos numeros: ");    //Leitura da seed
    fgets(input, sizeof(input), stdin);

    unsigned int seed = string_to_seed(input);  //Transforma a string em um int
    srand(seed);   // Inicializa a seed

    Fila *emergencia = NULL;        //Criação das filas
    emergencia = criaFila();

    Fila *normal = NULL;
    normal = criaFila();

    Fila *pouso = NULL;
    pouso = criaFila();

    Horario horarioSistema;         //Criação do horario local
    horarioSistema.hora = randomInteger(23,1);      //Gera um horario local aleatorio 
    horarioSistema.minuto = randomInteger(59,1);
    
    int opcaoNum = 0;
    char opcao[3];

    Horario horaEsperada;
    char codVoo[5];
    int optEmergencia;
    int minutos;

    char inputHora[4];
    char inputMinuto[4];
    char inputPassageiros[5];
    char inputEmergencia[3];
    char inputMinutos[5];

    while (opcaoNum != 7) {
        do{
            system("cls");
            printf("\n\tHorário atual: %.2d:%.2d\n", horarioSistema.hora, horarioSistema.minuto);
            printf("\n\t\t1. Inserir uma aeronave à fila de espera para o pouso\n");
            printf("\t\t2. Autorizar uma aeronave a pousar\n");
            printf("\t\t3. Imprimir um Relatório com as aeronaves na fila para pouso\n");
            printf("\t\t4. Imprimir a próxima aeronave que será autorizada a pousar\n");
            printf("\t\t5. Imprimir todos os voos que já pousaram\n");
            printf("\t\t6. Simular o processamento de pouso\n");
            printf("\t\t7. Finalizar o sistema\n");
            printf("\n\tOpção: ");
            fflush(stdin);
            fgets(opcao, sizeof(opcao), stdin);
            opcaoNum = atoi(opcao);
            if(!digitCheck(opcao) || outOfRange(opcaoNum,8,0))    printf("\n\n\tErro! \t Digite um número!\n\n");
        }while(!digitCheck(opcao) || outOfRange(opcaoNum,8,0));


        system("cls");
        switch (opcaoNum) {
            case 1:
                randomAlphaNumeric(codVoo);
                printf("\tVoo %s\n\n",codVoo);
                int IinputHora;
                int IinputMinuto;
                do{
                    printf("\tHorário previsto de chegada: \n\t\tHora: ");
                    fflush(stdin);
                    fgets(inputHora, sizeof(inputHora), stdin);
                    IinputHora = atoi(inputHora);
                    printf("\t\tMinuto: ");
                    fflush(stdin);
                    fgets(inputMinuto, sizeof(inputMinuto), stdin);
                    IinputMinuto = atoi(inputMinuto);
                    if(outOfRange(IinputHora,23,0) || outOfRange(IinputMinuto,59,0) || !digitCheck(inputHora) || !digitCheck(inputMinuto))    printf("\n\n\tHorário inválido!\n\n");
                } while(outOfRange(IinputHora,23,0) || outOfRange(IinputMinuto,59,0) || !digitCheck(inputHora) || !digitCheck(inputMinuto));
                horaEsperada.hora = IinputHora;
                horaEsperada.minuto = IinputMinuto;
                
                
                int IinputPassageiros;
                do {
                    printf("\t\tNúmero de passageiros: ");
                    fflush(stdin);
                    fgets(inputPassageiros, sizeof(inputPassageiros), stdin);
                    IinputPassageiros = atoi(inputPassageiros);
                    if(outOfRange(IinputPassageiros,200,50) || !digitCheck(inputPassageiros))    printf("\n\n\tO número de passageiros tem que ser no mínimo 50 e no máximo 200!\n\n");
                } while(outOfRange(IinputPassageiros,200,50) || !digitCheck(inputPassageiros));

                do {
                    printf("\n\t\tNecessita de um pouso de emergência?\n(0 - Não, 1 - Sim)\n\t\tR: ");
                    fflush(stdin);
                    fgets(inputEmergencia, sizeof(inputEmergencia), stdin);
                    optEmergencia = atoi(inputEmergencia);
                    if(outOfRange(optEmergencia,1,0) || !digitCheck(inputEmergencia))    printf("\n\n\tApenas 0 ou 1!\n\n");
                } while(outOfRange(optEmergencia,1,0) || !digitCheck(inputEmergencia));

                if(optEmergencia)  insereFila(emergencia,codVoo,horaEsperada,IinputPassageiros);
                else {
                    insereFila(normal,codVoo,horaEsperada,IinputPassageiros);
                }

                break;

            case 2:
                if (!vaziaFila(emergencia)) {
                    No* aux = retiraFila(emergencia);
                    aux->checkHora = -1;
                    insereFila(pouso, aux->codigo, aux->horario, aux->numPassageiros);
                    horarioSistema = passTime(horarioSistema, 10);
                } else if (!vaziaFila(normal)) {
                    No* aux = retiraFila(normal);
                    if(!comparaHorario(passTime(horarioSistema, 15), aux->horario))   aux->checkHora = 0;
                    else {
                        aux->checkHora = 1;
                    }
                    insereFila(pouso, aux->codigo, aux->horario, aux->numPassageiros);
                    horarioSistema = passTime(horarioSistema, 10);
                } else {
                    printf("\n\tNão há voos previstos");
                }
                break;

            case 3:
                printf("\t \t LISTA DE VOOS DE EMERGÊNCIA \n");
                if(!vaziaFila(emergencia))
                {
                    imprimeFila(emergencia);
                }
                else
                {
                    printf("\n\t\tNenhum voo de emergência em espera\n\n\n");
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
                    printf("\n\n\tInsira o tempo a avançar (em minutos): ");
                    fflush(stdin);
                    fgets(inputMinutos, sizeof(inputMinutos), stdin);
                    minutos = atoi(inputMinutos);
                    if (outOfRange(minutos,999,1) || !digitCheck(inputMinutos))     printf("\n\n\tO número de minuto tem que ser no mínimo 1 e no máximo 999!\n\n");
                } while(outOfRange(minutos,999,1) || !digitCheck(inputMinutos));

                Horario horarioFinal = passTime(horarioSistema, minutos);
                Horario horarioSimulado = horarioSistema;

                Fila* aux = criaFila();
                No* aux1 = emergencia->ini;
                while(aux1 != NULL && comparaHorario(horarioSimulado, horarioFinal)) {
                    printf("\n\n\tHorário de autorização: %.2d:%.2d", horarioSimulado.hora, horarioSimulado.minuto);
                    insereFila(aux, aux1->codigo, aux1->horario, aux1->numPassageiros);
                    aux->fim->checkHora = -1;
                    horarioSimulado = passTime (horarioSimulado, 10);
                    aux1 = aux1->prox;
                }
                aux1 = normal->ini;
                while(aux1 != NULL && comparaHorario(horarioSimulado, horarioFinal)) {
                    printf("\n\n\tHorário de autorização: %.2d:%.2d", horarioSimulado.hora, horarioSimulado.minuto);
                    insereFila(aux, aux1->codigo, aux1->horario, aux1->numPassageiros);
                    if(comparaHorario(passTime(aux1->horario, 15), horarioSimulado)) aux->fim->checkHora = 1;
                    else {aux->fim->checkHora = 0;}
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
                printf("FILA EMERGÊNCIA\n");
                imprimeFilaComCheckHora(emergencia);
                printf("FILA POUSADOS\n");
                imprimeFilaComCheckHora(pouso);
                system("pause");
                break;
            default:
                printf("\n\n\t Digite uma opção válida\n\n");
                system("pause");
                break;
        }
    }
    return 0;
}