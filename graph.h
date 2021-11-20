#pragma once
#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

struct myForm
{

	struct vertex
	{
		int index; //it is index of vertex
		int n_counter; //it counts number of neighbors
		vector<int> neighbors; //it contains indexes of neughbors
		vertex()
		{
			n_counter = 0;
		}
		vertex(const vertex& copy)
		{
			index = copy.index;
			n_counter = copy.n_counter;
			neighbors = copy.neighbors;
		}
		~vertex() {};
	};

	int edges; //It counts number of edges in graph
	int vertexes; //It counts number of vertexes in graph
	vector<vertex> nodes; //It contains information about each vertex;
	myForm()
	{
		edges = 0;
		vertexes = 0;
	}
	void fillRandom(int n) //this func fills graph randomly
	{
		int t, one_more_t;
		bool key;
		vertexes = n;
		srand(time(NULL));
		vertex T;
		nodes.insert(nodes.begin(), n, T);
		for (int i = 0; i < vertexes; i++)
		{
			nodes[i].index = i;
		}
		for (int i = 0; i < n; i++)
		{
			t = abs(rand() % n - 1); //in such way we find number of edges that are incedent to vertex[i]
			for (int j = nodes[i].n_counter; j <= t; j++)
			{
				do                                               //
				{                                                //
					key = 0;                                     //
					do                                           //
						one_more_t = abs(rand() % n);            //in such way we avoid loops
					while (one_more_t == i);                     //

					for (int l = 0; l < nodes[i].n_counter; l++) //
					{                                            //
						if (one_more_t == nodes[i].neighbors[l]) //here we are checking if this neig. already exists
						{                                        //
							key = 1;                             //
							break;                               //
						}                                        //
					}                                            //
				} while (key);                                   //
				nodes[i].neighbors.push_back(one_more_t);//add a vertex in the end of neig. of this vertex
				nodes[one_more_t].neighbors.push_back(i);//add a vertex in the end of neig. of that vertex
				nodes[i].n_counter++;
				nodes[one_more_t].n_counter++;
				edges++;
			}
		}
		sortForm();
	}
	void introduce()
	{
		int t = 0, key;
		string line; //if u'r absent-minded and input letter :D

		cout << "Enter number of vertexes\n>> ";
		cin >> line;
		for (int j = 0; line[j] != '\0'; j++)        //   //
		{                                            //   //this moment will save your execution when u input "w2"
			t = t * 10 + int(line[j]) - 48;          //   //
		}
		vertexes = t;
		line.clear();

		vertex T;
		nodes.insert(nodes.begin(), vertexes, T);
		for (int i = 0; i < vertexes; i++)
		{
			nodes[i].index = i;
		}

		for (int i = 0; i < vertexes; i++)
		{
			cout << "Enter index of neighbors of " << i << " vertex (-1 if there not more neighbors)\n";
			for (int j = nodes[i].n_counter;; j++)
			{
				do                                               //
				{                                                //
					key = 0;                                     //
					cout << ">> ";                               //
					cin >> line;                                 //
					t = 0;                                       //   //
					for (int l = 0; line[l] != '\0'; l++)        //   //
					{                                            //   //this moment will save your execution when u input "w2"
						t = t * 10 + int(line[l]) - 48;          //   //
					}                                            //   //
					key = 0;                                     //
					if (t == i) { key = 1; continue; };                //
					for (int l = 0; l < nodes[i].n_counter; l++) //
					{                                            //
						if (t == nodes[i].neighbors[l])          //here we are checking if this neig. already exists
						{                                        //
							key = 1;                             //
							break;                               //
						}                                        //
					}											 //
					line.clear();                                //

				} while (key);                                   //

				if (t < 0 or t >= vertexes)
					break;
				nodes[i].neighbors.push_back(t);//add a vertex in the end of neig. of this vertex
				nodes[t].neighbors.push_back(i);//add a vertex in the end of neig. of that vertex
				nodes[i].n_counter++;           //one more neig of node[i]
				nodes[t].n_counter++;           //one more neig of node[t]
				edges++;                        //one more edge

			}
		}
		sortForm();
	}
	void sortForm()
	{
		for (int i = 0; i < vertexes; i++)
			sort(nodes[i].neighbors.begin(), nodes[i].neighbors.end());
	}
	void showForm()
	{
		cout << "\nVERTEX |QUANTITY OF NEIGHBORS| ITS NEIGHBORS";
		for (int i = 0; i < vertexes; i++)
		{
			cout << endl;
			for (int j = 0; j < (10 + 21 + nodes[i].n_counter * 5); j++) cout << "-";
			printf("\n%7i|%21i|", nodes[i].index, nodes[i].n_counter);
			for (int j = 0; j < nodes[i].n_counter; j++)
			{
				printf("%5i", nodes[i].neighbors[j]);
			}
		}
	}
	~myForm() {};
	vector< vector<int> > BronKerboschForColouring()
	{
		int* matching = new int[vertexes];
		for (int i = 0; i < vertexes; i++)
		{
			matching[i] = nodes[i].index;
			nodes[i].index = i;
		}

		for (int i = 0; i < vertexes; i++)
		{
			for (int j = 0; j < nodes[i].n_counter; j++)
			{
				for (int k = 0; k < vertexes; k++)
				{
					if (nodes[i].neighbors[j] == matching[k])
					{
						nodes[i].neighbors[j] = k;
						break;
					}
				}
			}
		}
		int index_of_MIS = 0;
		vector< vector<int> > a(2 * vertexes * vertexes);

		int* S = new int[vertexes * (vertexes + 2)];       //We create arraies for S, Q_plus and Q_minus
		int* Q_plus = new int[vertexes * (vertexes + 2)];       //I use [i * j] because type of [i][j] has many difficulties
		int* Q_minus = new int[vertexes * (vertexes + 2)];
		for (int i = 0; i < vertexes * (vertexes + 2); i++)
		{
			S[i] = 0;
			Q_minus[i] = 0;
		}
		int* currentIndexPlus = new int[vertexes + 1]; //it is necessary for backtracking in cicle

		for (int i = 0; i <= vertexes; i++)
		{
			currentIndexPlus[i] = 0;

		}
		Q_plus[0] = vertexes;
		for (int i = 0; i < vertexes; i++)               //Fill Q_plus[0]
		{
			Q_plus[i + 1] = /*nodes[i].index*/i;
		}
		vertexes++;
		for (int i = 0; ;) //entry in cicle and exit condition 
		{
			currentIndexPlus[i]++; //here we go to the next vertex in Q_plus "deleting" those, that are befoe
			S[i * vertexes]++; //dimension of S is increases by one, first element shows a number of vertexes 
			S[i * vertexes + S[i * vertexes]] = Q_plus[i * vertexes + currentIndexPlus[i]]; //Here we transfer one vertex from Q_plus to S
			update(Q_plus, currentIndexPlus[i], Q_minus, S[i * vertexes + S[i * vertexes]], i); //Here we create new Q_plus and Q_minus
			if (!Q_plus[(i + 1) * vertexes] and !Q_minus[(i + 1) * vertexes]) //If Q_plus and Q_minus are empty - we have found new maximal independent set
			{
				for (int k = i * vertexes; k <= i * vertexes + S[i * vertexes]; k++)
				{
					if (k == i * vertexes)
					{
						a[index_of_MIS].push_back(S[k]);  //here we are putting dimension of independent set
						k++;
					}
					a[index_of_MIS].push_back(matching[S[k]]); //here we are putting a real index of vertex
				}
				index_of_MIS++;//when we inserted MIS, we should increase index for the next MIS
			}
			else //If there was not new MIS
			{
				if ((currentIndexPlus[i + 1] < Q_plus[(i + 1) * vertexes]) and neighboring_for_max(Q_plus, Q_minus, i + 1)) //We are checking if we can go to next iteration
				{
					for (int k = 0; k <= S[i * vertexes]; k++)
					{
						S[(i + 1) * vertexes + k] = S[i * vertexes + k];        //if we can, we create new S for the next level
					}
					Q_minus[i * vertexes]++;                                        
					Q_minus[i * vertexes + Q_minus[i * vertexes]] = S[i * vertexes + S[i * vertexes]]; //in S of this level we delete last obtained vertex and add it ti Q_minus
					S[i * vertexes]--;
					i++;
					continue;  //Here we go to the next iteration
				}
			}

			Q_minus[i * vertexes]++;
			Q_minus[i * vertexes + Q_minus[i * vertexes]] = S[i * vertexes + S[i * vertexes]]; //this part of code is necessary, if we found new MIS 
			S[i * vertexes]--;                                                                 //or can't go to next iteration

			if ((currentIndexPlus[i] < Q_plus[i * vertexes]) and neighboring_for_max(Q_plus, Q_minus, i)) //we go to next iteration if it's allowed
			{
				continue;
			}
			else                                     //in the other way, we should go back to some iteration ago
			{
				do
				{
					currentIndexPlus[i] = 0;
					i--;
					if (i < 0)  //one of conditions to exit
						break;
				} while (!((currentIndexPlus[i] < Q_plus[i * vertexes]) and neighboring_for_max(Q_plus, Q_minus, i)));
			}
			if (i < 0) //one of condtions to exit
				break;

		}
		while (index_of_MIS != a.size())  //delete empty arrays, they aren't needed
		{
			a.pop_back();
		}

		vertexes--;
		for (int i = 0; i < vertexes ; i++)
		{
			for (int j = 0; j < nodes[i].n_counter; j++)
			{
				nodes[i].neighbors[j] = matching[nodes[i].neighbors[j]];  //return real indexes to neighbors
			}
		}
		
		for (int i = 0; i < vertexes; i++)
		{
			nodes[i].index = matching[i];       //return real indexes to vertexes
		}
		/*free memory*/
		delete[]matching;
		delete[]currentIndexPlus;
		delete[]Q_minus;
		delete[]Q_plus;
		delete[]S;
		//return MISes
		return a;
	}


