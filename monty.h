#ifndef MONTY_H_
#define MONTY_H_

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <ctype.h>
/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
        int n;
        struct stack_s *prev;
        struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
        char *opcode;
        void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

extern stack_t *head;
typedef void (*op_func)(stack_t **, unsigned int);
/*monty.c*/
stack_t *create_node(int n);
void free_nodes(void);
void add_to_queue(stack_t **, unsigned int);

/*mandatory*/
void push_op(stack_t **, unsigned int);
void pall_op(stack_t **, unsigned int);
void pint_op(stack_t **, unsigned int);
void pop_op(stack_t **, unsigned int);
void swap_op(stack_t **, unsigned int);
void nop_op(stack_t **, unsigned int);

/*errors*/
void monty_error(int error_code, ...);
void string_error(int error_code, ...);

/*utils*/
void open(char *file);
void read_(FILE *);
int parse_line(char *buffer, int line_number, int format);
int len_chars(FILE *);
void find_func(char *, char *, int, int);
void call_fun(op_func, char*, char*, int, int);

#endif
