/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_back_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 22:17:19 by suhkim            #+#    #+#             */
/*   Updated: 2023/01/18 06:41:57 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static void	push_back_first(t_stack *stack, t_node *new_node)
{
	new_node->prev = &stack->head;
	new_node->next = &stack->tail;
	stack->head.next = new_node;
	stack->tail.prev = new_node;
}

static void	push_back_common(t_stack *stack, t_node *new_node)
{
	new_node->prev = stack->tail.prev;
	new_node->next = &stack->tail;
	stack->tail.prev->next = new_node;
	stack->tail.prev = new_node;
}

int	push_back_env(t_stack *stack, char *name, char *value)
{
	t_node	*new_node;

	if (!stack)
		return (0);
	new_node = malloc(sizeof(t_node));
	if (!new_node)
		exit(1);
	new_node->env_name = name;
	new_node->env_value = value;
	if (stack->tail.prev == &stack->head)
		push_back_first(stack, new_node);
	else
		push_back_common(stack, new_node);
	stack->size += 1;
	return (1);
}
