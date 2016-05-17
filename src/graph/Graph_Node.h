
#ifndef GRAPH_NODE_H
#define GRAPH_NODE_H

#include"stdlib.h"
#include"stdio.h"
#include<queue>

#ifdef NOPRINTF

#define printf(x...)

#endif

using namespace std;

#define ALLOCATION_STEP 5

class Graph_Node
{


	bool token;	//used to mark those nodes of the graph already printed

	static FILE* fp;  	//used to print a log
	static queue<Graph_Node*> print_queue;

	void initialize();
	inline void inlineRemoveConnectionWithIndex(int index);
	void recursivelyPrint();
	void recursivelyPrintValue();
	void recursivelyFillLeafIds(int* leaf_array, int * counter);

public:

	//use only one of the following constructors, otherwise the id_counter might create nodes with repeated id.
	Graph_Node();
	Graph_Node(float id); 
	~Graph_Node();
	
	float id;	
	double value;
	static float id_counter; 	//used when no id is passed to the constructor

	Graph_Node** connection;
	double* connection_weight;
	
	int connection_number;	
	int connection_allocated;	//number allocated in the array of connections, it stores ALLOCATION_STEP more edges than it need to every time it reallocs

	void insertConnection(Graph_Node* node, double weight=0.0f);
	void removeAnyConnectionWithNode(Graph_Node* node);
	Graph_Node* removeConnectionWithIndex(int index);	//remove a connection in a respective index of the vector of connections
	Graph_Node* removeConnectionWithId(int id);		//return the removed connection
	int numberOfLeafNodes();
	int* arrayOfLeafIds(int* array_size);
	int treeHeight();

	void print(const char* filename);
	void print();
	//pass an array of Graph_Nodes to be printed together, 
	//those Graph Nodes passed are like the roots of the trees composing a forest data structure
	static void print(Graph_Node** roots, int number_of_roots, const char* filename=NULL); 
	static void printValue(Graph_Node** roots, int number_of_roots, const char* filename=NULL); 

	//functions that only work for trees
	void deleteTree();

	//neural networks and maybe other dynamical networks
	void passValue();	//pass value to connected nodes, multiplied by the weights of the connections

};


#endif
