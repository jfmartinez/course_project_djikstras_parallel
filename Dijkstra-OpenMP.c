//  Author: Jose F. Martinez Rivera
//  Course: ICOM4036 - 040
//	Professor: Wilson Rivera Gallego
// 	Assignment 2 - OpenMP Implementation


#include <stdio.h>
#include <time.h>
#include <math.h>
#include <omp.h>


#define INT_MAX 100000
#define TRUE    1
#define FALSE   0
#define V 8
#define E 11

//boolean type
typedef int bool;

//Represents an edge or path between Vertices
typedef struct
{
	int u;
	int v;

} Edge;

//Represents a Vertex
typedef struct 
{
	int title;
	bool visited;	

} Vertex;

//Prints the array
void printArray(int *array)
{
	int i;
	for(i = 0; i < V; i++)
	{
		printf("Path to Vertex %d is %d\n", i, array[i]);
	}
}

//OpenMP Implementation of Dijkstra's Algorithm
void DijkstraOMP(Vertex *vertices, Edge *edges, int *weights, Vertex *root)
{	


	double start, end;
	





	root->visited = TRUE;
	
	int len[V];
	len[(int)root->title] = 0;

	int i, j;
	
	for(i = 0; i < V;i++)
	{

		if(vertices[i].title != root->title)
		{
			len[(int)vertices[i].title] = findEdge(*root, vertices[i], edges, weights);
			

		}
		else{
		
			vertices[i].visited = TRUE;
		}


	}

	
	start = omp_get_wtime();
	for(j = 0; j < V; j++){

		
		Vertex u;
		int h = minPath(vertices, len);
		u = vertices[h];
		
		
		//OpenMP Parallelization Starts here!!!
		#pragma omp parallel for schedule(runtime) private(i)
			for(i = 0; i < V; i++)
			{
				if(vertices[i].visited == FALSE)
				{	
					int c = findEdge( u, vertices[i], edges, weights);
					len[vertices[i].title] = minimum(len[vertices[i].title], len[u.title] + c);
				
				}
			}
		

	

	}
	end = omp_get_wtime();
	printArray(len);
	printf("Running time: %f ms\n", (end - start)*1000);
	
	
	
}


//Finds the edge that connects Vertex u with Vertex v
int findEdge(Vertex u, Vertex v, Edge *edges, int *weights)
{

	int i;
	for(i = 0; i < E; i++)
	{

		if(edges[i].u == u.title && edges[i].v == v.title)
		{
			return weights[i];
		}
	}

	return INT_MAX;




}

//Returns the minimum between two integers
int minimum(int A, int B)
{
	if( A > B)
	{
		return B;
	}

	else{
		return A;
	}
}

//Visits the vertices and looks for the lowest weight from the vertex
int minWeight(int *len, Vertex *vertices)
{
	int i;
	int minimum = INT_MAX;
	for(i = 0; i < V; i++)
	{
		if(vertices[i].visited == TRUE)
		{
			continue;
		}
		
		else if(vertices[i].visited == FALSE && len[i] < minimum)
		{
			minimum = len[i];
			
		}
		
	}
	return minimum;
}

//Localizes the vertex with the lowest weight path
int minPath(Vertex *vertices, int *len)
{
	int i;
	int min = minWeight(len, vertices);
	
	for(i = 0; i < V; i++)
	{
		if(vertices[i].visited == FALSE && len[vertices[i].title] == min)
		{
			vertices[i].visited = TRUE;
			return i;

		}
	}
	
	
	
	
}






int main(void)
{



	Vertex vertices[V];
	// Edge edges[E];
	// int weights[E];
	
	
	//----------------------------------Graph Base Test-------------------------------------//

	Edge edges[E] ={{0, 4}, {0, 6}, {0,2}, {4,6}, {4,7}, {0, 7}, {7, 3}, {3, 1}, {2,5}, {2, 1}, {5,3}};
	int weights[E] = {10, 90, 30, 20, 20, 50, 10, 20, 10, 10, 10};

	int i = 0;
	for(i = 0; i < V; i++)
	{
		Vertex a = { .title =i , .visited=FALSE};
		vertices[i] = a;


	}

	//----------------------------------Graph Base Test-------------------------------------//

	//--------------------------------Graph Randomizer-----------------------------------//


	// srand(time(NULL));
	// int i = 0;
	// for(i = 0; i < V; i++)
	// {
	// 	Vertex a = { .title =(int) i, .visited=FALSE};
	// 	vertices[i] = a;


	// }



	// for(i = 0; i < E; i++)
	// {

	// 	Edge e = {.u = (int) rand()%V , .v = rand()%V};
	// 	edges[i] = e;

	// 	weights[i] = rand()%100;

	// }
	//--------------------------------Graph Randomizer-----------------------------------//


	Vertex root = {0, FALSE};

	printf("OpenMP Results for Small Graph of 8 Vertices:\n");
	DijkstraOMP(vertices, edges, weights, &root);

	
	




}



	
	
	
	
	
	
	
	
	
	
	
	
	
