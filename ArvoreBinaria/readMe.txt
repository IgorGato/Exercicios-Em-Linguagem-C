Implementação de uma arvore binaria simples e leitura das irformações da mesma.
  
Entrada:
	A primeira linha de cada caso de testes, possui um inteiro n -> número de nós da árvore. 
	As próximas n linhas, possuem as informações de cada nó da seguinte maneira:
		id esq dir
	Sendo: id  -> ID do nó, 
	       esq -> ID do nó filho esquerdo,
	       dir -> ID do nó filho direito. 
	Se não possuir nó filho esquerdo, o valor de esq será -1 (o mesmo para dir).

Saida:
 	
	no id: pai = p, altura = a, grau = g, filhos = (esq, dir), tipo = t, u = no atual
	-> p é o ID do nó pai de u. Caso u seja o nó raiz, imprima -1;
	-> a e g são respectivamente: altura e grau de saída de u;
	-> esq é o ID do nó filho esquerdo de u. Caso não exista, imprima -1;
	-> dir é o ID do nó filho direito de u. Caso não exista, imprima -1;
	-> t é o tipo de u (raiz, interno ou folha).


Os arquivos .in podem ser utilizados como exemplo de input, enquando os arquivos .out são exemplos de output
