#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED

/* FUNCOES AUXILIARES

int randomInteger(int SupLimit, int InfLimit)   RETORNA UM NUMERO ALEATORIO EM CERTO INTERVALO DEFINIDO

void randomAlphaNumeric(char* code)     RETORNA UMA STRING ALEATORIA DE 4 CARACTERES

Horario passTime(Horario Time, int forward)     RETORNA A PASSAGEM DE X MINUTOS

bool comparaHorario(Horario horario1, Horario horario2)     COMPARA DOIS HORARIOS, RETORNA TRUE SE O HORARIO2 FOR MAIOR

unsigned int string_to_seed(const char *str)    RETORNA UMA STRING COMO A SOMATORIA DO CODIGO ASC DE CADA CARACTER

bool digitCheck(char key[])     RETORNA true SE NA STRING SÓ CONTER NUMEROS E false SE TIVER ALGO ALEM

void ProximoVooPrint (Fila*emergencia,Fila*normal)     IMPRIME O PROXIMO VOO

bool outOfRange(int number, int max, int min)     RETORNA true SE O NUMERO ESTIVER FORA DO INTERVALO E false SE ESTIVER DENTRO

*/
int randomInteger(int SupLimit, int InfLimit) {
    return rand() % (SupLimit + 1 - InfLimit) + InfLimit;
}

void randomAlphaNumeric(char* code) {
    char alphabet[62] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";       //string contendo todos caracteres para o codigo
    for(int i = 0; i < 4; i++) {
        int randomIndex = rand() % (sizeof(alphabet) - 1);      //gera uma posição aleatoria da string
        code[i] = alphabet[randomIndex];        //insere o valor aleatorio escolhido
    }
    code[4] = '\0';     //adiciona a finalização da string
}



Horario passTime(Horario Time, int forward) {
    Time.minuto += forward;
    // Adjust hours based on overflow or underflow in minutes
    Time.hora += floor((double) Time.minuto / 60);
    Time.minuto = (60 + Time.minuto % 60) % 60; // Wrap minutes correctly

    Time.dia += Time.hora / 24;
    // Wrap hours correctly considering underflow when moving backwards
    Time.hora = (24 + Time.hora % 24) % 24;

    return Time;
}

bool comparaHorario(Horario horario1, Horario horario2) {

    if (horario1.dia < horario2.dia) return true;

    if (horario1.dia == horario2.dia && horario1.hora < horario2.hora) return true;

    if (horario1.hora == horario2.hora && horario1.minuto < horario2.minuto) return true;

    return false;
}

unsigned int string_to_seed(const char *str) {
    unsigned int seed = 0;
    for(int i = 0; str[i]!= '\0';i++)
    {
        seed += (unsigned int)str[i];
    }
    return seed;
}

bool digitCheck(char key[]) {
    for (unsigned int i = 0; i < strlen(key); i++)
    {
        if(!isdigit(key[i]) && key[i]!='\n')  return false;
    }
    return true;
}

void ProximoVooPrint (Fila*emergencia,Fila*normal) {
    No *a;
    printf("\n\n");
    if(!vaziaFila(emergencia)) 
    {
        a = emergencia -> ini;
        printf("\t\tAtenção, o próximo voo é de emergência!! \n");
        printf("\t\tO código do próximo voo de emergência é: %s\n", a -> codigo);
        printf("\t\tO Número de passageiros do próximo voo de emergencia é: %d\n", a ->numPassageiros);
    }
    else if(!vaziaFila(normal))
    {
        a = normal -> ini;
        printf("\t\tInformações do próximo voo \n");
        printf("\t\tO código do próximo voo é: %s\n", a -> codigo);
        printf("\t\tO número de passageiros do próximo voo é: %d\n", a ->numPassageiros);
    }
    else {
        printf("\t\tNão há voos previstos\n");
    }
}

bool outOfRange(int number, int max, int min) {
    if(max<number || min>number)    return true;
    return false;
}

#endif //UTILITIES_H_INCLUDED