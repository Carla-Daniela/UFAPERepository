#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	arvore avlTree, aux2;
	int opcao, valor, aux, temp, temp2;
	avlTree = NULL;
	aux2 = NULL;
	temp = 0;
	temp2 = 0;
	while (1) {
		scanf("%d", &opcao);
		switch (opcao) {
		case 1:
			scanf("%d", &valor);
			avlTree = inserir_avl(valor, avlTree);
			printf("\n");
			break;
		case 2:
			pre_orderAvl(avlTree);
			break;
		case 3:
			scanf("%d", &valor);
			avlTree = remover_avl(valor, avlTree);
			break;
		case 99:
			exit(0);

		}



	}

}