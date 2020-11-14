Entrada:
Insira os valores de N, x, y e T da entrada padrão.
- T será utilizado para inicializar uma sementen aleatoria.
- Uma matriz N x N será criada dinamicamente com números aleatórios entre 0 e 255.
- A partir do ponto (x,y), chamado de p, o programa fará uma busca explorando os 4 vizinhos da posição atual (cima, direita, baixo, esquerda), e, caso o pixel vizinho v seja diferente de p dentro de um intervalo m, modifique o valor de v inserindo p em seu lugar.
 - O valor de m será calculado: Se |p - v| <= T, v receberá o valor de p.

Saida:
 - Matriz inicial e matriz resultante;
 - Cria 2 arquivos no formato .pgm, os quais representarão respectivamente a imagem inicial (Aleatória) e a imagem final (Modificada Recursivamente). 

Os arquivos .in podem ser utilizados como exemplo de input, enquando os arquivos .out são exemplos de output