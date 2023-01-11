/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_l.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 04:51:16 by suhkim            #+#    #+#             */
/*   Updated: 2023/01/12 04:03:40 by jaeywon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"
#include <errno.h>

static int	valid_redir_l(t_info *info, t_token *temp)
{
	if (temp->next == &info->input->tail || temp->next->pipe \
			|| temp->next->redir_r || temp->next->redir_l \
			|| temp->next->heredoc || temp->next->append)
		return (0);
	else
		return (1);
}

int	redir_l(t_info *info, t_token *target)
{
	int		fd;

	if (valid_redir_l(info, target))
	{
		fd = open(target->next->token, O_RDONLY);
		if (fd < 0)
		{
			 print_err("minishell", target->next->token, strerror(errno));
		    return (0);
		}
		ft_dup2(fd, STDIN_FILENO);
	}
	else
		return (0);
	return (1);
}
