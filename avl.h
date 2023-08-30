#ifndef AVL_H
#define AVL_H

typedef struct no {
	int valor;
	int fatorBalanceamento;
	struct no* sub_esq, * sub_dir;
} no;

typedef no* arvore;

int maior(int dir, int esq);
int maior_avl(arvore raiz);
int altura_avl(arvore raiz);
arvore rotacionar(arvore raiz);
arvore rotacaoSimplesDireitaAvl(arvore raiz);
arvore rotacaoSimplesEsquerdaAvl(arvore raiz);
arvore rotacaoDuplaDireitaAvl(arvore raiz);
arvore rotacaoDuplaEsquerdaAvl(arvore raiz);
arvore atualizaFator(arvore raiz);
void in_orderAvl(arvore raiz);
void pre_orderAvl(arvore raiz);
arvore inserir_avl(int valor, arvore raiz);
arvore remover_avl(int valor, arvore raiz);

#endif