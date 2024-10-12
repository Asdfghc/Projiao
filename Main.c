#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include "FILA.h"
#include "UTILITIES.h"


int main() {

    char seedInput[10];    //String que vai registrar a seed

    system("cls");
    printf("\n\n\tDigite a seed desejada para geração dos numeros: ");    //Leitura da seed
    fgets(seedInput, sizeof(seedInput), stdin);

    unsigned int seed = string_to_seed(seedInput);  //Transforma a string em um int
    srand(seed);   // Inicializa a seed

    Fila *emergencia = NULL;        //Criação das filas
    emergencia = criaFila();

    Fila *normal = NULL;
    normal = criaFila();

    Fila *pouso = NULL;
    pouso = criaFila();

    Horario horarioSistema;                         //Criação do horário local
    horarioSistema.hora = randomInteger(23,1);      //Gera um horário local aleatório e inicializa no dia 0
    horarioSistema.minuto = randomInteger(59,1);
    horarioSistema.dia = 0;
    
    char opcao[3];
    int opcaoNum = 0;

    Horario horaEsperada;       //variaveis auxiliares para os inputs
    char codVoo[5];
    int numPassageiros;
    int optEmergencia;
    int minutos;

    char inputMinutos[5];

    while (opcaoNum != 7) {
        do{
            system("cls");
            printf("\n\n\tHorario atual: %.2d:%.2d\n", horarioSistema.hora, horarioSistema.minuto);         //print do menu
            printf("\n\t\t1. Inserir uma aeronave na fila de espera para o pouso\n");
            printf("\t\t2. Autorizar uma aeronave a pousar\n");
            printf("\t\t3. Imprimir um Relatorio com as aeronaves na fila para pouso\n");
            printf("\t\t4. Imprimir a proxima aeronave que sera autorizada a pousar\n");
            printf("\t\t5. Imprimir todos os voos que ja pousaram\n");
            printf("\t\t6. Simular o processamento de pouso\n");
            printf("\t\t7. Finalizar o sistema\n");
            printf("\n\tOpcao: ");
            fflush(stdin);
            fgets(opcao, sizeof(opcao), stdin);         //limpa o cache e coleta 3 digitos e apos transforma em int
            opcaoNum = atoi(opcao);                     
            if(!digitCheck(opcao) || outOfRange(opcaoNum,7,0))    {     //verifica se todos os caracteres sao numeros e se estao no intervalo correto
                system("cls");
                printf("\n\n\n\tErro! \t Digite uma opcao!\n\n");
                system("pause");
            }
        }while(!digitCheck(opcao) || outOfRange(opcaoNum,7,0));


        system("cls");
        switch (opcaoNum) {
            case 1:
                randomAlphaNumeric(codVoo);             //gera um codigo alfanumerico aleatorio
                printf("\n\n\tVoo %s\n\n",codVoo);
                horaEsperada = passTime(horarioSistema, randomInteger(100, -100));      //geração de um horario aleatorio, em uma janela de 100 minutos da hora atual
                printf("\t\tHorario de chegada esperado: %.2d:%.2d\n", horaEsperada.hora, horaEsperada.minuto);
                numPassageiros = randomInteger(200, 50);            //gera o numero de passageiros aleatorio, entre 200 e 50
                printf("\t\tNumero de passageiros: %d\n", numPassageiros);
                optEmergencia = randomInteger(10, 0)<4 ? 1 : 0;
                printf("\t\tVoo de emergencia? %s\n", optEmergencia ? "Sim" : "Nao");       //gera a opção de emergencia aleatoriamente, em uma proporção 6:4

                if(optEmergencia)  insereFila(emergencia,codVoo,horaEsperada,numPassageiros, -2);       //ja insere nas devidas filas
                else {
                    insereFila(normal,codVoo,horaEsperada,numPassageiros, -2);
                }
                system("pause");
                break;

            case 2:
                if (!vaziaFila(emergencia)) {           //Se fila de emergencia nao estiver vazia ja retira, se nao vai na normal
                    No* aux = retiraFila(emergencia);
                    aux->checkHora = -1;
                    insereFila(pouso, aux->codigo, aux->horario, aux->numPassageiros, aux->checkHora);
                    horarioSistema = passTime(horarioSistema, 10);
                } else if (!vaziaFila(normal)) {
                    No* aux = retiraFila(normal);       
                    if(comparaHorario(passTime(horarioSistema, 15), aux->horario)) aux->checkHora = 1;
                    else {
                        aux->checkHora = 0;
                    }
                    insereFila(pouso, aux->codigo, aux->horario, aux->numPassageiros, aux->checkHora);
                    horarioSistema = passTime(horarioSistema, 10);
                } else {
                    printf("\n\tNao ha voos previstos");        //se as duas estiverem vazias, aparece a mensagem
                }
                break;

            case 3:
                printf("\t \t LISTA DE VOOS DE EMERGENCIA \n");     //lista os voos de emergencia e as normais, se nao tiver apenas apresenta a mensagem que esta vazia
                if(!vaziaFila(emergencia))
                {
                    imprimeFila(emergencia);
                }
                else
                {
                    printf("\n\t\tNenhum voo de emergencia em espera\n\n\n");
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
                ProximoVooPrint(emergencia,normal);     //printa o proximo voo a pousar
                system("pause");
                break;
            case 5:
                imprimeFilaComCheckHora(pouso);         //imprime os que ja pousaram
                system("pause");
                break;
            case 6:
                do {
                    printf("\n\n\tInsira o tempo a avancar (em minutos): ");        //coleta do tempo e verifica se sao digitos, e se ta no intervalo de 1 a 999
                    fflush(stdin);
                    fgets(inputMinutos, sizeof(inputMinutos), stdin);
                    minutos = atoi(inputMinutos);
                    if (outOfRange(minutos,999,1) || !digitCheck(inputMinutos))     printf("\n\n\tO numero de minuto tem que ser no minimo 1 e no maximo 999!\n\n");
                } while(outOfRange(minutos,999,1) || !digitCheck(inputMinutos));

                Horario horarioFinalSimulacao = passTime(horarioSistema, minutos);       //cria duas variaveis auxiliares, um do horario final e outro da hora da simulacao
                Horario horarioSimulado = horarioSistema;

                Fila* filaSimulacao = criaFila();           //cria uma fila auxiliar para a simulacao e um No para percorrer as duas filas
                No* auxInsercaoSimulacao = emergencia->ini;
                while(auxInsercaoSimulacao != NULL && comparaHorario(horarioSimulado, horarioFinalSimulacao)) {     //percorre pela fila de emergencia e vai inserindo na filaSimulacao, enquanto estiver no horario
                    auxInsercaoSimulacao->checkHora = -1;
                    insereFila(filaSimulacao, auxInsercaoSimulacao->codigo, auxInsercaoSimulacao->horario, auxInsercaoSimulacao->numPassageiros, auxInsercaoSimulacao->checkHora);
                    horarioSimulado = passTime (horarioSimulado, 10);
                    auxInsercaoSimulacao = auxInsercaoSimulacao->prox;
                }
                auxInsercaoSimulacao = normal->ini;
                while(auxInsercaoSimulacao != NULL && comparaHorario(horarioSimulado, horarioFinalSimulacao)) {             //faz a mesma coisa anterior, so que na fila normal
                    if(comparaHorario(passTime(auxInsercaoSimulacao->horario, 15), horarioSimulado)) auxInsercaoSimulacao->checkHora = 1;
                    else {
                        auxInsercaoSimulacao->checkHora = 0;
                    }
                    insereFila(filaSimulacao, auxInsercaoSimulacao->codigo, auxInsercaoSimulacao->horario, auxInsercaoSimulacao->numPassageiros, auxInsercaoSimulacao->checkHora);
                    horarioSimulado = passTime(horarioSimulado, 10);
                    auxInsercaoSimulacao = auxInsercaoSimulacao->prox;
                }
                imprimeFilaComCheckHora(filaSimulacao);       //imprime a fila da Simulacao e libera logo em seguida
                filaSimulacao = liberaFila(filaSimulacao);
                free(filaSimulacao);
                system("pause");
                break;
            case 7:
                printf("\n\n\tSistema encerrado\n\n");      //encerra o programa, saindo do while
                system("pause");
                system("cls");
                break;
            default:
                printf("\n\n\t Digite uma opcao valida\n\n");       //mensagem de erro
                system("pause");
                break;
        }
    }
    return 0;       //finaliza o programa
}