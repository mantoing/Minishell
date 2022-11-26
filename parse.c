/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 00:26:59 by suhkim            #+#    #+#             */
/*   Updated: 2022/11/27 04:11:09 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	parse(t_info *info, char *line)
{
	int		len;
//	int		pid;
//	int		status;

	while (*(line))
	{
		len = split_token(info, line);
		if (!len)
			line++;
		else
			line += len;
	}
	t_token *temp;
	temp = info->input->head.next;
	while (temp != &info->input->tail)
	{
		//dprintf(2,"%s\n", temp->token);
		temp = temp->next;
	}
	//토큰 보기
	ft_pipe(info);
	/*
	pid = fork();
	if (pid == 0)
	{
		if (!ft_strncmp(cmd, "echo", 4))
		{
		//	//dprintf("\n i'm echo \n");
		}
		exit(1);
	}
	else
	{
		pid = wait(&status);
	}
	*/
}
