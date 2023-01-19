/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 00:26:59 by suhkim            #+#    #+#             */
/*   Updated: 2023/01/19 22:02:35 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	check_closed_pipe(t_info *info)
{
	t_token	*temp;

	temp = info->input->head.next;
	while (temp != &info->input->tail)
	{
		if (temp->pipe && temp->next->pipe)
			return (2);
		temp = temp->next;
	}
	if (info->input->head.next->pipe)
		return (1);
	if (info->input->tail.prev->pipe)
		return (1);
	return (0);
}

static int	check_pipe(t_info *info)
{
	if (check_closed_pipe(info) == 1)
	{
		info->exit_code = print_err_with_exit_num(\
				"syntax error near unexpected token '|'", NULL, NULL, 258);
		g_signal = 0;
		return (0);
	}
	else if (check_closed_pipe(info) == 2)
	{
		info->exit_code = print_err_with_exit_num(\
				"syntax error near unexpected token '||'", \
				NULL, NULL, 258);
		g_signal = 0;
		return (0);
	}
	return (1);
}

int	parse(t_info *info, char *line)
{
	int		len;

	len = 0;
	while (*(line))
	{
		len = split_token(info, line);
		if (len < 0)
		{
			if (len == -2)
				return (0);
			info->exit_code = print_err_with_exit_num(\
					"syntax error near unexpected token quotes"\
					, NULL, NULL, 258);
			g_signal = 0;
			return (0);
		}
		if (!len)
			line++;
		else
			line += len;
	}
	if (!check_pipe(info))
		return (0);
	return (1);
}
