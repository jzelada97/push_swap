#ifndef STACK_H
# define STACK_H

typedef struct s_node
{
	int				value;
	int				index;
	struct s_node	*prev;
	struct s_node	*next;
}					t_node;

typedef struct s_stack
{
	t_node			*head;
	t_node			*tail;
	int				size;
}					t_stack;

t_stack				*create_stack(void);
t_node				*create_node(int value);
void				free_stack(t_stack *stack);
int					assign_indexes(t_stack *stack);

#endif
