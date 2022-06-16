#include "monty.h"

/**
 * open - opens a file
 * @file: file to open
 * Return: void
 */
void open(char *file)
{
	FILE *n = fopen(file, "r");

	if (file == NULL || n == NULL)
		monty_error(2, file);

	read_(n);
	fclose(n);
}

/**
 * read - reads a file
 * @n: pointer to file
 * Return: void
 */
void read_(FILE *n)
{
	int line_number, format = 0;
	char *buffer = NULL;
	size_t len = 0;

	for (line_number = 1; getline(&buffer, &len, n) != -1; line_number++)
	{
		format = parse_line(buffer, line_number, format);
	}
	free(buffer);
}

/**
 * parse_line - separates lines
 * @buffer: line
 * @line_number: line number
 * @format: storage format
 * Return: int
 */
int parse_line(char *buffer, int line_number, int format)
{
	char *opcode, *value;
	const char *delim = "\n";

	if (buffer == NULL)
		monty_error(4);

	opcode = strtok(buffer, delim);
	if (opcode == NULL)
		return (format);
	value = strtok(NULL, delim);

	if (strcmp(opcode, "stack") == 0)
		return (0);
	if (strcmp(opcode, "queue") == 0)
		return (1);

	find_func(opcode, value, line_number, format);
	return (format);
}

/**
 * find_func - finds functions
 * @opcode: opcode
 * @value: argument
 * @format: storage format
 * @line_number: line number
 * Return: void
 */
void find_func(char *opcode, char *value, int line_number, int format)
{
	int c;
	int d;

	instruction_t func_list[] = {
		{"push", push_op},
		{"pall", pall_op},
		{"pint", pint_op},
		{"pop", pop_op},
		{NULL, NULL}
	};

	if (opcode[0] == '#')
		return;

	for (d = 1, c = 0; func_list[c].opcode != NULL; c++)
	{
		if (strcmp(opcode, func_list[c].opcode) == 0)
		{
			call_fun(func_list[c].f, opcode, value, line_number, format);
			d = 0;
		}
	}
	if (d == 1)
		monty_error(3, line_number, opcode);
}

/**
 * call_fun - calls the functions
 * @func: pointer to function
 * @op: opcode
 * @value: value
 * @line_number: line number
 * @format: storage format
 * Return: void
 */
void call_fun(op_func func, char *op, char *value, int line_number, int format)
{
	stack_t *node;
	int d;
	int c;

	d = 1;
	if (strcmp(op, "push") == 0)
	{
		if (value != NULL && value[0] == '-')
		{
			value = value + 1;
			d = -1;
		}
		if (value == NULL)
			monty_error(5, line_number);
		for (c = 0; value[c] != '\0'; c++)
		{
			if (isdigit(value[c]) == 0)
				monty_error(5, line_number);
		}
		node = create_node(atoi(value) *d);
		if (format == 0)
			func(&node, line_number);
		if (format == 1)
			add_to_queue(&node, line_number);
	}
	else
		func(&head, line_number);
}
