/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:06:01 by jaeywon           #+#    #+#             */
/*   Updated: 2023/01/20 00:19:08 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	g_signal;

static void	do_minishell(t_info *info, char *line)
{
	add_history(line);
	if (parse(info, line))
	{
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
