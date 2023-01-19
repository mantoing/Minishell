/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_r.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 22:41:23 by suhkim            #+#    #+#             */
/*   Updated: 2023/01/20 01:59:09 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static int	valid_redir_r(t_info *info, t_token *temp)
{
	if (temp->next == &info->input->tail || temp->next->pipe \
			|| temp->next->redir_r || temp->next->redir_l \
			|| temp->next->heredoc || temp->next->append)
		return (0);
	else
		return (1);
}

int	redir_r(t_info *info, t_token *target)
{
	int		fd;

	if (valid_redir_r(info, target))
	{
		if (access(target->next->token, F_OK) != -1 && access(\
					target->next->token, W_OK) == -1)
		{
			info->exit_code = print_err_with_exit_num(target->next->token, \
					"Permission denied", NULL, 1);
			return (0);
		}
		fd = open(target->next->token, \
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
