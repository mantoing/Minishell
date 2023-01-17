/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_front_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 19:29:48 by suhkim            #+#    #+#             */
/*   Updated: 2023/01/18 06:41:41 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static void	push_front_first(t_stack *stack, t_node *new_node)
{
	new_node->next = &stack->tail;
	stack->head.next = new_node;
	new_node->prev = &stack->head;
	stack->tail.prev = new_node;
}

static void	push_front_common(t_stack *stack, t_node *new_node)
{
	new_node->next = stack->head.next;
	stack->head.next->prev = new_node;
	new_node->prev = &stack->head;
	stack->head.next = new_node;
}

int	push_front_env(t_stack *stack, char *name, char *value)
{
	t_node	*new_node;

	if (!stack)
		return (0);
	new_node = malloc(sizeof(t_stack));
	if (!new_node)
		exit(1);
	new_node->env_name = name;
	new_node->env_value = value;
	if (stack->head.next == &stack->tail)
		push_front_first(stack, new_node);
	else
		push_front_common(stack, new_node);
	stack->size += 1;
	return (1);
}
