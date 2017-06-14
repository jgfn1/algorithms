#include "stdio.h"
#include "stdlib.h"

typedef struct uni_f
{
    struct uni_f* parent;
    int value;
    int height;
} node;

node* find_path_compression(node* element);
node* make_set(int value);
node* find(node* element);
node* union_(node* element1, node* element2);

typedef struct linked_list
{
    int value;
    struct linked_list* next;
} lists;

typedef struct graph
{
    lists* adj_list;
    lists** front;
    lists** rear;
    int vertex_number;
    int edge_number;
} graphs;

graphs* graph_insert(graphs* graph, int vertix1, int vertix2);
void graph_print(graphs* graph);
int* shortest_path(graphs* graph, int source);

lists* list_find(lists* head, int value);
lists* list_insert(lists* cur, int value);
int list_delete(lists* cur);
lists* enqueue(lists* rear, int value);
lists* dequeue(lists* front, lists* rear);

void contraction(graphs* graph, int vertix1, int vertix2);

int vertex_value;

int global_vertex_quant;

node* element;

int main()
{
    int i;
    int vertex_number;
    int edge_number;
    int vertix1;
    int vertix2;
    graphs* graph = (graphs*) malloc(sizeof(graphs));
    graph->adj_list = NULL;
    graph->vertex_number = 0;
    graph->edge_number = 0;

    scanf("%d %d", &vertex_number, &edge_number);
    global_vertex_quant = vertex_number;

    element = (node*) malloc(vertex_number * sizeof(node));

    graph->adj_list = (lists*) malloc(vertex_number * sizeof(lists));

    graph->front = (lists**) malloc(vertex_number * sizeof(lists));
    graph->rear = (lists**) malloc(vertex_number * sizeof(lists));

    for(i = 0; i < vertex_number; ++i)
    {
        graph->front[i] = &graph->adj_list[i];
        graph->rear[i] = &graph->adj_list[i];
        element[i] = *(make_set(i));
    }
    /*for (i = 0; i < vertex_number; ++i)
    {
    	printf("%d\n", element[i].parent->value);
    }*/

    graph->vertex_number = vertex_number;
    graph->edge_number = edge_number;

    for(i = 0; i < edge_number; ++i)
    {
        scanf("%d %d", &vertix1, &vertix2);
        graph = graph_insert(graph, vertix1, vertix2);
    }
    int operation_number;
    char command;
    scanf("%d", &operation_number);
    for(i = 0; i < operation_number; ++i)
    {
        scanf(" %c", &command);
        if(command == 'c')
        {
            scanf("%d %d", &vertix1, &vertix2);
            contraction(graph, vertix1, vertix2);
            printf("%d\n", global_vertex_quant);
        }
        else if(command == 'd')
        {
            scanf("%d %d", &vertix1, &vertix2);
            if(vertix1 != vertix2)
            {
                node* repr_A = find(&element[vertix1]);
                node* repr_B = find(&element[vertix2]);
                if(repr_A != repr_B)
                {
                    int* distances = shortest_path(graph, repr_A->value);
                    printf("%d\n", distances[repr_B->value]);
                }
                else
                    printf("0\n");
            }
            else
                printf("0\n");
        }
    }
}

