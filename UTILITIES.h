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

Horario passTime(Horario Time, int forward) {
    Time.minuto += forward;
    Time.hora += Time.minuto / 60;
    Time.minuto %= 60;
    Time.hora %= 24;
    return Time;
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
    else
    {
        a = emergencia -> ini;
        printf("\n Informações do Proximo voo normal \n");
        printf("\nO codigo do Próximo Voo é: %s\n", a -> codigo);
        printf("\nO Numero de passageiros do Próximo Voo é: %d\n", a ->numPassageiros);
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
}

#endif //UTILITIES_H_INCLUDED