#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

void emptyNodeCheck(Tree t, link n, int item)
{
	
	if(n->total < t->ordem)
	{
		link irmEsq = irmaoEsquerda(t, n);
		if(irmEsq != NULL && irmEsq->total > t->ordem)
		{
			int i;
			for(i=0; i <= n->pai->total; i++) if(n->pai->filhos[i] == n) break;
			n = insereVet(n, n->pai->itens[i-1]);
			n->pai->itens[i-1] = irmEsq->itens[irmEsq->total-1];
			n->filhos[1] = n->filhos[0];
			n->filhos[0] = irmEsq->filhos[irmEsq->total];
			removeVet(irmEsq,irmEsq->itens[irmEsq->total-1]);
			return;
		}
		link irmDir = irmaoDireita(t, n);
		if(irmDir != NULL && irmDir->total > t->ordem)
		{
			int i;
			for(i=0; i <= n->pai->total; i++) if(n->pai->filhos[i] == n) break;
			n = insereVet(n, n->pai->itens[i]);
			n->pai->itens[i] = irmDir->itens[0];
			n->filhos[n->total] = irmDir->filhos[0];
			removeVet(irmDir,irmDir->itens[0]);
			return;
		}
		n = merge(t,n);
		if(n->pai == t->head)
		{
			if(n->pai->total == 0)
			{
				t->head = n;
				free(n->pai->itens);
			    free(n->pai->filhos);
			    free(n->pai);
			    n->pai = NULL;
			} 
		}
		else if(n->pai->total < t->ordem) emptyNodeCheck(t, n->pai, 0);
		return;
	}
	else if(n->filhos[0] == t->z)
	{
		
		if(n->total > t->ordem) removeVet(n, item);
		else
		{
			link irmEsq = irmaoEsquerda( t,  n);
			if(irmEsq != NULL && irmEsq->total > t->ordem)
			{
				int i;
				for(i=0; i <= n->pai->total; i++) if(n->pai->filhos[i] == n) break;
				n = insereVet(n, n->pai->itens[i-1]);
				n->pai->itens[i-1] = irmEsq->itens[irmEsq->total-1];
				n->filhos[1] = n->filhos[0];
				n->filhos[0] = irmEsq->filhos[irmEsq->total];
				removeVet(irmEsq,irmEsq->itens[irmEsq->total-1]);
				removeVet(n,item);
				return;
			}
			link irmDir = irmaoDireita(t,  n);
			if(irmDir != NULL && irmDir->total > t->ordem)
			{
				int i;
				for(i=0; i <= n->pai->total; i++) if(n->pai->filhos[i] == n) break;
				n = insereVet(n, n->pai->itens[i]);
				n->pai->itens[i] = irmDir->itens[0];
				n->filhos[n->total] = irmDir->filhos[0];
				removeVet(irmDir,irmDir->itens[0]);
				removeVet(n,item);
				return;
			}
			
			n = merge(t,n);
			
			removeVet(n,item);
			if(n->pai == t->head)
			{
				if(n->pai->total == 0)
				{
					t->head = n;
					free(n->pai->itens);
				    free(n->pai->filhos);
				    free(n->pai);
				    n->pai = NULL;
				} 
			}
			else if(n->pai->total < t->ordem) emptyNodeCheck(t, n->pai, 0);
		}
		return;
	} 
	else
	{
		link ant = antecessor(t,n,item);
		int i;
		for(i=0; i < n->total; i++) if(n->itens[i] == item) break;
		n->itens[i] = ant->itens[ant->total-1]; 
		removeVet(ant,item);
		if(ant->total < t->ordem) emptyNodeCheck(t, ant, 0);
		return;
	}
}

link remocaoR(Tree t, link h, int item) {
	for(int i = 0; i <= h->total; i++)
	{
		if(h->itens[i] == item) return h;
		
		if(i == 0)
		{
			if(h->itens[0] > item)
			{
				return remocaoR(t, h->filhos[i], item);	
			}
		}
		else if(i == h->total)
		{
			
			if(h->itens[h->total - 1] < item)
			{
				return remocaoR(t, h->filhos[i], item);	
			}
		}
		else if(h->itens[i-1] < item && h->itens[i] > item)
		{
			return remocaoR(t, h->filhos[i], item);
		}
	}
}


void remocao(Tree t, int item) {
	if(t->head == t->z) {
		return;
	}
	link n = remocaoR(t, t->head, item);
	emptyNodeCheck(t, n, item);
	
	return;
}

link merge(Tree t, link n1) {
	int item;
	link n2;
	for (int i = 0; i <= n1->pai->total; i++)
	{
		if(n1->pai->filhos[i] == n1)
		{
			if(i == n1->pai->total)
			{
				item = n1->pai->itens[i-1];
				n2 = n1;
				n1 = n1->pai->filhos[i-1];
			}
			else
			{
				item = n1->pai->itens[i];
				n2 = n1->pai->filhos[i+1];
			}
			break;
		}
	}

    for (int i = 0; i < n2->total; i++) {
        n1 = insereVet(n1, n2->itens[i]);
    }

    n1 = insereVet(n1, item);

    int i;
    for (i = 0; i < n1->total; i++) {
        if (n1->itens[i] == item) {
            n1->filhos[i + 1] = n2->filhos[0];
            break;
        }
    }


    for (int j = 0; j < n2->total + 1; j++) {
        n1->filhos[i + j + 1] = n2->filhos[j];
        n2->filhos[j]->pai = n1;
    }

    n1->pai = removeVet(n1->pai, item);

    for (int j = 0; j <= n1->pai->total; j++) {
        if (n1->pai->filhos[j] == n2) {
            for (int k = j; k < n1->pai->total; k++) {
                n1->pai->filhos[k] = n1->pai->filhos[k + 1];
            }
            break;
        }
    }

    free(n2->itens);
    free(n2->filhos);
    free(n2);

    return n1;
}
