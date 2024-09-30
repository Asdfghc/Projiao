#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED

/* FUNCOES AUXILIARES

int randomInteger(int SupLimit, int InfLimit)   RETORNA UM NUMERO ALEATORIO EM CERTO INTERVALO DEFINIDO

Horario passTime(Horario Time, int forward)     RETORNA A PASSAGEM DE X MINUTOS

unsigned int string_to_seed(const char *str)    RETORNA UMA STRING COMO A SOMATORIA DO CODIGO ASC DE CADA CARACTER

bool digitCheck(char key[])     RETORNA true SE NA STRING SÓ CONTER NUMEROS E false SE TIVER ALGO ALEM

*/
int randomInteger(int SupLimit, int InfLimit) {
    return rand() % (SupLimit + 1 - InfLimit) + InfLimit;
}

void randomAlphaNumeric(char* code) {
    char alphabet[62] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    for(int i = 0; i < 4; i++) {
        int randomIndex = rand() % (sizeof(alphabet) - 1);
        code[i] = alphabet[randomIndex];
    }
    code[5] = '\0';
}

Horario passTime(Horario Time, int forward){
    Time.minuto += forward;
    Time.hora += Time.minuto / 60;
    Time.minuto %= 60;
    Time.hora %= 24;
    return Time;
}

bool comparaHorario(Horario horario1, Horario horario2) {
    if (horario1.hora < horario2.hora) return true;
    if (horario1.hora == 23 && horario2.hora == 0) return true;
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

bool digitCheck(char key[]){
    for (unsigned int i = 0; i < strlen(key); i++)
    {
        if(isdigit(key[i])==0)  return false;
    }
    return true;
}

void ProximoVooPrint (Fila*emergencia,Fila*normal)
{
    No *a;
    if(!vaziaFila(emergencia))
        {
            a = emergencia -> ini;
            printf("\nAtenção o Proximo voo é de emergencia!! \n");
            printf("\nO codigo do Próximo Voo de emergencia é: %s\n", a -> codigo);
            printf("\nO Numero de passageiros do Próximo de emergencia Voo é: %d\n", a ->numPassageiros);
        }
        else if(!vaziaFila(normal))
        {
            a = normal -> ini;
            printf("\n Informações do Proximo voo normal \n");
            printf("\nO codigo do Próximo Voo é: %s\n", a -> codigo);
            printf("\nO Numero de passageiros do Próximo Voo é: %d\n", a ->numPassageiros);
        }
        else {
            printf("Não há voos previstos");
        }
}

No *ProximoVoo (Fila*emergencia, Fila*normal)
{
    No *a;
    if(!vaziaFila(emergencia))
    {
        a = emergencia -> ini;
    }
    else
    {
        a = normal -> ini;
    }
    return a;
}

bool outOfRange(int number, int max, int min) {
    if(max<number || min>number)    return true;
    return false;
}

#endif //UTILITIES_H_INCLUDED