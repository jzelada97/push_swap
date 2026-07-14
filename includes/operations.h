#ifndef OPERATIONS_H
# define OPERATIONS_H

# include "bench.h"
# include "stack.h"

// Operaciones nombradas (imprimen a stdout, actualizan t_ops_count)

int	sa(t_stack *a, t_ops_count *ops);
int	sb(t_stack *b, t_ops_count *ops);
int	ss(t_stack *a, t_stack *b, t_ops_count *ops);

int	pa(t_stack *a, t_stack *b, t_ops_count *ops);
int	pb(t_stack *a, t_stack *b, t_ops_count *ops);

int	ra(t_stack *a, t_ops_count *ops);
int	rb(t_stack *b, t_ops_count *ops);
int	rr(t_stack *a, t_stack *b, t_ops_count *ops);

int	rra(t_stack *a, t_ops_count *ops);
int	rrb(t_stack *b, t_ops_count *ops);
int	rrr(t_stack *a, t_stack *b, t_ops_count *ops);

#endif
