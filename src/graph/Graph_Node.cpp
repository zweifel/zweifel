
#include"Graph_Node.h"
	
Graph_Node::Graph_Node(float id)
{
	this->id= id;
	
	initialize();
}

Graph_Node::Graph_Node()
{
	this->id= ++id_counter;

	initialize();
}

void Graph_Node::initialize()
{
	connection_number=0;
	connection_allocated=ALLOCATION_STEP;

	connection=(Graph_Node**)malloc(sizeof(Graph_Node*)*connection_allocated);
	connection_weight=(double*)malloc(sizeof(double)*connection_allocated);

	value=0.0;
	token=false;
}

Graph_Node::~Graph_Node()
{
	free(connection);
	free(connection_weight);
}

/*****************************************************************
 *	Delete Entire Tree
 *
 *	NOTE that this only works for TREES!! 
 *	Because a generic graph could contain a cyclic path
 * *************************************************************/
void Graph_Node::deleteTree()
{
	int i;

	//printf("entering %.0f\n",this->id);
	//loop through all the connections, recursively
	for(i=0;i<connection_number;i++)
	{
		//recursively call this function
		connection[i]->deleteTree();
	}

	//printf("deleting %.0f\n",this->id);
	delete this;
	//printf("deleted\n");
	

}

void Graph_Node::insertConnection(Graph_Node* node, double weight)
{
	connection_number++;

	//check if there is enough allocated space
	if(connection_number > connection_allocated)
	{
		connection_allocated+=ALLOCATION_STEP;

		connection=(Graph_Node**)realloc(connection, sizeof(Graph_Node*)*connection_allocated);
		connection_weight=(double*)realloc(connection_weight, sizeof(double)*connection_allocated);
	}
	
	//insert it
	connection[connection_number-1]=node;
	connection_weight[connection_number-1]=weight;
}

void Graph_Node::removeAnyConnectionWithNode(Graph_Node* node)
{
	int i;

	for(i=0;i<connection_number;++i)
	{	
		//if the node is found
		if(connection[i]==node)
		{
			inlineRemoveConnectionWithIndex(i);

			//since the last connection was put inside this connection
			//we have to check this connection again, so we decrease the counter
			//to check it in the next iteraction
			i--;
		}
	}
}

Graph_Node* Graph_Node::removeConnectionWithId(int id)
{
	int i;
	Graph_Node* removed_node;

	for(i=0;i<connection_number;++i)
	{	
		//if the node is found
		if((connection[i])->id==id)
		{
			removed_node= connection[i];
		
			//this connection is substituted with the last connection
			connection[i]= connection[connection_number-1];
			connection_weight[i]= connection_weight[connection_number-1];

			//number of connections decreased
			connection_number--;
			
			return removed_node;
		}
	}

	return NULL;
}

void Graph_Node::inlineRemoveConnectionWithIndex(int index)
{
	//this connection is substituted with the last connection
	connection[index]= connection[connection_number-1];
	connection_weight[index]= connection_weight[connection_number-1];

	//number of connections decreased
	connection_number--;
}

//return the node which was removed
Graph_Node* Graph_Node::removeConnectionWithIndex(int index)
{
	Graph_Node* removed_node= connection[index];
	
	inlineRemoveConnectionWithIndex(index);

	//since the removed node is the node after the last node, we return it
	return removed_node;
}

//return the number of leaf nodes
int Graph_Node::numberOfLeafNodes()
{
	int i;
		
	if(connection_number==0)
	{
		return 1;		
	}

	int leaf_nodes=0;

	//loop through all the connections, recursively
	for(i=0;i<connection_number;i++)
	{
		leaf_nodes+=connection[i]->numberOfLeafNodes();
	}

	return leaf_nodes;
}

int Graph_Node::treeHeight()
{
	int i;
		
	if(connection_number==0)
	{
		return 0;		
	}

	int height=0;

	//loop through all the connections, recursively
	for(i=0;i<connection_number;i++)
	{
		int new_height= connection[i]->treeHeight();
		
		if(height < new_height)
		{
			height= new_height;
		}

	}

	height++;

	return height;
}



//return the array of ids of all the leafs from this node below and 
//the size of the array in the array_size variable
int* Graph_Node::arrayOfLeafIds(int* array_size)
{
	*array_size= this->numberOfLeafNodes();

	int* leaf_ids= (int*)malloc(sizeof(int)*(*array_size));

	int counter=0;

	recursivelyFillLeafIds(leaf_ids, &counter);

	return leaf_ids;
}

void Graph_Node::recursivelyFillLeafIds(int* leaf_array, int * counter)
{
	int i;

	if(connection_number==0)
	{
		leaf_array[(*counter)]=(int)id;
		(*counter)++;

		return ;
	}
	

	//loop through all the connections, recursively
	for(i=0;i<connection_number;i++)
	{
		connection[i]->recursivelyFillLeafIds(leaf_array,counter);
	}

}

void Graph_Node::recursivelyPrint()
{
	int i;

	//put token and insert in the queue
	token=true;
	print_queue.push(this);

	if(connection_number==0)
	{
		//fprintf(fp, "%.2f\n", id);	
		fprintf(fp, "%d\n", (int)id);	
		return;
	}

	//loop through all the connections, recursively
	for(i=0;i<connection_number;i++)
	{
		//fprintf(fp, "%.2f -> %.2f [label=\"%.1f\"];\n", id, (connection[i])->id, connection_weight[i]);	
		fprintf(fp, "%d -> %d [label=\"%.1f\"];\n", (int)id, (int)(connection[i])->id, connection_weight[i]);	
	
		//if the node which it is connected has already a token, do nothing
		if(connection[i]->token)
		{
			//do nothing
		}
		else
		{
			//recursively call this function
			connection[i]->recursivelyPrint();
		}
	}


}

