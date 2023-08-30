#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

int maior(int dir, int esq) {
	int maior = 0;

	if (dir > esq || esq == dir) {
		maior = dir;
	}
	else if ( esq > dir) {
		maior = esq;
	}

	return maior;
}

int altura_avl(arvore raiz) {
	int altura_dir = 0;
	int altura_esq = 0;
	int altura = 0;

	if (raiz==NULL) {
		return 0;
	}
	else {
		altura_dir = altura_avl(raiz->sub_dir);
		altura_esq = altura_avl(raiz->sub_esq);
		altura = 1 + maior(altura_dir, altura_esq);
		return altura;
	}
}

arvore atualizaFator(arvore raiz) {

	if (raiz == NULL) {
		return 0;
	}
	else {
		raiz->fatorBalanceamento = altura_avl(raiz->sub_dir) - altura_avl(raiz->sub_esq);
		atualizaFator(raiz->sub_dir);
		atualizaFator(raiz->sub_esq);
		return raiz;
	}

}


arvore rotacaoSimplesDireitaAvl(arvore raiz) {
	arvore auxU, auxT2;
	auxU = raiz->sub_esq;
	auxT2 = auxU->sub_dir;

	auxU->sub_dir = raiz;
	raiz->sub_esq = auxT2;

	auxU = atualizaFator(auxU);
	raiz = atualizaFator(raiz);


	return auxU;
}

arvore rotacaoSimplesEsquerdaAvl(arvore raiz) {
	arvore auxU, auxT2;
	auxU = raiz->sub_dir;
	auxT2 = auxU->sub_esq;

	auxU->sub_esq = raiz;
	raiz->sub_dir = auxT2;

	auxU = atualizaFator(auxU);
	raiz = atualizaFator(raiz);

	return auxU;

}

arvore rotacaoDuplaDireitaAvl(arvore raiz) {
	raiz->sub_esq = rotacaoSimplesEsquerdaAvl(raiz->sub_esq);
	raiz = rotacaoSimplesDireitaAvl(raiz);
	return raiz;
}

arvore rotacaoDuplaEsquerdaAvl(arvore raiz) {
	raiz->sub_dir = rotacaoSimplesDireitaAvl(raiz->sub_dir);
	raiz = rotacaoSimplesEsquerdaAvl(raiz);
	return raiz;
}

arvore rotacionar(arvore raiz) {
	if (raiz->fatorBalanceamento == -2 && raiz->sub_esq->fatorBalanceamento == -1) {
		return rotacaoSimplesDireitaAvl(raiz);
	}
	else if (raiz->fatorBalanceamento == 2 && raiz->sub_dir->fatorBalanceamento == 1) {
		return rotacaoSimplesEsquerdaAvl(raiz);
	}
	else if (raiz->fatorBalanceamento == -2 && raiz->sub_esq->fatorBalanceamento == 1) {
		return rotacaoDuplaDireitaAvl(raiz);
	}
	else if (raiz->fatorBalanceamento == 2 && raiz->sub_dir->fatorBalanceamento == -1) {
		return rotacaoDuplaEsquerdaAvl(raiz);
	}
	return raiz;
}

arvore inserir_avl(int valor, arvore raiz) {

	if (raiz == NULL) {
		arvore novo = (arvore)malloc(sizeof(struct no));
		novo->valor = valor;
		novo->sub_esq = NULL;
		novo->sub_dir = NULL;
		novo->fatorBalanceamento = 0;
		return novo;
	}
	else {
		if (valor > raiz->valor) {
			raiz->sub_dir = inserir_avl(valor, raiz->sub_dir);
			raiz = atualizaFator(raiz);

		}
		else {
			raiz->sub_esq = inserir_avl(valor, raiz->sub_esq);
			raiz = atualizaFator(raiz);

		}
		raiz = rotacionar(raiz);

		return raiz;
	}
}
int maior_avl(arvore raiz) {
	int maiorAvl = raiz->valor;
	while (raiz->sub_dir != NULL) {
		if (raiz->sub_dir->valor > maiorAvl) {
			maiorAvl = raiz->sub_dir->valor;
		}
		raiz = raiz->sub_dir;
	}
	return maiorAvl;

}
arvore remover_avl(int valor, arvore raiz) {

	if (raiz == NULL) {
		return raiz;
	}

	if (raiz->valor == valor) {

		if (raiz->sub_esq == NULL && raiz->sub_dir == NULL) {
			free(raiz);
			return NULL;
		}

		if (raiz->sub_esq != NULL && raiz->sub_dir == NULL) {
			arvore aux = raiz->sub_esq;
			free(raiz);

			aux = atualizaFator(aux);
			aux = rotacionar(aux);

			return aux;
		}
		if (raiz->sub_esq == NULL && raiz->sub_dir != NULL) {
			arvore aux = raiz->sub_dir;
			free(raiz);

			aux = atualizaFator(aux);
			aux = rotacionar(aux);

			return aux;
		}

		int maiorAvl = maior_avl(raiz->sub_esq);
		raiz->valor = maiorAvl;
		raiz->sub_esq = remover_avl(maiorAvl, raiz->sub_esq);

		raiz = atualizaFator(raiz);
		raiz = rotacionar(raiz);

		return raiz;

	}
	if (valor > raiz->valor) {
		raiz->sub_dir = remover_avl(valor, raiz->sub_dir);
	}
	else {
		raiz->sub_esq = remover_avl(valor, raiz->sub_esq);
	}

	return raiz;

}
void in_orderAvl(arvore raiz) {
	if (raiz != NULL) {
		in_orderAvl(raiz->sub_esq);
		printf("[%d] fb:%d\n", raiz->valor, raiz->fatorBalanceamento);
		in_orderAvl(raiz->sub_dir);
	}
}

void pre_orderAvl(arvore raiz) {
	if (raiz != NULL) {
		printf("[%d] fb:%d\n", raiz->valor, raiz->fatorBalanceamento);
		pre_orderAvl(raiz->sub_esq);
		pre_orderAvl(raiz->sub_dir);
	}
}




