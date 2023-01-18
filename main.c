/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:06:01 by jaeywon           #+#    #+#             */
/*   Updated: 2023/01/18 13:43:43 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int g_signal;

int main(int argc, char **argv, char **env)
{
    char    *line;
    t_info  info;

    if (argc != 1)
    {
        info.exit_code = print_err_with_exit_num(argv[1], \
				"No such file or directory", NULL, 127);
		exit(info.exit_code);
    }
//    if (*(argv + 1))
//        return (0);
    init_info(&info);
    init_terminal();
    set_signal("SHELL");
    save_env(env, &info);
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
        {
            add_history(line);
            if (parse(&info, line))
            {
//                t_token *temp;
//                temp = info.input->head.next;
//                while (temp != &info.input->tail)
//                {
//                    dprintf(2, "%s\n", temp->token);
//                    temp = temp->next;
//                }
                if (heredoc(&info))
                    ft_pipe(&info);
                unlink_all(&info);
                free_unlink(info.unlink);
            }
            free_token(info.input);
        }
        free(line);
        line = NULL;
    }
    return (0);
}
