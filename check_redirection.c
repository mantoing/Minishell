/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 05:35:00 by suhkim            #+#    #+#             */
/*   Updated: 2023/01/19 16:38:32 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	do_l_or_heredoc(t_info *info, t_token *target, char **arg, int *i)
{
	int	arg_size;

	arg_size = cal_arg_length(arg);
	if (!redir_l(info, target))
	{
		free_arg(arg, arg_size);
		return (0);
	}
	arg[*i][0] = 0;
	*i += 1;
	arg[*i][0] = 0;
	return (1);
}

int	do_r(t_info *info, t_token *target, char **arg, int *i)
{
	int	arg_size;

	arg_size = cal_arg_length(arg);
	if (!redir_r(info, target))
	{
		free_arg(arg, arg_size);
		return (0);
	}
	arg[*i][0] = 0;
	*i += 1;
	arg[*i][0] = 0;
	return (1);
}

int	do_append(t_info *info, t_token *target, char **arg, int *i)
{
	int	arg_size;

	arg_size = cal_arg_length(arg);
	if (!redir_append(info, target))
	{
		free_arg(arg, arg_size);
		return (0);
	}
	arg[*i][0] = 0;
	*i += 1;
	arg[*i][0] = 0;
	return (1);
}

int	is_redirection(t_info *info, t_token *target, char **arg, int *i)
{
	if (target->redir_l || target->heredoc)
	{
		if (!do_l_or_heredoc(info, target, arg, i))
			return (0);
		return (1);
	}
	else if (target->redir_r)
	{
		if (!do_r(info, target, arg, i))
			return (0);
		return (1);
	}
	else if (target->append)
	{
		if (!do_append(info, target, arg, i))
			return (0);
		return (1);
	}
	return (2);
}

char	**check_redirection(t_info *info, t_token *pipe)
{
	int		i;
	int		arg_size;
	int		is_red;
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
		is_red = is_redirection(info, target, arg, &i);
		if (is_red == 0)
			return (0);
		else if (is_red == 1)
			target = target->next;
		target = target->next;
		i++;
	}
	arg = arrange_arg(arg, arg_size);
	return (arg);
}
