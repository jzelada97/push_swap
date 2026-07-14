/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzelada- <jzelada-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 16:20:46 by jzelada-          #+#    #+#             */
/*   Updated: 2026/07/04 16:23:04 by jzelada-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	sort_selection(t_stack *a, t_stack *b, t_ops_count *ops)
{
	int	count;

	count = 0;
	while (a->size > 1)
	{
		count += simple_move_min_to_top(a, ops);
		count += pb(a, b, ops);
	}
	while (b->size > 0)
		count += pa(a, b, ops);
	return (count);
}

int	sort_simple(t_stack *a, t_stack *b, t_ops_count *ops)
{
	if (!a || !b || is_sorted(a))
		return (0);
	if (a->size == 2)
		return (simple_sort_two(a, ops));
	if (a->size == 3)
		return (simple_sort_three(a, ops));
	if (a->size <= 5)
		return (simple_sort_five(a, b, ops));
	return (sort_selection(a, b, ops));
}
