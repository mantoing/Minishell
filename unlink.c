/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unlink.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 08:16:25 by suhkim            #+#    #+#             */
/*   Updated: 2022/12/23 16:36:29 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	check_unlink(t_info *info, t_token *temp)
{
	if (temp->next == &info->input->tail || temp->next->pipe \
			|| temp->next->redir_r || temp->next->redir_l \
			|| temp->next->heredoc || temp->next->append)
		return (0);
	else
		return (1);
}

void	unlink_all(t_info *info)
{
	t_token	*temp;

	temp = info->input->head.next;
	while (temp != &info->input->tail)
	{
		if (temp->heredoc)
		{
			if (check_unlink(info, temp))
				unlink(temp->next->token);
		}
		temp = temp->next;
	}
}
