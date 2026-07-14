/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_adaptive.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzelada- <jzelada-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 16:16:42 by jzelada-          #+#    #+#             */
/*   Updated: 2026/07/04 16:22:50 by jzelada-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	is_rotated_sorted(t_stack *a)
{
	t_node	*current;
	int		drops;

	if (!a || a->size < 2)
		return (1);
	drops = 0;
	current = a->head;
	while (current && current->next)
	{
		if (current->index > current->next->index)
			drops++;
		current = current->next;
	}
	if (a->tail->index > a->head->index)
		drops++;
	return (drops <= 1);
}

static int	low_bubble_pass(t_stack *a, t_ops_count *ops, int *swaps)
{
	int	count;
	int	i;
	int	size;

	count = 0;
	i = 0;
	size = a->size;
	*swaps = 0;
	count += simple_move_min_to_top(a, ops);
	while (i < size - 1)
	{
		if (a->head->index > a->head->next->index)
		{
			count += sa(a, ops);
			(*swaps)++;
		}
		count += ra(a, ops);
		i++;
	}
	count += simple_move_min_to_top(a, ops);
	return (count);
}

static int	sort_low_disorder(t_stack *a, t_ops_count *ops)
{
	int	count;
	int	swaps;
	int	limit;

	count = 0;
	if (is_rotated_sorted(a))
		return (simple_move_min_to_top(a, ops));
	limit = a->size;
	while (!is_sorted(a) && limit > 0)
	{
		count += low_bubble_pass(a, ops, &swaps);
		if (swaps == 0)
			break ;
		limit--;
	}
	return (count);
}

static void	set_adaptive_bench(t_bench *bench, char *name, char *complexity)
{
	bench->strategy_name = name;
	bench->complexity = complexity;
}

int	sort_adaptive(t_stack *a, t_stack *b, t_bench *bench)
{
	if (!a || !b || !bench)
		return (0);
	set_adaptive_bench(bench, "adaptive-sorted", "O(1)");
	if (is_sorted(a))
		return (0);
	if (a->size <= 5)
	{
		set_adaptive_bench(bench, "adaptive-simple", "O(n^2)");
		return (sort_simple(a, b, &bench->ops));
	}
	if (bench->disorder < 20.0)
	{
		set_adaptive_bench(bench, "adaptive-low", "O(n)");
		return (sort_low_disorder(a, &bench->ops));
	}
	if (bench->disorder < 50.0)
	{
		set_adaptive_bench(bench, "adaptive-medium", "O(n*sqrt(n))");
		return (sort_medium(a, b, &bench->ops));
	}
	set_adaptive_bench(bench, "adaptive-complex", "O(n*log(n))");
	return (sort_complex(a, b, &bench->ops));
}
