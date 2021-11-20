#include "graph.h"

myForm splitGraph(myForm source, vector<int> array)
{
	for (int i = 1; i <= array[0]; i++)
	{
		for (int j = 0; j < source.vertexes; j++)
		{
			if (array[i] == source.nodes[j].index)
			{
				source.vertexes--;
				source.nodes.erase(source.nodes.begin() + j);
				j--;
				continue;
			}
			for (int k = 0; k < source.nodes[j].n_counter; k++)
			{
				if (array[i] == source.nodes[j].neighbors[k])
				{
					source.nodes[j].neighbors.erase(source.nodes[j].neighbors.begin() + k);
					k--;
					source.nodes[j].n_counter--;
					source.edges--;
				}
			}
		}
	}
	return source;
}
