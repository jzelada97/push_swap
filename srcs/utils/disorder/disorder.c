#include "push_swap.h"

/*
** Calcula el índice de desorden como porcentaje (0.0 a 100.0).
** Por cada par (i, j) con i < j, cuenta un error si a[i] > a[j].
** Devuelve (mistakes / total_pairs) * 100.
** Si hay 0 o 1 elementos, el desorden es 0.
*/
double	compute_disorder(t_stack *a)
{
	t_node	*i;
	t_node	*j;
	double	mistakes;
	double	total_pairs;

	if (!a || a->size < 2)
		return (0.0);
	mistakes = 0.0;
	total_pairs = 0.0;
	i = a->head;
	while (i && i->next)
	{
		j = i->next;
		while (j)
		{
			total_pairs += 1.0;
			if (i->value > j->value)
				mistakes += 1.0;
			j = j->next;
		}
		i = i->next;
	}
	return ((mistakes / total_pairs) * 100.0);
}
