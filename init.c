/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 22:58:23 by suhkim            #+#    #+#             */
/*   Updated: 2023/01/19 22:34:01 by suhkim           ###   ########.fr       */
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
		exit(1);
	info->input = malloc(sizeof(t_input));
	if (!info->input)
		exit(1);
	info->unlink = malloc(sizeof(t_unlink));
	if (!info->unlink)
		exit(1);
	init_stack(info->env_stack);
	init_input(info->input);
	init_unlink(info->unlink);
	info->exit_code = 0;
	info->pipe_cnt = 0;
	info->quote = 0;
	return (1);
}

void	init_main(int argc, char **argv, char **env, t_info *info)
{
	if (argc != 1)
	{
		info->exit_code = print_err_with_exit_num(argv[1], \
				"No such file or directory", NULL, 127);
		exit(info->exit_code);
	}
	init_info(info);
	set_terminal_not_echo();
	set_signal("SHELL");
	save_env(env, info);
}
