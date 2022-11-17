/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 22:58:23 by suhkim            #+#    #+#             */
/*   Updated: 2022/11/18 03:45:38 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	init_stack(t_stack *stack)
{
	stack->head.next = &stack->tail;
	stack->tail.prev = &stack->head;
	stack->size = 0;
	return (1);
}

int	init_info(t_info *info)
{
	info->env_stack = malloc(sizeof(t_stack));
	if (!info->env_stack)
		return (0);
	init_stack(info->env_stack);
	return (1);
}
