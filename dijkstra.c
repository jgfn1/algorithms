#include "stdio.h"
#include "stdlib.h"
typedef struct linked_list
{
    int value;
    int weight;
    struct linked_list* next;
} lists;

typedef struct graph
{
    int vertex_number;
    int edge_number;
    lists* adj_list;
    lists** front;
    lists** rear;
} graphs;

typedef struct heap
{
    int* array;
    int array_size;
    int* weight;
    int weight_size;
    int size;	//Number of elements in the heap.
} heap;

typedef struct pair
{
    int value1;
    int value2;
} pairs;

void dijkstra(graphs* graph, int source);

graphs* graph_insert(graphs* graph, int vertix1, int vertix2, int weight);

lists* list_insert(lists* cur, int value, int weight);
void enqueue(lists* rear, int value, int weight);

heap* heap_insert(heap* Heap, int value, int weight);
void build_heap(heap* Heap);
heap* bubble_up(heap* Heap);
void heapify(heap* Heap, int sub_tree_index);
pairs *heap_extract(heap* Heap);
void heap_update(heap* Heap, int new_weight, int vertix);
int heap_pos(heap* Heap, int value);
int* array_doubleler(int** array, int* array_size);

heap Heaper;
int* distances; //Minimum distance from S to all the vertex_number vertices
int* fathers;	//Father of each vertix

int main()
{
//------------------------------Graph Initializer-------------------------------------//
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
//------------------------------------------------------------------------------------//

    distances = (int*) malloc(vertex_number * sizeof(int));
    fathers = (int*) malloc(vertex_number * sizeof(int));

    int source = 0;
    int destination = 0;
    printf("Insert the path to be calculated by Dijkstra in the form 'source destination':\n");
    scanf("%d %d", &source, &destination);
    dijkstra(graph, source);
    printf("The minimum-path cost is: %d\n", distances[destination]);
}

void dijkstra(graphs* graph, int source)
{
    int i = 0;
    pairs* pair = NULL;
    lists* cursor = NULL;

    for(i = 0; i < graph->vertex_number; ++i)
    {
        distances[i] = -1;
        fathers[i] = -1;
    }

    distances[source] = 0;

//--------------------------Heap Initializer------------------//
    Heaper.array = (int*) malloc(sizeof(int));
    Heaper.weight = (int*) malloc(sizeof(int));
    Heaper.array_size = 1;
    Heaper.weight_size = 1;
    Heaper.size = 0;
//-----------------------------------------------------------//

    heap_insert(&Heaper, source, 0);

    for(i = 0; i < graph->vertex_number; ++i)
    {
        pair = heap_extract(&Heaper);
        if(pair->value1 != -1 && pair->value2 != -1)
        {
            cursor = &graph->adj_list[pair->value1];
            cursor = cursor->next;
            while(cursor != NULL)
            {
                if(distances[cursor->value] == -1 || (distances[pair->value1] + cursor->weight) < distances[cursor->value])
                {
                    distances[cursor->value] = distances[pair->value1] + cursor->weight;
                    fathers[cursor->value] = pair->value1;
                    heap_update(&Heaper, distances[cursor->value], cursor->value);
                }
                cursor = cursor->next;
            }
        }
    }
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

lists* list_insert(lists* cur, int value, int weight)	// Push
{
    lists* node  = (lists*) malloc(sizeof(lists));
    node->value = value;
    node->weight = weight;
    node->next = cur->next;
    cur->next = node;
    return cur;
}

void enqueue(lists* rear, int value, int weight)
{
    lists* new_rear = list_insert(rear, value, weight);
    rear = new_rear->next;
}

int heap_pos(heap* Heap, int value)
{
    int i;
    for(i = 0; i < Heap->array_size; ++i)
    {
        if(Heap->array[i] == value)
            return i;
    }
    return -1;
}

void heap_update(heap* Heap, int new_weight, int vertix)
{
    int i = heap_pos(Heap, vertix);
    if(i != -1)
    {
        Heap->weight[i] = new_weight;
        build_heap(Heap);
    }
    else
        heap_insert(Heap, vertix, new_weight);
}

heap* heap_insert(heap* Heap, int value, int weight)
{
    if(Heap->size == Heap->array_size)
        Heap->array = array_doubleler(&(Heap->array), &(Heap->array_size));

    if(Heap->size == Heap->weight_size)
        Heap->weight = array_doubleler(&(Heap->weight), &(Heap->weight_size));

    Heap->array[Heap->size] = value;
    Heap->weight[Heap->size] = weight;
    Heap->size++;
    Heap = bubble_up(Heap);
    return Heap;
}

void build_heap(heap* Heap)
{
    int i;
    for(i = ((Heap->size / 2) - 1); i >= 0; --i)
        heapify(Heap, i);
}

heap* bubble_up(heap* Heap)
{
    int i = Heap->size - 1;
    while(i > 0 && (Heap->weight[i] /*order_relation*/ <= Heap->weight[(i - 1) / 2]))
    {
        int exchanger = Heap->weight[i];
        Heap->weight[i] = Heap->weight[(i - 1) / 2];
        Heap->weight[(i - 1) / 2] = exchanger;

        exchanger = Heap->array[i];
        Heap->array[i] = Heap->array[(i - 1) / 2];
        Heap->array[(i - 1) / 2] = exchanger;

        i = (i - 1) / 2;
    }
    return Heap;
}

void heapify(heap* Heap, int sub_tree_index)
{
    int left_node = (2 * sub_tree_index) + 1;
    int right_node = (2 * sub_tree_index) + 2;
    int node = sub_tree_index;

    if(left_node < Heap->size && (Heap->weight[left_node] /*order_relation*/ <= Heap->weight[node]))
        node = left_node;
    if(right_node < Heap->size && (Heap->weight[right_node] /*order_relation*/ <= Heap->weight[node]))
        node = right_node;

    if(node != sub_tree_index)
    {
        int exchanger = Heap->weight[sub_tree_index];
        Heap->weight[sub_tree_index] = Heap->weight[node];
        Heap->weight[node] = exchanger;

        exchanger = Heap->array[sub_tree_index];
        Heap->array[sub_tree_index] = Heap->array[node];
        Heap->array[node] = exchanger;

        heapify(Heap, node);
    }
}

pairs *heap_extract(heap* Heap)
{
    pairs *pair = (pairs*) malloc(sizeof(pairs));
    pair->value1 = -1;
    pair->value2 = -1;
    if(Heap->size > 0)
    {
        pair->value1 = Heap->array[0];
        pair->value2 = Heap->weight[0];

        int exchanger = Heap->array[0];
        Heap->array[0] = Heap->array[Heap->size - 1];
        Heap->array[Heap->size - 1] = exchanger;

        exchanger = Heap->weight[0];
        Heap->weight[0] = Heap->weight[Heap->size - 1];
        Heap->weight[Heap->size - 1] = exchanger;

        Heap->size--;
        heapify(Heap, 0);
    }
    return pair;
}

int* array_doubleler(int** array, int* array_size)
{
    *array = (int*) realloc(*array, *(array_size) * 2 * sizeof(int));
    *array_size *= 2;
    return *array;
}