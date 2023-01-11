/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 05:35:00 by suhkim            #+#    #+#             */
/*   Updated: 2023/01/11 19:02:27 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	**check_redirection(t_info *info, t_token *pipe)
{
	int		i;
	int		arg_size;
	char	**arg;
	t_token	*target;

	target = get_first_arg(info, pipe);
	arg_size = get_arg_size(info, target, pipe);
	arg = malloc(sizeof(char *) * (arg_size + 1));
	if (!arg)
		return (0);
	conv_arg(target, arg, arg_size);
	i = 0;
	while (target != &info->input->tail && target != pipe)
	{
		if (target->redir_l || target->heredoc)
		{
			if (!redir_l(info, target))
			{
				free_arg(arg, arg_size);
				return (0);
			}
			target = target->next->next;
			arg[i][0] = 0;
			i++;
			arg[i][0] = 0;
		}
		else if (target->redir_r)
		{
			if (!redir_r(info, target))
			{
				free_arg(arg, arg_size);
				return (0);
			}
			target = target->next->next;
			arg[i][0] = 0;
			i++;
			arg[i][0] = 0;
		}
		else if (target->append)
		{
			if (!redir_append(info, target))
			{
				free_arg(arg, arg_size);
				return (0);
			}
			target = target->next->next;
			arg[i][0] = 0;
			i++;
			arg[i][0] = 0;
		}
		/*
		else if (target->heredoc)
		{
			if (!redir_heredoc(info, target))
			{
				free_arg(arg, arg_size);
				return (0);
			}
		}
		*/
		else
			target = target->next;
		i++;
	}
	arg = arrange_arg(arg, arg_size);
	//dprintf(2, "ret arg = %s\n", arg[0]);
	return (arg);
}
