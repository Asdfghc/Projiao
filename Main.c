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
    char input[100];    //String que vai registrar a seed

    printf("\n\tDigite a seed desejada para geração dos numeros: ");    //Leitura da seed
    scanf("%s",input);

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
    
    int minutos; 
    int opcaoNum = 0;
    char opcao[2];

    Horario horaEsperada;
    char codVoo[5];
    int numeroPassageiro, optEmergencia;

    while (opcaoNum != 7) {
        do{
            printf("Horário atual: %.2d:%.2d\n", horarioSistema.hora, horarioSistema.minuto);
            printf("1. Inserir uma aeronave à fila de espera para o pouso\n");
            printf("2. Autorizar uma aeronave a pousar\n");
            printf("3. Imprimir um Relatório com as aeronaves na fila para pouso\n");
            printf("4. Imprimir a próxima aeronave que será autorizada a pousar\n");
            printf("5. Imprimir todos os voos que já pousaram\n");
            printf("6. Simular o processamento de pouso\n");
            printf("7. Finalizar o sistema\n");
            scanf("%s", opcao);
            if(!digitCheck(opcao))    printf("\n\n\tErro! \t Digite um numero!\n\n");
        }while(!digitCheck(opcao));

        opcaoNum = atoi(opcao);

        switch (opcaoNum) {
            case 1:
                randomAlphaNumeric(codVoo);
                printf("Voo %s\n\n",codVoo);
                do{
                    printf("\tHorario previsto de chegada: \n\tHora: ");
                    scanf("%d",&horaEsperada.hora);
                    printf("\tMinuto: ");
                    scanf("%d",&horaEsperada.minuto);
                    if(outOfRange(horaEsperada.hora,23,0) || outOfRange(horaEsperada.minuto,59,0))    printf("\n\n\tHorario Invalido!\n\n");
                }while(outOfRange(horaEsperada.hora,23,0) || outOfRange(horaEsperada.minuto,59,0));
                
                do {
                    printf("\tNumero de passageiros: ");
                    scanf("%d",&numeroPassageiro);
                    if(outOfRange(numeroPassageiro,200,50))    printf("\n\n\tO numero de passageiros tem que ter no minimo 50 e no maximo 200!\n\n");
                } while(outOfRange(numeroPassageiro,200,50));
                
                do {
                    printf("\n\tNecessita de um pouso de emergência?\n(0 - Não, 1 - Sim)\n\t\tR: ");
                    scanf("%d",&optEmergencia);
                    if(outOfRange(optEmergencia,1,0))    printf("\n\n\tApenas 0 ou 1\n\n");
                } while(outOfRange(optEmergencia,1,0));

                if(optEmergencia)  insereFila(emergencia,codVoo,horaEsperada,numeroPassageiro);
                else {
                    insereFila(normal,codVoo,horaEsperada,numeroPassageiro);
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
                    if(horarioSistema.hora!=aux->horario.hora)   aux->checkHora = 0;
                    else {
                        if(horarioSistema.minuto+15 > aux->horario.minuto)   aux->checkHora = 0;
                        else {
                            aux->checkHora = 1;
                        }
                    }
                    insereFila(pouso, aux->codigo, aux->horario, aux->numPassageiros);
                    horarioSistema = passTime(horarioSistema, 10);
                } else {
                    printf("Não há voos previstos");
                }

                break;
            case 3:
                printf("\t \t LISTA DE VOOS DE EMERGÊNCIA \t \t \n");
                if(!vaziaFila(emergencia))
                {
                    imprimeFila(emergencia);
                }
                else
                {
                    printf("\n lista vazia :( \n\n\n");
                }
                printf("\t \t LISTA DE VOOS \t \t \n");
                if(!vaziaFila(normal))
                {
                    imprimeFila(normal);
                }
                else
                {
                    printf("\n lista vazia :( \n\n");
                }
                break;
            case 4:
                ProximoVooPrint(emergencia,normal);
                break;
            case 5:
                imprimeFilaComCheckHora(pouso);
                break;
            case 6:
                //int minutos; talvez aqui seja melhor para a variavel só ficar nessa instancia, e nao ocupar espaço de memoria desnecessario  
                printf("\nInsira o tempo a avançar (em minutos): ");
                scanf("%d", &minutos);
                horarioSistema = passTime(horarioSistema,minutos);
                break;
            case 8:
                printf("FILA NORMAL!!!!!!!!!!!!!!1!11!\n");
                imprimeFilaComCheckHora(normal);
                printf("FILA EMERGENCIA!!!!!!!!!!!!!!1!11!\n");
                imprimeFilaComCheckHora(emergencia);
                printf("FILA POUSADOS!!!!!!!!!!!!!!1!11!\n");
                imprimeFilaComCheckHora(pouso);
                break;
            default:
                printf("\n\n\t Digite uma opção válida\n\n");
                break;
        }
    }
    return 0;
}