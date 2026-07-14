#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "../libft/libft.h"

# include "stack.h"
# include "bench.h"
# include "operations.h"
# include "algorithms.h"

// Utils propias (no disponibles en libft)
long		ft_atol(const char *str);

// Parsing
t_stack		*parse_args(int argc, char **argv, int *arg_start);

// Disorder
double		compute_disorder(t_stack *a);

// Bench
void		print_bench(t_bench *bench);

// Flags de estrategia
# define FLAG_NONE		0
# define FLAG_SIMPLE	1
# define FLAG_MEDIUM	2
# define FLAG_COMPLEX	3
# define FLAG_ADAPTIVE	4

#endif