void contraction(graphs* graph, int vertix1, int vertix2)
{
    lists* vertex_list;
    node* dominant;

    node* repr_A = find(&element[vertix1]);
    node* repr_B = find(&element[vertix2]);


    if(repr_A != repr_B)
    {
        dominant = union_(&element[repr_A->value], &element[repr_B->value]);
        global_vertex_quant--;

        if(repr_A == dominant)
        {
            vertex_list /*e*/= &graph->adj_list[repr_A->value];
            while(vertex_list != NULL)
            {
                if(vertex_list->next != NULL && vertex_list->next->value == repr_B->value)
                {
                    list_delete(vertex_list);
                }
                vertex_list = vertex_list->next;
            }

            vertex_list = &graph->adj_list[repr_B->value];
            while(vertex_list->next != NULL)
            {
                int aux = list_delete(vertex_list);
                if(aux != repr_A->value && aux != repr_B->value && aux != -1)
                {
                    list_insert(&graph->adj_list[repr_A->value], aux);
                }
            }
        }
        else if(repr_B == dominant)
        {
            vertex_list /*e*/= &graph->adj_list[vertix2];
            while(vertex_list != NULL)
            {
                if(vertex_list->next != NULL && vertex_list->next->value == vertix1)
                {
                    list_delete(vertex_list);
                }
                vertex_list = vertex_list->next;
            }

            vertex_list = &graph->adj_list[repr_A->value];
            while(vertex_list->next != NULL)
            {
                int aux = list_delete(vertex_list);
                if(aux != repr_A->value && aux != repr_B->value && aux != -1)
                {
                    list_insert(&graph->adj_list[repr_B->value], aux);
                }
            }
        }

    }
}

graphs* graph_insert(graphs* graph, int vertix1, int vertix2)
{
    if(vertix1 != vertix2)
    {
        enqueue(graph->rear[vertix1], vertix2);
        enqueue(graph->rear[vertix2], vertix1);
    }
    else
    {
        enqueue(graph->rear[vertix1], vertix2);
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
            printf("(%d,%d) ", i, list->value);
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

lists* list_insert(lists* cur, int value)	// Push
{
    lists* node  = (lists*) malloc(sizeof(lists));
    node->value = value;
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
    return -1;
}

lists* enqueue(lists* rear, int value)
{
    lists* new_rear = list_insert(rear, value);
    new_rear = new_rear->next;
    return new_rear;
}

lists* dequeue(lists* front, lists* rear)
{
    int value = list_delete(front);
    lists* new_rear;
    lists* new_front = front;
    if(new_front->next == NULL)
    {
        new_rear = new_front;
    }
    else
        new_rear = rear;
    vertex_value = value;
    return new_rear;
}

int* shortest_path(graphs* graph, int source)
{
    int i;
    int value;
    lists* vertex_list;
    int* distances = (int*) malloc(graph->vertex_number * sizeof(int));
    for(i = 0; i < graph->vertex_number; ++i)
    {
        distances[i] = -1;
    }
    distances[source] = 0;
    lists* list = (lists*) malloc(sizeof(lists));
    list->next = NULL;
    lists* rear = list;
    lists* front = list;
    rear = enqueue(rear, source);
    while(rear != front)
    {
        /*vertex_value u*/ rear = dequeue(front, rear);
        vertex_list /*e*/= &graph->adj_list[vertex_value];
        vertex_list = vertex_list->next; //graph->adj_list[vertex_value] is the sentinel.
        while(vertex_list != NULL)
        {
            value /*v*/ = vertex_list->value;
            node* repr_value = find(&element[value]);
            value = repr_value->value;

            if(distances[value] == -1)
            {
                distances[value] = distances[vertex_value] + 1;
                rear = enqueue(rear, value);
            }
            vertex_list = vertex_list->next;
        }
    }
    return distances;
}


node* find_path_compression(node* element)
{
    if(element->parent != element)
    {
        element->parent = find_path_compression(element->parent);
    }
    return element->parent;
}

node* make_set(int value)
{
    node* element = (node*) malloc(sizeof(node));
    element->value = value;
    element->parent = element;
    element->height = 1;
    return element;
}

node* find(node* element)
{
    if(element->parent == element)
        return element;
    else
        return find(element->parent);
}

node* union_(node* element1, node* element2)
{
    node* parent1 =  find(element1);
    node* parent2 =  find(element2);
    if(parent1 == parent2)
        return parent1;
    else if(parent1->height < parent2->height)
    {
        parent1->parent = parent2;
        return parent2;
    }
    else
    {
        parent2->parent = parent1;
        if(parent1->height == parent2->height)
            parent1->height++;
    }
    return parent1;
}