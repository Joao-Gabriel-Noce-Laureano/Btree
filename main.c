#include <stdio.h>
#include "functions.h"

int main () {
	Tree t = createTree(2);
	insert(t,30);
	insert(t,70);
	insert(t,50);
	insert(t,40);
	insert(t,60);
	insert(t,45);
	insert(t,46);
	insert(t,35);
	insert(t,52);
	insert(t,80);
	insert(t,48);
	insert(t,51);
	insert(t,36);
	insert(t,44);
	insert(t,43);
	insert(t,20);
	insert(t,10);
	insert(t,42);
	remocao(t,45);
	remocao(t, 44);
	remocao(t,60);
	remocao(t,35);
	imprime(t, "ArvoreB");
	

	return 0;
}
