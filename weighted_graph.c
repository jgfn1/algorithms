#include "stdio.h"
#include "stdlib.h"

typedef struct linked_list
{
	struct linked_list* next;
	int value;
	int weight;
} lists;

typedef struct graph
{
	lists* adj_list;
	lists** front;
	lists** rear;
	int vertex_number;
	int edge_number;
} graphs;

graphs* graph_insert(graphs* graph, int vertix1, int vertix2, int weight);
void graph_print(graphs* graph);

lists* list_find(lists* head, int value);
lists* list_insert(lists* cur, int value, int weight);
int list_delete(lists* cur);
void enqueue(lists* rear, int value, int weight);
int dequeue(lists* front, lists* rear);

int main()
{
	int i = 0;
	int vertex_number = 0;
	int edge_number = 0;
	int vertix1 = 0;
	int vertix2 = 0;
	int weight = 0;
	graphs* graph = (graphs*) malloc(sizeof(graphs));
	graph->adj_list = NULL;
	graph->vertex_number = 0;
	graph->edge_number = 0;

	printf("Insert the number of vertices and edges, respectively:\n");
	scanf("%d %d", &vertex_number, &edge_number);
	
	graph->adj_list = (lists*) malloc(vertex_number * sizeof(lists));
	
	graph->front = (lists**) malloc(vertex_number * sizeof(lists));
	graph->rear = (lists**) malloc(vertex_number * sizeof(lists));

	for(i = 0; i < vertex_number; ++i)
	{
		graph->front[i] = &graph->adj_list[i];
		graph->rear[i] = &graph->adj_list[i];
	}

	graph->vertex_number = vertex_number;
	graph->edge_number = edge_number;

	printf("Insert the edges in the form 'vertix1 vertix2 weight'):\n");
	for(i = 0; i < edge_number; ++i)
	{
		scanf("%d %d %d", &vertix1, &vertix2, &weight);
		graph = graph_insert(graph, vertix1, vertix2, weight);
	}

	int command;
	do
	{
		printf("Type 0 to print the edges, 1 to delete an edge, 2 to calculate the shortest path between two vertices or -1 to leave.\n");
		scanf("%d", &command);
		if(command == 0)
		{
			graph_print(graph);
		}
		else if(command == 1)
		{

		}
		else if(command == 2)
		{

		}
	} while(command != -1);
}

graphs* graph_insert(graphs* graph, int vertix1, int vertix2, int weight)
{
	if(vertix1 != vertix2)
	{
		enqueue(graph->rear[vertix1], vertix2, weight);
		enqueue(graph->rear[vertix2], vertix1, weight);		
	}
	else
	{
		enqueue(graph->rear[vertix1], vertix2, weight);
	}
	return graph;
}

void graph_print(graphs* graph)
{
	lists* list = NULL;
	int i;
	for(i = 0; i < graph->vertex_number; ++i)
	{
		list = &graph->adj_list[i];
		list = list->next;
		while(list != NULL)
		{
			printf("(%d,%d) | w: %d ||| ", i, list->value, list->weight);
			list = list->next;
		}
		printf("\n");
	}
}

lists* list_find(lists* head, int value)
{
	lists* cur = head;
	while((cur->next != NULL) && (cur->next->value != value))
		cur = cur->next;
	return cur;
}

lists* list_insert(lists* cur, int value, int weight)	// Push
{
	lists* node  = (lists*) malloc(sizeof(lists));
	node->value = value;
	node->weight = weight;
	node->next = cur->next;
	cur->next = node;
	return cur;
}

int list_delete(lists* cur)	//Pop
{
	if(cur->next != NULL)
	{
		lists* aux = cur->next;
		int value = aux->value;
		cur->next = aux->next;
		free(aux);
		return value;
	}
}

void enqueue(lists* rear, int value, int weight)
{
	lists* new_rear = list_insert(rear, value, weight);
	rear = new_rear->next;
}

int dequeue(lists* front, lists* rear)
{
	int value = list_delete(front);
	lists* new_rear;
	lists* new_front = front;
	if(new_front == NULL)
	{
		new_rear = new_front;
		rear = new_rear;
		front = new_front;
	}
	return value;
}