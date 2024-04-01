#ifndef STAC_H
#define STAC_H
int pop_max;
int pop_index;
int lier_index;
int list_size;
int stack_size(char** stack);
char** create_stack();
char* create_element();
void push(char** stack, char* element);
char* pop(char** stack);
int is_full();
int is_empty();
void clear(char** stack);
void print_stack(const char** stack,const char* oper);
char* peek(char** stack);

















#endif
