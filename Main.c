#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "FILA.h"


int main() {

    setlocale(LC_ALL, "Portuguese");

    int opcao;
    while (1) {
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

                break;
            case 3:

                break;
            case 4:

                break;
            case 5:

                break;
            case 6:

                break;
            case 7:
                return 0;
                break;
        }
    }

}