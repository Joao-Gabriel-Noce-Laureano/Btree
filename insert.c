#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

void fullNodeCheck(Tree t, link n)
{
	if(n->total == t->ordem*2+1) fullNodeCheck(t, split(t,n));
}

link insertR (Tree t, link h, int item) {
	for(int i = 0; i <= h->total; i++)
	{
		if(i == 0)
		{
			if(h->itens[0] > item)
			{
				if(h->filhos[i] == t->z)
				{
					h = insereVet(h, item);
					return h;
				}
				else return insertR(t, h->filhos[i], item);	
			}
		}
		else if(i == h->total)
		{
			
			if(h->itens[h->total - 1] < item)
			{
				if(h->filhos[i] == t->z)
				{
					h = insereVet(h, item);
					return h;
				}
				else return insertR(t, h->filhos[i], item);	
			}
		}
		else if(h->itens[i-1] < item && h->itens[i] > item)
		{
			if(h->filhos[i] == t->z)
			{
				h = insereVet(h, item);
				return h;
			}
			else return insertR(t, h->filhos[i], item);
		}
	}
}

link insert (Tree t, int item){
	if(t->head == t->z) {
		return (t->head =novoNo(t, item, NULL));
	}
	link n = insertR(t, t->head, item);
	fullNodeCheck(t,n);
	
	return n;
}

link split(Tree t, link n)
{
	if(n == t->head)
	{
		t->head = novoNo(t, n->itens[t->ordem], NULL);
		
		link n2 = novoNo(t, 0, t->head);
		n2->filhos[t->ordem] = n->filhos[t->ordem*2+1];
		n->filhos[t->ordem*2+1]->pai = n2;
		for(int i = t->ordem*2; i >= t->ordem+1;i--)
		{
			
			n2->itens[i - t->ordem - 1] = n->itens[i];
			n2->filhos[i - t->ordem - 1] = n->filhos[i];
			n->filhos[i]->pai = n2;
			n = removeVet(n, n->itens[i]);
		}
		n2->total = t->ordem;
		
		n = removeVet(n, n->itens[t->ordem]);

		n->pai = t->head;
		t->head->filhos[0] = n;
		t->head->filhos[1] = n2;
		return t->head;
	}
	else
	{
		int pos = 0;
		n->pai = insereVet(n->pai,n->itens[t->ordem]);
		for(int i = 0; i < n->pai->total;i++)
		{
			if(n->pai->itens[i] == n->itens[t->ordem])
			{
				pos = i;
				break;
			} 
		}
		
		
		link n2 = novoNo(t, 0, t->head);
		n2->pai = n->pai;
		n2->filhos[t->ordem] = n->filhos[t->ordem*2+1];
		n->filhos[t->ordem*2+1]->pai = n2;
		for(int i = t->ordem*2; i >= t->ordem+1;i--)
		{
			
			n2->itens[i - t->ordem - 1] = n->itens[i];
			n2->filhos[i - t->ordem - 1] = n->filhos[i];
			n->filhos[i]->pai = n2;
			n = removeVet(n, n->itens[i]);
		}
		n2->total = t->ordem;
		n = removeVet(n, n->itens[t->ordem]);
		
		n->pai->filhos[pos] = n;
		n->pai->filhos[pos+1] = n2;
		return n->pai;
	}
}

