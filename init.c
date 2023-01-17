/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 22:58:23 by suhkim            #+#    #+#             */
/*   Updated: 2023/01/18 06:18:57 by suhkim           ###   ########.fr       */
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
	init_input_edge(input);
	input->token_size = 0;
	return (1);
}

int	init_unlink(t_unlink *unlink)
{
	unlink->head.next = &unlink->tail;
	unlink->tail.prev = &unlink->head;
	unlink->temp_file_cnt = 0;
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
	info->unlink = malloc(sizeof(t_unlink));
	init_stack(info->env_stack);
	init_input(info->input);
	init_unlink(info->unlink);
	info->exit_code = 0;
	info->pipe_cnt = 0;
	return (1);
}

void	init_terminal(void)
{
	set_terminal_not_echo();
}
