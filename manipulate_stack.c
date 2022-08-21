#include "monty.h"
/**
 * check_for_digit - checks that a string only contains digits.
 * @arg: string to check.
 *
 * Return: 0 if only digits, else 1
 */
static int check_for_digit(char *arg)
{
	int i;

	for (i = 0; arg[i]; i++)
	{
		if (arg[i] == '-' && i == 0)
			continue;
		if (isdigit(arg[i]) == 0)
			return (1);
	}
	return (0);
}

/**
 * _push - push an integer onto the stack.
 * @stack: double pointer to the beginning of the stack.
 * @line_number: script line number.
 *
 * Return: void
 */
void _push(stack_t **stack, unsigned int line_number)
{
	char *arg;
	int n;

	arg = strtok(NULL, "\n\t\r ");
	if (arg == NULL || check_for_digit(arg))
	{
		fprintf(stderr,
			"L%u: usage: push integer\n",
			line_number);
		if (*stack != NULL)
		{
			free_stack(*stack);
		}
		free(var.gline);
		fclose(var.gfs);
		exit(EXIT_FAILURE);
	}
	n = atoi(arg);
	if (!add_node_end(stack, n))
	{
		fprintf(stderr, "Error: malloc failed\n");
		if (*stack != NULL)
		{
			free_stack(*stack);
		}
		free(var.gline);
		fclose(var.gfs);
		exit(EXIT_FAILURE);
	}
	var.stack_len++;
}

/**
 * print_stack_t - Print the stack from top to bottom.
 * @head: Head of the stack.
 */

void print_stack_t(stack_t *head)
{
	size_t i;
	stack_t *ptr;

	if (head == NULL)
		return;
	ptr = head;
	while (ptr->next != NULL)
		ptr = ptr->next;
	for (i = 0; ptr; i++)
	{
		printf("%d\n", ptr->n);
		ptr = ptr->prev;
	}
}

/**
 * _pall - Prints stack elements.
 * @stack: Head of the stack.
 * @line_number: Read file line.
 */

void _pall(stack_t **stack, unsigned int line_number __attribute__((unused)))
{
	stack_t *print_all;

	print_all = *stack;
	print_stack_t(print_all);
}

/**
 * _pint - Print the value at the top of the stack.
 * @stack: Head of the stack.
 * @line_number: Read file line.
 */

void _pint(stack_t **stack, unsigned int line_number)
{
	stack_t *ptr;

	ptr = *stack;
	if ((*stack) == NULL)
	{
		fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
		free(var.gline);
		fclose(var.gfs);
		exit(EXIT_FAILURE);
	}

	while (ptr->next != NULL)
		ptr = ptr->next;

	printf("%d\n", ptr->n);
}