	bool neighboring_for_max(int*& Q_plus, int*& Q_minus, int index)//here we arechecking, any vertex of Q_minus must have neig. in Q_plus
	{
		bool subkey;

		for (int i = 0; i < Q_minus[index * vertexes]; i++)
		{
			subkey = 0;//by default vertex doesn't have neig
			for (int j = 0; j < nodes[Q_minus[index * vertexes + 1 + i]].n_counter; j++)
			{

				for (int l = 0; l < Q_plus[index * vertexes]; l++)
				{

					if (nodes[Q_minus[index * vertexes + 1 + i]].neighbors[j] == nodes[Q_plus[index * vertexes + 1 + l]].index)
					{
						subkey = 1; //if we have found at least one, we can leave cycle (not func)
						break;
					}
				}
				if (subkey) //and this cycle too
					break;
			}
			if (!subkey) //this cycle we can leave only if we've checked all vertexes or found at least one without neig.
				return 0;
		}
		return 1;
	}
	void update(int*& Q_plus, int plusIndex, int*& Q_minus, int node, int index) //here we are creating new Q_plus and Q_minus
	{
		int dimension_plus = 0, dimension_minus = 0;
		bool key;
		for (int i = plusIndex; i <= Q_plus[index * vertexes]; i++, key = 1) //We are starting from current position of Q_plus
		{
			if (!(nodes[Q_plus[index * vertexes + i]].index == node))        //if it's not the same, that we transfer to S
			{
				for (int j = 0; j < nodes[Q_plus[index * vertexes + i]].n_counter; j++)  
				{

					if (node == nodes[Q_plus[index * vertexes + i]].neighbors[j])  //and if this Q_plus vertex is not neig. of new item in S
					{
						key = 0;  //key remains 1 and we can add it in new Q_plus
						break;
					}
				}
			}
			else
			{
				key = 0;         //in other way it become 0
			}
			if (key) //if key is 1
			{
				dimension_plus++;            //then we increase by one dimension of new Q_plus
				Q_plus[(index + 1) * vertexes + dimension_plus] = nodes[Q_plus[index * vertexes + i]].index; //and put new node in new Q_plus
			}
		}
		Q_plus[(index + 1) * vertexes] = dimension_plus; //New dimension of new Q_plus


		//the same action with new Q_minus
		for (int i = 0; i < Q_minus[index * vertexes]; i++, key = 1)
		{

			for (int j = 0; j < nodes[Q_minus[index * vertexes + i + 1]].n_counter; j++)
				if (node == nodes[Q_minus[index * vertexes + i + 1]].neighbors[j])
				{
					key = 0;
					break;
				}
			if (key)
			{
				dimension_minus++;
				Q_minus[(index + 1) * vertexes + dimension_minus] = nodes[Q_minus[index * vertexes + i + 1]].index;
			}
		}
		Q_minus[(index + 1) * vertexes] = dimension_minus;
	}

	friend void colouring(myForm);
	friend myForm splitGraph(myForm, vector<int>);
};
