/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 00:26:59 by suhkim            #+#    #+#             */
/*   Updated: 2022/11/20 17:02:02 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	parse(t_info *info, char *line)
{
	char	**arv;
	char	*cmd;
	char	*opt;
	char	*arg;
	int		pid;
	int		status;

	arv = malloc(sizeof(char *) * 4);
	divide_space(&info->input, line);
//	printf("cmd = %s\n", info->input.cmd);
//	printf("opt = %s\n", info->input.opt);
//	printf("arg = %s\n", info->input.arg);
	cmd = split_quote(info, info->input.cmd);
	opt = split_quote(info, info->input.opt);
	arg = split_quote(info, info->input.arg);
//	printf("after split cmd = %s\n",cmd);
//	printf("after split opt = %s\n",opt);
//	printf("after split arg = %s\n",split_quote(info, info->input.arg));
	pid = fork();
	if (pid == 0)
	{
		if (!ft_strncmp(cmd, "echo", 4))
		{
		//	printf("\n i'm echo \n");
			arv[0] = ft_strdup(opt);
			arv[1] = ft_strdup(opt);
			arv[2] = ft_strdup(arg);
			arv[3] = NULL;
			execve("/bin/echo", arv, NULL);
		}
		exit(1);
	}
	else
	{
		pid = wait(&status);
	}
}
