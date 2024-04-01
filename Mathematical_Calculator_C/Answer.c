#define _CRT_SECURE_NO_WARNINGS
#include "Answer.h"
char* final_answer_star(char* ptr)
{
	char temp_4[300] = "";
	
	if (!strpbrk(ptr, "*"))
	{
		char* pttr = malloc(100);
		strcpy(pttr, ptr);
		return ptr;
	}

	char* index = strpbrk(ptr, "*");
	int numsize = index - ptr;
	char* holder = index;
	int fiststr = numsize;
	index--;
	char temp_1[15];
	int i = 0;
	while (*index != '-' && *index != '/' && *index != '+' && *index != '%' && *index != '*' && numsize >= 1)
	{
		temp_1[i++] = *index--;
		numsize--;
	}
	temp_1[i] = '\0';
	_strrev(temp_1);

	char temp_2[15];

	index = holder;
	index++;
	i = 0;
	while (*index != '-' && *index != '/' && *index != '+' && *index != '%' && *index != '*' && *index != '\0')
	{
		temp_2[i++] = *index++;
	}
	temp_2[i] = '\0';
	double num_1 = atof(temp_1);
	double num_2 = atof(temp_2);
	char temp_5[15];
	strcpy(temp_5, index);
	num_1 *= num_2;
	char temp_3[15];

	snprintf(temp_3, 9, "%.2f", num_1);

	strcpy(ptr + numsize, temp_3);
	strcat(ptr, temp_5);
	ptr[strlen(ptr)] = '\0';
	return final_answer_star(ptr);
}
char* final_answer_divide(char* ptr)
{
	char temp_4[300] = "";
	
	if (!strpbrk(ptr, "/"))
	{
		char* pttr = malloc(100);
		strcpy(pttr, ptr);
		return ptr;
	}

	char* index = strpbrk(ptr, "/");
	int numsize = index - ptr;
	char* holder = index;
	int fiststr = numsize;
	index--;
	char temp_1[15];
	int i = 0;
	while (*index != '-' && *index != '/' && *index != '+' && *index != '%' && *index != '*' && numsize >= 1)
	{
		temp_1[i++] = *index--;
		numsize--;
	}
	temp_1[i] = '\0';
	_strrev(temp_1);

	char temp_2[15];

	index = holder;
	index++;
	i = 0;
	while (*index != '-' && *index != '/' && *index != '+' && *index != '%' && *index != '*' && *index != '\0')
	{
		temp_2[i++] = *index++;
	}
	temp_2[i] = '\0';
	double num_1 = atof(temp_1);
	double num_2 = atof(temp_2);
	char temp_5[15];
	strcpy(temp_5, index);
	num_1 /= num_2;
	char temp_3[15];

	snprintf(temp_3, 9, "%.2f", num_1);

	strcpy(ptr + numsize, temp_3);
	strcat(ptr, temp_5);
	ptr[strlen(ptr)] = '\0';
	return final_answer_divide(ptr);
}
char* final_answer_mod(char* ptr)
{
	char temp_4[300] = "";
	
	if (!strpbrk(ptr, "%"))
	{
		char* pttr = malloc(100);
		strcpy(pttr, ptr);
		return ptr;
	}

	char* index = strpbrk(ptr, "%");
	int numsize = index - ptr;
	char* holder = index;
	int fiststr = numsize;
	index--;
	char temp_1[15];
	int i = 0;
	while (*index != '-' && *index != '/' && *index != '+' && *index != '%' && *index != '*' && numsize >= 1)
	{
		temp_1[i++] = *index--;
		numsize--;
	}
	temp_1[i] = '\0';
	_strrev(temp_1);

	char temp_2[15];

	index = holder;
	index++;
	i = 0;
	while (*index != '-' && *index != '/' && *index != '+' && *index != '%' && *index != '*' && *index != '\0')
	{
		temp_2[i++] = *index++;
	}
	temp_2[i] = '\0';
	double num_1 = atof(temp_1);
	double num_2 = atof(temp_2);
	char temp_5[15];
	strcpy(temp_5, index);
	num_1 = (int)num_1 % (int)num_2;
	char temp_3[15];

	snprintf(temp_3, 9, "%.2f", num_1);

	strcpy(ptr + numsize, temp_3);
	strcat(ptr, temp_5);
	ptr[strlen(ptr)] = '\0';
	return final_answer_mod(ptr);
}
char* final_answer_plus(char* ptr)
{
	char temp_4[300] = "";

	if (!strpbrk(ptr, "+"))
	{
		char* pttr = malloc(100);
		strcpy(pttr, ptr);
		return ptr;
	}

	char* index = strpbrk(ptr, "+");
	int numsize = index - ptr;
	char* holder = index;
	int fiststr = numsize;
	index--;
	char temp_1[15];
	int i = 0;
	while (*index != '-' && *index != '/' && *index != '+' && *index != '%' && *index != '*' && numsize >= 1)
	{
		temp_1[i++] = *index--;
		numsize--;
	}
	temp_1[i] = '\0';
	_strrev(temp_1);

	char temp_2[15];

	index = holder;
	index++;
	i = 0;
	while (*index != '-' && *index != '/' && *index != '+' && *index != '%' && *index != '*' && *index != '\0')
	{
		temp_2[i++] = *index++;
	}
	temp_2[i] = '\0';
	double num_1 = atof(temp_1);
	double num_2 = atof(temp_2);
	char temp_5[15];
	strcpy(temp_5, index);
	num_1 += num_2;
	char temp_3[15];

	snprintf(temp_3, 9, "%.2f", num_1);

	strcpy(ptr + numsize, temp_3);
	strcat(ptr, temp_5);
	ptr[strlen(ptr)] = '\0';
	return final_answer_plus(ptr);
}
char* final_answer_minus(char* ptr)
{
	char temp_4[300] = "";

	if (!strpbrk(ptr, "-"))
	{
		char* pttr = malloc(100);
		strcpy(pttr, ptr);
		return ptr;
	}

	char* index = strpbrk(ptr, "-");
	int numsize = index - ptr;
	char* holder = index;
	int fiststr = numsize;
	index--;
	char temp_1[15];
	int i = 0;
	while (*index != '-' && *index != '/' && *index != '+' && *index != '%' && *index != '*' && numsize >= 1)
	{
		temp_1[i++] = *index--;
		numsize--;
	}
	temp_1[i] = '\0';
	_strrev(temp_1);

	char temp_2[15];

	index = holder;
	index++;
	i = 0;
	while (*index != '-' && *index != '/' && *index != '+' && *index != '%' && *index != '*' && *index != '\0')
	{
		temp_2[i++] = *index++;
	}
	temp_2[i] = '\0';
	double num_1 = atof(temp_1);
	double num_2 = atof(temp_2);
	char temp_5[15];
	strcpy(temp_5, index);
	num_1 -= num_2;
	char temp_3[15];

	snprintf(temp_3, 9, "%.2f", num_1);

	strcpy(ptr + numsize, temp_3);
	strcat(ptr, temp_5);
	ptr[strlen(ptr)] = '\0';
	return final_answer_minus(ptr);
}