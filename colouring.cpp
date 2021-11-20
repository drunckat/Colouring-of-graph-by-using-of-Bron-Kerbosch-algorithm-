#include "graph.h"

#define MIT maxIndependentSet
//These variables are needed in both function
int maxStage;          //it counts the minimal number of colours
int* colours;           //this array contain matching between vertexes and colours
int dimension;          //this variable contain a dimension of initial graph

void downMoving(myForm, int*&, int);

void colouring(myForm graph)
{
	colours = new int[graph.vertexes]; //dimension of colours must be the same to number of vertexes
	int* colorInRec = new int[graph.vertexes];  //in first step dimension of colours of current graph also has the same dimension
	maxStage = graph.vertexes + 3;               //maxStage must be changed during execution of program
	dimension = graph.vertexes;                  //dimension will be static
	for (int i = 0; i < graph.vertexes; i++)     
	{
		colours[i] = i;                          //initially all vertexes of initial graph have different colours
		colorInRec[i] = 0;                       //of current the same 
	}
	
	downMoving(graph, colorInRec, 0);             //call recursive func to determine colours
	cout << "\nCOLOURS:\n";
	int counter = 0;
	for (int i = 0; i < dimension; i++)
	{
		counter = counter > colours[i] ? counter : colours[i];     //counts number of colours
	}


	for (int i = 0; i <= counter; i++)                         //outpur vertexes by colours
	{
		for (int j = 0; j < dimension; j++)
		{
			if (colours[j] == i)
			{
				cout << j << " ";              //output of index of vertexes
			}

		}
		cout << " : " << i << endl;           //output of colour
	}

	delete[]colorInRec;
	delete[]colours;
}

void downMoving(myForm graph, int*& colorInRec, int stage)
{

	myForm temporaryGraph;
	vector< vector<int> > MIT = graph.BronKerboschForColouring();  //call Bron-Kerbosch to determine MISes
	for (int i = 0; i < MIT.size(); i++)
	{
		temporaryGraph = splitGraph(graph, MIT[i]);           //splitting initial graph by MISes, deleting their vertexes and neig.
		for (int j = 1; j <= MIT[i][0]; j++)
		{
			colorInRec[MIT[i][j]] = stage;                         //each vertex in MIS has a colour of this stage
		}
		if ((stage < (maxStage - 1)) and !temporaryGraph.edges)     //if there is new MIS and stage of this branch is lesser, 
			                                                        //than stage of ex minimal combination
		{
			for (int j = 0; j < temporaryGraph.nodes.size(); j++)
			{
				colorInRec[temporaryGraph.nodes[j].index] = stage + 1;       //we are colouring the left vertexes
			}
			for (int l = 0; l < dimension; l++)
			{
				colours[l] = colorInRec[l];                               //and transfer colours of this combination to the main set of colours
			}
			maxStage = stage;
		}
		else if (stage < (maxStage - 1))
		{
			downMoving(temporaryGraph, colorInRec, stage + 1);           //in the other way we're going deeper if there is sense
		}
	}
}