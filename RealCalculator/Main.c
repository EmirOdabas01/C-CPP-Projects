#define _CRT_SECURE_NO_WARNINGS
#include "Stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include"Visualize.h"
#define asize(x)	(strlen(x))
int main()
{
	char** arrey_list = create_stack();
	
	
	char array[100];
	char oper[20] = "";

	printf("enter a string\n");
	scanf(" %[^\n]s", array);
	int x = asize(array);
	array[x] = '\0';
	int operator_count = 0;
	int j = 0;
	for (unsigned i = 0; i < strlen(array); i++)
	{
		if (ispunct(array[i]) && array[i] != '(' && array[i] != ')' && array[i] != '!')
		{
			oper[j++] = array[i];
				++operator_count;
				if (array[i] == '^' || array[i] == '!')
					--operator_count;
		}
	}
	oper[j] = '\0';



	 char delim[] = " +*-/%";
	 push(arrey_list, strtok(array, delim));
	 
		while (!is_full() && lier_index++ != list_size)
			 push(arrey_list, strtok(NULL, delim));
			 
		if (operator_count >= stack_size(arrey_list))
		{
			fprintf(stderr, "The number of operators and operands is not compatible");
			exit(EXIT_FAILURE);
		}
		print_stack(arrey_list, oper);
		printf("is = ");
		visual_stack(arrey_list);
		print_stack(arrey_list, oper);
		cpy_str(arrey_list, oper);
		


}