/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:06:01 by jaeywon           #+#    #+#             */
/*   Updated: 2022/11/30 08:20:17 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// int main(int ac, char **av)
// {
// // 	if (ac != 1)
// // 		return (put_error);

// 	while (1)
// 	{
// 		read()
// 	}
// }

#include "./minishell.h"

// void handler(int signum)
// {
//     if (signum != SIGINT)
//         return;
//     //dprintf("ctrl + c\n");
//     rl_on_new_line();
//     rl_replace_line("", 1);
//     rl_redisplay();
// }

int main(int argc, char **argv, char **env)
{
    // int ret;
    char *line;
    t_info  info;

    if (argc != 1)
        return (-1);
    init_info(&info);
    (void)argc;
    (void)argv;
   save_env(env, info.env_stack);
   // save_env(env, &env_arr);
    // signal(SIGINT, handler);
    while (1)
    {
        line = readline("minishell$ ");
        if (!line)
        {
            //dprintf(2,"ctrl + d\n");
            break ;
        }
        else if (*line != '\0')
        {
            parse(&info, line);
            add_history(line);
            if (heredoc(&info))
            {
                ft_pipe(&info);
                unlink_all(&info);
            }
            free(line);
            free_token(info.input);
            line = NULL;
        }
    }
    return (0);
}
