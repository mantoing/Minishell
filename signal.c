/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 00:24:40 by suhkim            #+#    #+#             */
/*   Updated: 2023/01/18 03:34:54 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static void	sigint_handler_shell(int sig)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_signal = 1;
	(void) sig;
}

static void	sigint_handler_waitheredoc(int sig)
{
	g_signal = 1;
	(void) sig;
}

void	set_signal(char *type)
{
	if (!ft_strcmp(type, "SHELL"))
	{
		signal(SIGINT, sigint_handler_shell);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (!ft_strcmp(type, "HEREDOCWAIT"))
	{
		signal(SIGINT, sigint_handler_waitheredoc);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (!ft_strcmp(type, "HEREDOC"))
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (!ft_strcmp(type, "DEFAULT"))
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (!ft_strcmp(type, "IGNORE"))
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}
