/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_simple_small.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzelada- <jzelada-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 16:19:59 by jzelada-          #+#    #+#             */
/*   Updated: 2026/07/04 16:23:00 by jzelada-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	simple_sort_two(t_stack *a, t_ops_count *ops)
{
	if (a->head->value > a->head->next->value)
		return (sa(a, ops));
	return (0);
}

int	simple_sort_three(t_stack *a, t_ops_count *ops)
{
	int	count;
	int	first;
	int	second;
	int	third;

	count = 0;
	first = a->head->value;
	second = a->head->next->value;
	third = a->head->next->next->value;
	if (first > second && first > third)
		count += ra(a, ops);
	else if (second > first && second > third)
		count += rra(a, ops);
	if (a->head->value > a->head->next->value)
		count += sa(a, ops);
	return (count);
}

int	simple_sort_five(t_stack *a, t_stack *b, t_ops_count *ops)
{
	int	count;

	count = 0;
	while (a->size > 3)
	{
		count += simple_move_min_to_top(a, ops);
		count += pb(a, b, ops);
	}
	count += simple_sort_three(a, ops);
	while (b->size > 0)
		count += pa(a, b, ops);
	return (count);
}
