/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 22:58:23 by suhkim            #+#    #+#             */
/*   Updated: 2022/11/24 22:35:57 by suhkim           ###   ########.fr       */
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

int	init_input(t_input *input)
{
	input->head.next = &input->tail;
	input->tail.prev = &input->head;
	input->token_size = 0;
	return (1);
}

int	init_info(t_info *info)
{
	info->env_stack = malloc(sizeof(t_stack));
	if (!info->env_stack)
		return (0);
	info->input = malloc(sizeof(t_input));
	if (!info->input)
		return (0);
	init_stack(info->env_stack);
	init_input(info->input);
	info->pipe_cnt = 0;
	return (1);
}
