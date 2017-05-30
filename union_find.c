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
node* union_(node* element1; node* element2);

int main()
{

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
	element->parent = element;
	element->height = 1;
	return element;
}

node* find(node* element)
{
	if(element->parent == x)
		return x;
	else
		return find(element->parent);
}

node* union_(node* element1; node* element2)
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