/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 07:50:04 by suhkim            #+#    #+#             */
/*   Updated: 2023/01/20 01:58:34 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static int	valid_append(t_info *info, t_token *temp)
{
	if (temp->next == &info->input->tail || temp->next->pipe \
			|| temp->next->redir_r || temp->next->redir_l \
			|| temp->next->heredoc || temp->next->append)
		return (0);
	else
		return (1);
}

int	redir_append(t_info *info, t_token *target)
{
	int	fd;

	if (valid_append(info, target))
	{
		if (access(target->next->token, F_OK) != -1 && access(\
					target->next->token, W_OK) == -1)
		{
			info->exit_code = print_err_with_exit_num(target->next->token, \
					"Permission denied", NULL, 1);
			return (0);
		}
		fd = open(target->next->token, \
			O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
		{
			info->exit_code = print_err_with_exit_num(target->next->token, \
					strerror(errno), NULL, 1);
			return (0);
		}
		ft_dup2(fd, STDOUT_FILENO);
		target = target->next->next;
	}
	else
		return (0);
	return (1);
}
