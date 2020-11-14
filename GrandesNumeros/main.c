#include <stdio.h>
#include <stdlib.h>
#include "GrandesNumeros.h"

int main(){
   
    conta_t **inputs;
    int num_inputs;
    // insira o numero de operacoes que deseja realizar
    // depois insira na ordem: a operacao, e ambos os numeros
    scanf("%d", &num_inputs);
    
    inputs = ler_guardar_input(num_inputs);
    escolher_operacao(inputs, num_inputs);

    return 0;
}