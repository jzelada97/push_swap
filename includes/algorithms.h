#ifndef ALGORITHMS_H
# define ALGORITHMS_H

# include "stack.h"
# include "bench.h"

int	is_sorted(t_stack *stack);

int	sort_simple(t_stack *a, t_stack *b, t_ops_count *ops);
int	sort_medium(t_stack *a, t_stack *b, t_ops_count *ops);
int	sort_complex(t_stack *a, t_stack *b, t_ops_count *ops);
int	sort_adaptive(t_stack *a, t_stack *b, t_bench *bench);

int	simple_sort_two(t_stack *a, t_ops_count *ops);
int	simple_sort_three(t_stack *a, t_ops_count *ops);
int	simple_sort_five(t_stack *a, t_stack *b, t_ops_count *ops);
int	simple_move_min_to_top(t_stack *a, t_ops_count *ops);

#endif
