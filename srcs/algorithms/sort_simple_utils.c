/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_simple_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzelada- <jzelada-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 16:20:23 by jzelada-          #+#    #+#             */
/*   Updated: 2026/07/04 16:23:02 by jzelada-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_sorted(t_stack *stack)
{
	t_node	*current;

	if (!stack || stack->size < 2)
		return (1);
	current = stack->head;
	while (current && current->next)
	{
		if (current->value > current->next->value)
			return (0);
		current = current->next;
	}
	return (1);
}

static int	get_min_position(t_stack *stack)
{
	t_node	*current;
	int		min_value;
	int		min_pos;
	int		pos;

	if (!stack || stack->size == 0)
		return (-1);
	current = stack->head;
	min_value = current->value;
	min_pos = 0;
	pos = 0;
	while (current)
	{
		if (current->value < min_value)
		{
			min_value = current->value;
			min_pos = pos;
		}
		current = current->next;
		pos++;
	}
	return (min_pos);
}

static int	rotate_position_to_top(t_stack *a, int pos, t_ops_count *ops)
{
	int	count;

	count = 0;
	if (pos <= a->size / 2)
	{
		while (pos-- > 0)
			count += ra(a, ops);
	}
	else
	{
		while (pos++ < a->size)
			count += rra(a, ops);
	}
	return (count);
}

int	simple_move_min_to_top(t_stack *a, t_ops_count *ops)
{
	int	pos;

	pos = get_min_position(a);
	if (pos == -1)
		return (0);
	return (rotate_position_to_top(a, pos, ops));
}
