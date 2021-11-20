#include <iostream>
#include "graph.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv)
{
	myForm graph;
	graph.introduce();
	graph.showForm();
	colouring(graph);
	system("Pause>NULL");
	return 0;
}
