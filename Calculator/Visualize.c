#define _CRT_SECURE_NO_WARNINGS
#include "Visualize.h"
#include"Stack.h"
#include"Control.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
char temp[50];
int fact(int x)
{
	int sum = 1;
	if (x == 1 || x == 0)
		return 1;
	for (int i = 1; i <= x; i++)
	{
		sum *= i;
	}
	return sum;
}
void visual_stack(char** str)
{
	for (int i = 0; i <= pop_index; i++)
	{
		if (strlen(*str) >= 2 && isnum(*str))
		{
			char* temp = *str;
			char temp_str[20] = "";
			int i = 0;
			int a = 0;
			temp_str[i] = '(';

			while (**str)
			{
				temp_str[++i] = (**str); 
				temp_str[++i] = '*';
				(*str)++;
				
			}
			temp_str[i] = ')';
			temp_str[++i] = '\0';
			*str = temp;
			strcpy(*str, temp_str);
		}
		++str;
	}
}

char* str_rev(char* str)
{
	int length = strlen(str);
	int start = 0;
	int end = length - 1;

	while (start < end) {
		char temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
	return str;
}

char* cpy_str(char** str, char* oper) {
	int i = 0;
	char* arr = (char*)malloc(sizeof(char) * 50);
	strcpy(arr, " ");
	char* temp = oper;
	while (i <= pop_max)
	{
		strcat(arr, str[i++]);
		if (*oper)
		{
			strncat(arr, oper++, 1);
		}
	}
	oper = temp;
	//printf("%s", arr);
	printf("is = ");
		find_values(arr, oper);
}
void find_values(char* str, char* oper)
{
	str++;
	while (*str)
	{
			
		if (*str == 'e')
		{
			strcat(temp, "2.71");
			strncat(temp, oper++, 1);
		}
		else if (*str == 'p' && *(str + 1) == 'i')
		{
			strcat(temp, "3.1415");
			strncat(temp, oper++, 1);
			str++;
		}
		else if (*str == 'c' && *(str + 1) == 'o' && *(str + 2) == 's')
		{
			if (*oper == '/')
				oper++;
			while (!isdigit(*str))
			{
				str++;
			}
			int a = atoi(str);
			double dval = 180. / a;
			char temp_1[10];
			snprintf(temp_1, 10, "%lf", cos(dval * 3.1415 / 180));
			strcat(temp, temp_1);
			strncat(temp, oper++, 1);
			
		}
		else if (*str == 's' && *(str + 1) == 'i' && *(str + 2) == 'n')
		{
			if (*oper == '/')
			oper++;
			while (!isdigit(*str))
			{
				str++;
			}
			int a = atoi(str);
			double dval = 180. / a;
			char temp_1[10];
			snprintf(temp_1, 10, "%lf", sin(dval * 3.1415 / 180));
			strcat(temp, temp_1);
			strncat(temp, oper++, 1);
		}
		else if (*str == 't' && *(str + 1) == 'a' && *(str + 2) == 'n')
		{
			if (*oper == '/')
				oper++;
			while (!isdigit(*str))
			{
				str++;
			}
			int a = atoi(str);
			double dval = 180. / a;
			char temp_1[10];
			snprintf(temp_1, 10, "%lf", tan(dval * 3.1415 / 180));
			strcat(temp, temp_1);
			strncat(temp, oper++, 1);
		}
		else if (*str == 'c' && *(str + 1) == 'o' && *(str + 2) == 't')
		{
			if (*oper == '/')
				oper++;
			while (!isdigit(*str))
			{
				str++;
			}
			int a = atoi(str);
			double dval = 180. / a;
			char temp_1[10];
			snprintf(temp_1, 10, "%lf", 1 / tan(dval * 3.1415 / 180));
			strcat(temp, temp_1);
			strncat(temp, oper++, 1);
		}
		else if (*str == '(')
		{
			int sum = 1;
			str++;
				char temp_1[10];
			while (*str != ')')
			{
				if (isdigit(*str))
				{
					sum *= atoi(str);
				}
				str++;
			}
				snprintf(temp_1, 10, "%d", sum);
			strcat(temp, temp_1);
			strncat(temp, oper++, 1);
		}
		else if (isdigit(*str))
		{
			strncat(temp, str,1);
			strncat(temp, oper++, 1);
		}
		str++;
	}
	printf("(%s)", temp);
	printf("[%s]", final_answer_minus(final_answer_plus(final_answer_mod(final_answer_divide(final_answer_star((temp)))))));
}