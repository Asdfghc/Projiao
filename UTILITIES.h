#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED

/* FUNCOES AUXILIARES

int randomInteger(int SupLimit, int InfLimit)   RETORNA UM NUMERO ALEATORIO EM CERTO INTERVALO DEFINIDO

void randomAlphaNumeric(char* code)     GERA UMA STRING ALEATORIA DE 4 CARACTERESQ ALFANUMERICOS

Horario passTime(Horario Time, int forward)     RETORNA A PASSAGEM DE X MINUTOS

bool comparaHorario(Horario horario1, Horario horario2)     COMPARA DOIS HORARIOS, RETORNA TRUE SE O HORARIO 2 FOR MAIOR

unsigned int string_to_seed(const char *str)    RETORNA UMA STRING COMO A SOMATORIA DO CODIGO ASC DE CADA CARACTER

bool digitCheck(char key[])     RETORNA TRUE SE NA STRING SÓ CONTER NUMEROS

void ProximoVooPrint (Fila*emergencia,Fila*normal)     IMPRIME O PROXIMO VOO

bool outOfRange(int number, int max, int min)     RETORNA TRUE SE O NUMERO ESTIVER FORA DO INTERVALO

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
    Time.minuto += forward;     //soma os minutos
    Time.hora += floor((float) Time.minuto / 60);    //adiciona as horas necessarias
    Time.minuto = (60 + Time.minuto % 60) % 60;     // Ajusta os minutos
    Time.dia += floor((float) Time.hora / 24);     //adciona o dia se necessario

    Time.hora = (24 + Time.hora % 24) % 24;     //Ajusta as horas

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
        seed += (unsigned int)str[i];       //soma todos os valores ASC de uma string
    }
    return seed;
}

bool digitCheck(char key[]) {
    for (unsigned int i = 0; i < strlen(key); i++)
    {
        if(!isdigit(key[i]) && key[i]!='\n')  return false;     //roda por toda a string verificando se o caracter é digito
    }
    return true;
}

void ProximoVooPrint (Fila*emergencia,Fila*normal) {
    No *auxPrint;
    printf("\n\n");
    if(!vaziaFila(emergencia))      //printa o proximo voo
    {
        auxPrint = emergencia -> ini;
        printf("\n\n\tAtencao, o proximo voo eh de emergencia!! \n");
        printf("\t\tO codigo do proximo voo de emergencia: %s\n", auxPrint -> codigo);
        printf("\t\tO Numero de passageiros do proximo voo de emergencia: %d\n", auxPrint ->numPassageiros);
    }
    else if(!vaziaFila(normal))
    {
        auxPrint = normal -> ini;
        printf("\n\n\tInformacoes do proximo voo \n");
        printf("\t\tO codigo do proximo voo: %s\n", auxPrint -> codigo);
        printf("\t\tO numero de passageiros do proximo voo: %d\n", auxPrint ->numPassageiros);
    }
    else {
        printf("\n\n\t\tNão ha voos previstos\n");
    }
}

bool outOfRange(int number, int max, int min) {
    if(max<number || min>number)    return true;
    return false;
}

#endif //UTILITIES_H_INCLUDED