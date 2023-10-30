#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int id = 0;

Tree createTree(int ordem){
	Tree t = malloc (sizeof (struct tree)); 
	t->ordem = ordem; 
	int max = ordem*2; 

	t->z = malloc(sizeof(struct node));
	t->z->pai = NULL; 
	t->z->total = 0;


	t->z->itens = malloc(sizeof(int)*(max+1)); 
	
	t->z->filhos = malloc(sizeof(struct node)*(max+2)); 
	for(int i = 0; i < max + 2; i++) t->z->filhos[i] = t->z;  

	t->head = t->z; 
	return t;
}

link novoNo (Tree t, int item, link pai) {
	link n = malloc(sizeof(struct node));
	int max = t->ordem*2; 

	n->pai = pai;
	n->total = 0;

	n->itens = malloc(sizeof(int)*(max+1));

	n = insereVet(n, item);

	
	n->filhos = malloc(sizeof(struct node)*(max+2)); 
	for(int i = 0; i < max + 2; i++) n->filhos[i] = t->z; 

	n->id = id++;
	return n; 
}


link insereVet(link n, int item)
{
	if(n->total != 0)
	{
		int i = n->total - 1;
		while(i>=0)
		{
			if(n->itens[i] < item) 
			{
				n->itens[i+1] = item;
				n->total++;
				return n;
			}
			n->itens[i+1] = n->itens[i];
			n->filhos[i+2] = n->filhos[i+1];
			i--;
		}	
	}
	n->itens[0] = item;
	n->total++;
	return n;
}

link removeVet(link n, int item)
{
	int i = 0;
	while(i < n->total - 1)
	{
		if(n->itens[i] == item) break;
		i++;
	}	
	
	while(i < n->total - 1)
	{
		i++;
		n->itens[i-1] = n->itens[i];
		n->filhos[i] = n->filhos[i+1];
	}	
	n->itens[i] = 0;
	n->total--;
	return n;
}

link antecessorR(Tree t, link h)
{
	if(h->filhos[h->total] != t->z) return antecessorR(t,h->filhos[h->total]);
	else return h;
}

link antecessor(Tree t, link h, int item)
{
	int i;
	for(i=0; i < h->total; i++) if(h->itens[i] == item) break;
	
	return antecessorR(t,h->filhos[i]);
}

link irmaoDireita(Tree t, link h)
{
	int i;
	for(i=0; i <= h->pai->total; i++) if(h->pai->filhos[i] == h) break;
	
	if(i == h->pai->total) return NULL;
	else return h->pai->filhos[i+1];
}

link irmaoEsquerda(Tree t, link h)
{
	int i;
	for(i=0; i <= h->pai->total; i++) if(h->pai->filhos[i] == h) break;
	
	if(i == 0) return NULL;
	else return h->pai->filhos[i-1];
}

int c = 0;
void imprimeR(Tree a, link t){
    char s[255];
    if(t==a->z) { return;}
    for(int i = 0; i <= t->total; i++) imprimeR(a,t->filhos[i]);
	printf ("%d [ label = \"<f0>| ", t->id); 
	int j = 0;
	for(j = 0; j <= t->total - 1; j++)
	{
		printf ("<f%d> %d |",j*2+1 , t->itens[j]); 
		if(j < t->total - 1) printf("<f%d> |",j*2+2 ); 
	} 
	printf (" <f%d>\"]\n",j*2); 
	
	for(int i = 0; i <= t->total; i++)
	{
		if(t->filhos[i] != a->z){
        printf("%d:f%d->%d:f%d;\n", t->id,i*2, t->filhos[i]->id,t->filhos[i]->total);
	    } else {
	        printf("z%d [ shape=point ];\n", c);
	        printf("%d:f%d->z%d;\n", t->id,i*2 , c);
	        c++;
	    }
	}
}
void imprime(Tree a, char *s) {
    c = 0;
    printf("digraph %s {\n", s);
    printf ("node [shape=record,style=rounded, height=.1]\n");
    imprimeR(a, a->head);
    printf("}\n");
}
void imprimeFromNode(Tree a, link h, char *s) {
	c = 0;
	printf("digraph  {\n" );
	printf ("name [label = \"%s\",shape=plaintext]\n", s);
	printf ("node [shape=record,style=rounded, height=.1]\n");
	imprimeR(a, h);
	printf("}\n");
}