void Graph_Node::recursivelyPrintValue()
{
	int i;

	//put token and insert in the queue
	token=true;
	print_queue.push(this);

	//if(connection_number==0)
	{
		//fprintf(fp, "%.2f\n", id);	
		fprintf(fp, "%d [label = %lf]\n", (int)id, value);	
		//return;
	}

	//loop through all the connections, recursively
	for(i=0;i<connection_number;i++)
	{
		//fprintf(fp, "%.2f -> %.2f [label=\"%.1f\"];\n", id, (connection[i])->id, connection_weight[i]);	
		fprintf(fp, "%d -> %d [label=\"%.1f\"];\n", (int)id, (int)(connection[i])->id, connection_weight[i]);	
	
		//if the node which it is connected has already a token, do nothing
		if(connection[i]->token)
		{
			//do nothing
		}
		else
		{
			//recursively call this function
			connection[i]->recursivelyPrintValue();
		}
	}


}


void Graph_Node::print(const char* filename)
{
	if(filename==NULL)
		fp= fopen("graph_structure.dot","w");
	else
		fp= fopen(filename,"w");
		

	fprintf(fp, "digraph G {\n");
	fprintf(fp, "node [layer=all];\n");
	fprintf(fp, "edge [layer=all];\n");
	fprintf(fp, "node [shape = circle];\n");

	recursivelyPrint();

	fprintf(fp, "}\n");

	fclose(fp);

	while(!print_queue.empty())
	{
		Graph_Node* node= print_queue.front();
		node->token=false;
		print_queue.pop();
	}

}

void Graph_Node::print()
{
	fp= fopen("graph_structure.dot","w");
		

	fprintf(fp, "digraph G {\n");
	fprintf(fp, "node [layer=all];\n");
	fprintf(fp, "edge [layer=all];\n");
	fprintf(fp, "node [shape = circle];\n");

	recursivelyPrint();

	fprintf(fp, "}\n");

	fclose(fp);

	while(!print_queue.empty())
	{
		Graph_Node* node= print_queue.front();
		node->token=false;
		print_queue.pop();
	}

}
	
//pass an array of Graph_Nodes to be printed together, 
//those Graph Nodes passed are like the roots of the trees composing a forest data structure
void Graph_Node::print(Graph_Node** roots, int number_of_roots, const char* filename)
{
	if(filename==NULL)
		fp= fopen("graph_structure.dot","w");
	else
		fp= fopen(filename,"w");
		

	fprintf(fp, "digraph G {\n");
	fprintf(fp, "node [layer=all];\n");
	fprintf(fp, "edge [layer=all];\n");
	fprintf(fp, "node [shape = circle];\n");

	for(int i=0; i<number_of_roots; ++i)
	{
		roots[i]->recursivelyPrint();
	}

	fprintf(fp, "}\n");

	fclose(fp);

	while(!print_queue.empty())
	{
		Graph_Node* node= print_queue.front();
		node->token=false;
		print_queue.pop();
	}

	
}

//pass an array of Graph_Nodes to be printed together, 
//those Graph Nodes passed are like the roots of the trees composing a forest data structure
void Graph_Node::printValue(Graph_Node** roots, int number_of_roots, const char* filename)
{
	if(filename==NULL)
		fp= fopen("graph_structure.dot","w");
	else
		fp= fopen(filename,"w");
		

	fprintf(fp, "digraph G {\n");
	fprintf(fp, "node [layer=all];\n");
	fprintf(fp, "edge [layer=all];\n");
	fprintf(fp, "node [shape = circle];\n");

	for(int i=0; i<number_of_roots; ++i)
	{
		roots[i]->recursivelyPrintValue();
	}

	fprintf(fp, "}\n");

	fclose(fp);

	while(!print_queue.empty())
	{
		Graph_Node* node= print_queue.front();
		node->token=false;
		print_queue.pop();
	}

	
}

//pass value to connected nodes, multiplied by the weights of the connections
void Graph_Node::passValue()
{
	int i;
	
	for(i=0;i<connection_number;++i)
	{	
		connection[i]->value+= connection_weight[i]*this->value;
	}

	this->value=0;
}

//pass value to connected nodes, multiplied by the weights of the connections
/*void Graph_Node::cleanSystemValues()
{
	int i;

	//put token and insert in the queue
	token=true;
	print_queue.push(this);

	//if(connection_number==0)
	{
		//fprintf(fp, "%.2f\n", id);	
		fprintf(fp, "%d\n [label = %lf]", (int)id, value);	
		return;
	}

	//loop through all the connections, recursively
	for(i=0;i<connection_number;i++)
	{
		//fprintf(fp, "%.2f -> %.2f [label=\"%.1f\"];\n", id, (connection[i])->id, connection_weight[i]);	
		fprintf(fp, "%d -> %d [label=\"%.1f\"];\n", (int)id, (int)(connection[i])->id, connection_weight[i]);	
	
		//if the node which it is connected has already a token, do nothing
		if(connection[i]->token)
		{
			//do nothing
		}
		else
		{
			//recursively call this function
			connection[i]->recursivelyPrint();
		}
	}
}*/
	
FILE* Graph_Node::fp;  	//used to print a log
queue<Graph_Node*> Graph_Node::print_queue;
float Graph_Node::id_counter = -1;
