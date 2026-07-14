/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_complex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzelada- <jzelada-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 16:19:14 by jzelada-          #+#    #+#             */
/*   Updated: 2026/07/04 16:22:44 by jzelada-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_max_index(t_stack *stack)
{
	t_node	*current;
	int		max;

	if (!stack || !stack->head)
		return (0);
	current = stack->head;
	max = current->index;
	while (current)
	{
		if (current->index > max)
			max = current->index;
		current = current->next;
	}
	return (max);
}

static int	get_max_bits(t_stack *stack)
{
	int	max;
	int	bits;

	max = get_max_index(stack);
	bits = 0;
	while ((max >> bits) != 0)
		bits++;
	return (bits);
}

static int	radix_bit_pass(t_stack *a, t_stack *b, int bit, t_ops_count *ops)
{
	int	count;
	int	size;
	int	i;

	count = 0;
	size = a->size;
	i = 0;
	while (i < size)
	{
		if (((a->head->index >> bit) & 1) == 1)
			count += ra(a, ops);
		else
			count += pb(a, b, ops);
		i++;
	}
	while (b->size > 0)
		count += pa(a, b, ops);
	return (count);
}

int	sort_complex(t_stack *a, t_stack *b, t_ops_count *ops)
{
	int	count;
	int	bits;
	int	bit;

	if (!a || !b || is_sorted(a))
		return (0);
	if (a->size <= 5)
		return (sort_simple(a, b, ops));
	count = 0;
	bits = get_max_bits(a);
	bit = 0;
	while (bit < bits)
	{
		count += radix_bit_pass(a, b, bit, ops);
		bit++;
	}
	return (count);
}
