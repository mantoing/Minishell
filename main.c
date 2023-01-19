/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:06:01 by jaeywon           #+#    #+#             */
/*   Updated: 2023/01/19 22:33:41 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	g_signal;

static void	do_minishell(t_info *info, char *line)
{
	add_history(line);
	if (parse(info, line))
	{
		t_token	*temp;
		temp = info->input->head.next;
		dprintf(2, "finished parse\n\n\n");
		while (temp != &info->input->tail)
		{
			dprintf(2, "%s\n", temp->token);
			temp = temp->next;
		}
		dprintf(2, "\n\n\nfinished parse\n");
		if (heredoc(info))
			ft_pipe(info);
		unlink_all(info);
		free_unlink(info->unlink);
	}
	free_token(info->input);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_info	info;

	init_main(argc, argv, env, &info);
	while (1)
	{
		if (g_signal == 1)
		{
			info.exit_code = 1;
			g_signal = 0;
		}
		line = readline("minishell$ ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		else if (*line != '\0')
			do_minishell(&info, line);
		free(line);
		line = NULL;
	}
	return (0);
}
