/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 00:26:59 by suhkim            #+#    #+#             */
/*   Updated: 2022/11/30 03:01:41 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	parse(t_info *info, char *line)
{
	int		len;

	while (*(line))
	{
		len = split_token(info, line);
		if (!len)
			line++;
		else
			line += len;
	}
//	t_token *temp;
//	temp = info->input->head.next;
//	while (temp != &info->input->tail)
//	{
//		dprintf(2,"%s ", temp->token);
//		dprintf(2, "heredoc : %d ", temp->heredoc);
//		dprintf(2, "redir_l : %d ", temp->redir_l);
//		dprintf(2, "redir_r : %d ", temp->redir_r);
//		dprintf(2, "append  : %d\n", temp->append);
//		temp = temp->next;
//	}
	//토큰 보기
}
