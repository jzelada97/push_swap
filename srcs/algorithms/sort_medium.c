/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_medium.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzelada- <jzelada-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 16:19:29 by jzelada-          #+#    #+#             */
/*   Updated: 2026/07/04 16:22:55 by jzelada-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_medium_range(int size)
{
	int	root;
	int	range;

	root = 1;
	while (root * root < size)
		root++;
	range = root * 14 / 10;
	if (range < 2)
		range = 2;
	return (range);
}

static int	push_chunks_to_b(t_stack *a, t_stack *b, int range,
		t_ops_count *ops)
{
	int	count;
	int	pushed;

	count = 0;
	pushed = 0;
	while (a->size > 0)
	{
		if (a->head->index <= pushed)
		{
			count += pb(a, b, ops);
			count += rb(b, ops);
			pushed++;
		}
		else if (a->head->index <= pushed + range)
		{
			count += pb(a, b, ops);
			pushed++;
		}
		else
			count += ra(a, ops);
	}
	return (count);
}

static int	get_max_position(t_stack *stack)
{
	t_node	*current;
	int		max_index;
	int		max_pos;
	int		pos;

	current = stack->head;
	max_index = current->index;
	max_pos = 0;
	pos = 0;
	while (current)
	{
		if (current->index > max_index)
		{
			max_index = current->index;
			max_pos = pos;
		}
		current = current->next;
		pos++;
	}
	return (max_pos);
}

static int	move_max_to_top(t_stack *b, t_ops_count *ops)
{
	int	count;
	int	pos;

	count = 0;
	pos = get_max_position(b);
	if (pos <= b->size / 2)
	{
		while (pos-- > 0)
			count += rb(b, ops);
	}
	else
	{
		while (pos++ < b->size)
			count += rrb(b, ops);
	}
	return (count);
}

int	sort_medium(t_stack *a, t_stack *b, t_ops_count *ops)
{
	int	count;
	int	range;

	if (!a || !b || is_sorted(a))
		return (0);
	if (a->size <= 5)
		return (sort_simple(a, b, ops));
	count = 0;
	range = get_medium_range(a->size);
	count += push_chunks_to_b(a, b, range, ops);
	while (b->size > 0)
	{
		count += move_max_to_top(b, ops);
		count += pa(a, b, ops);
	}
	return (count);
}
