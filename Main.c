#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include "FILA.h"


int main() {

    setlocale(LC_ALL, "Portuguese");

    Fila *emergencia = NULL;
    emergencia = CriaFila();

    Fila *normal = NULL;
    normal = CriaFila();

    Fila *pouso = NULL;
    pouso = CriaFila();

    srand((unsigned int)time(NULL));   // Initialization, should only be called once
    Horario horarioSistema;
    horarioSistema.hora = rand() % (23 + 1 - 0) + 0;  // Returns a pseudo-random integer between 0 and RAND_MAX
    horarioSistema.minuto = rand() % (59 + 1 - 0) + 0;  // Returns a pseudo-random integer between 0 and RAND_MAX

    int minutos;

    int opcao;
    while (1) {
        printf("Horário atual: %.2d:%.2d\n", horarioSistema.hora, horarioSistema.minuto);
        printf("1. Inserir uma aeronave à fila de espera para o pouso\n");
        printf("2. Autorizar uma aeronave a pousar\n");
        printf("3. Imprimir um Relatório com as aeronaves na fila para pouso\n");
        printf("4. Imprimir a próxima aeronave que será autorizada a pousar\n");
        printf("5. Imprimir todos os voos que já pousaram\n");
        printf("6. Simular o processamento de pouso\n");
        printf("7. Finalizar o sistema\n");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:

                break;
            case 2:
                if (vaziaFila(emergencia) == 1) {
                    No* aux = RetiraFila(normal);
                    InsereFila(pouso, aux->codigo, aux->horario, aux->numPassageiros);
                }
                else {
                    No* aux = RetiraFila(emergencia);
                    InsereFila(pouso, aux->codigo, aux->horario, aux->numPassageiros);
                }
                break;
            case 3:

                break;
            case 4:

                break;
            case 5:

                break;
            case 6:
                printf("\nInsira o tempo a avançar (em minutos): ");
                scanf("%d", &minutos);
                horarioSistema.minuto += minutos;
                horarioSistema.hora += horarioSistema.minuto / 60;
                horarioSistema.minuto = horarioSistema.minuto % 60;
                horarioSistema.hora = horarioSistema.hora % 24; 
                break;
            case 7:
                return 0;
                break;
        }
    }

}