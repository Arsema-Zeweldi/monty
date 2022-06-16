#include "monty.h"

/**
 * push - adds to a stack
 * @stack: pointer to the first node
 * @line_number: the line in the stack
 * Return: void
 */
void push_op(stack_t **stack, __attribute__((unused))unsigned int line_number)
{
	stack_t *new;

	if (stack == NULL || *stack == NULL)
		exit(EXIT_FAILURE);
	if (head == NULL)
	{
		head = *stack;
		return;
	}
	new = head;
	head = *stack;
	head->next = new;
	new->prev = head;
}
/**
 * pall - prints the whole stack
 * @stack: pointer to node
 * @line_number: line number
 * Return: void
 */
void pall_op(stack_t **stack, unsigned int line_number)
{
	stack_t *new;

	(void) line_number;
	if (stack == NULL)
		exit(EXIT_FAILURE);
	new = *stack;
	while (new != NULL)
	{
		printf("%d\n", new->n);
		new = new->next;
	}
}
/**
 * pint - prints to top
 * @stack: pointer to the first node
 * @line_number: line number
 * Return: void
 */
void pint_op(stack_t **stack, unsigned int line_number)
{
	if (stack == NULL || *stack == NULL)
		monty_error(6, line_number);
	printf("%d\n", (*stack)->n);
}
/**
 * pop - removes the tops elements
 * @stack: pointer to the first node
 * @line_number: line number
 * Return: void
 */
void pop_op(stack_t **stack, unsigned int line_number)
{
	stack_t *new;

	if (stack == NULL || *stack == NULL)
		monty_error(7, line_number);

	new = *stack;
	*stack = new->next;
	if (*stack != NULL)
		(*stack)->prev = NULL;
	free(new);
}
