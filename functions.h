#ifndef FUNCTIONS_H
#define FUNCTIONS_H


typedef struct node * link;
struct node {
  link* filhos; //vetor de filhos do node
  int* itens; //vetor de itens do node
  link pai; //pai do node
  int total; // total de itens no node
  int id;     // id do node
};

typedef struct tree {
  link head; //raiz da arvore
  link z;    //node externo
  int ordem; //ordem da arvore
} * Tree;

Tree createTree(int);

link novoNo(Tree, int, link);

link insert (Tree, int);
link insertR(Tree, link, int);

link split(Tree, link);

link merge(Tree, link);

link irmaoDireita(Tree, link);
link irmaoEsquerda(Tree, link);

link antecessor(Tree, link, int);

void emptyNodeCheck(Tree, link, int);

void remocao(Tree, int);
link remocaoR(Tree, link, int);

void fullNodeCheck(Tree, link);

link insereVet(link, int);
link removeVet(link, int);

void imprime(Tree, char*);
 
#endif 


