#define _CRT_SECURE_NO_WARNINGS
#include "Stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Control.h"
int list_size = 20;
 int pop_index = -1;
int lier_index;
char** create_stack()
{
	char** ptr = (char**)malloc(sizeof(char*) * list_size);
	if (!ptr)
	{
		fprintf(stderr, "not enough heap");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < list_size; i++)
		ptr[i] = create_element();

	return ptr;
}
char* create_element()
{
	char* ptr = (char*)malloc(sizeof(char) * 20);

	if (!ptr)
	{
		fprintf(stderr, "not enough heap");
		exit(EXIT_FAILURE);
	}
	return ptr;
}
void print_stack(const char** stack, const char* oper)
{
	int i = 0;
	while (i <= pop_max)
	{
		printf("%s ", stack[i++]);
		if(*oper)
		printf("%c ", *oper++);
	}
}
void push(char** stack, char* element)
{
	if(is_full())
	{
		fprintf(stderr, "stack is full");
		exit(EXIT_FAILURE);
	}
	
	
	if(element)
	strcpy(stack[++pop_index], element);
	 pop_max = pop_index;

	if(!format_control(peek(stack)))
	{
		fprintf(stderr, "wrong format");
		exit(EXIT_FAILURE);
	}
}
char* pop(char** stack)
{
	if(is_empty())
	{
		pop_index = pop_max;
		//fprintf(stderr, "stack is already empty");
	}
	return stack[pop_index--];

}
char* peek(char** stack)
{
	if(!is_empty())
	return stack[pop_index];

	fprintf(stderr, "stack is already empty");
	exit(EXIT_FAILURE);
}

int is_full()
{
	if (pop_index == list_size)
		return 1;
	return 0;
}
int is_empty()
{
	if (pop_index == -1)
		return 1;
	return 0;
}
int stack_size(char** stack)
{
	return pop_index + 1;
}
void clear(char** stack)
{
	int i = -1;
	while (i != pop_index)
		free(stack[pop_index--]);
	free(stack);
}