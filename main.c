/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:06:01 by jaeywon           #+#    #+#             */
/*   Updated: 2023/01/18 03:13:50 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int g_errno;

int main(int argc, char **argv, char **env)
{
    // int ret;
    char    *line;
    t_info  info;

    if (argc != 1)
        return (-1);
    if (*(argv + 1))
        return (0);
    init_info(&info);
    init_terminal(&info, argc, argv);
    set_signal("SHELL");
    save_env(env, &info);
    while (1)
    {
        if (g_errno == 1)
        {
            info.exit_code = 1;
            g_errno = 0;
        }
        line = readline("minishell$ ");
        if (!line)
        {
            dprintf(2,"exit\n");
            break ;
        }
        else if (*line != '\0')
        {
            parse(&info, line);
            add_history(line);
            if (heredoc(&info))
                ft_pipe(&info);
            unlink_all(&info);
            free(line);
            free_token(info.input);
            free_unlink(info.unlink);
            line = NULL;
        }
    }
    return (0);
}
