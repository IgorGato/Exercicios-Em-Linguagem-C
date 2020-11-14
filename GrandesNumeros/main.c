#include <stdio.h>
#include <stdlib.h>
#include "GrandesNumeros.h"

int main(){
   
    conta_t **inputs;
    int num_inputs;

    scanf("%d", &num_inputs);
    fgetc(stdin);
    inputs = ler_guardar_input(num_inputs);
    escolher_operacao(inputs, num_inputs);


    return 0;
}