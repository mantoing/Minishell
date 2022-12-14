/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_r.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 22:41:23 by suhkim            #+#    #+#             */
/*   Updated: 2022/11/30 00:45:13 by suhkim           ###   ########.fr       */
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
		 fd = open(target->next->token,\
				 O_WRONLY | O_CREAT | O_TRUNC, 0644);
		 if (fd < 0)
		 {
			 //error
			 return (0);
		 }
		 ft_dup2(fd, STDOUT_FILENO);
		 target = target->next->next;
	}
	else
		return (0);
	return (1);
}
