/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:06:01 by jaeywon           #+#    #+#             */
/*   Updated: 2022/11/16 20:00:20 by jaeywon          ###   ########.fr       */
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

#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>

// void handler(int signum)
// {
//     if (signum != SIGINT)
//         return;
//     printf("ctrl + c\n");
//     rl_on_new_line();
//     rl_replace_line("", 1);
//     rl_redisplay();
// }

int main(void)
{
    // int ret;
    char *line;

    // signal(SIGINT, handler);
    while (1)
    {
        line = readline("minishell$ ");
        if (line)
        {
            // if (ret)
            //     printf("output> %s\n", line);
            //add_history(line);
            free(line);
            line = NULL;
        }
        else
        {
            printf("ctrl + d\n");
        }
    }
    return (0);
}