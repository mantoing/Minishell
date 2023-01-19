/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 01:19:41 by suhkim            #+#    #+#             */
/*   Updated: 2023/01/19 19:05:20 by jaeywon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static void	exe_heredoc(t_token *target, size_t *temp_cnt)
{
	int		fd;
	char	*heredoc_line;
	char	*temp_file_name;
	char	*output;

	temp_file_name = create_temp_file_name(temp_cnt);
	fd = open(temp_file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(temp_file_name);
	set_signal("HEREDOC");
	while (1)
	{
		heredoc_line = readline("> ");
		if (!heredoc_line)
			break ;
		if (!ft_strcmp(heredoc_line, target->token))
		{
			free(heredoc_line);
			break ;
		}
		output = ft_strjoin(heredoc_line, ft_strdup("\n"));
		write(fd, output, ft_strlen(output) + 1);
		free(output);
		heredoc_line = NULL;
	}
	close(fd);
}

static void	is_heredoc(t_token *temp, size_t *temp_cnt)
{
	exe_heredoc(temp->next, temp_cnt);
	*temp_cnt += 1;
}

static int	check_heredoc(t_info *info)
{
	t_token	*temp;
	pid_t	pid;
	size_t	temp_cnt;

	temp_cnt = 0;
	temp = info->input->head.next;
	set_signal("IGNORE");
	pid = fork();
	if (pid == 0)
	{
		while (temp != &info->input->tail)
		{
			if (temp->heredoc)
			{
				if (valid_heredoc(info, temp))
					is_heredoc(temp, &temp_cnt);
				else
					exit(0);
			}
			temp = temp->next;
		}
		exit(0);
	}
	return (pid);
}

static void	save_temp_num(t_info *info)
{
	t_token	*temp;
	size_t	temp_cnt;

	temp_cnt = 0;
	temp = info->input->head.next;
	while (temp != &info->input->tail)
	{
		if (temp->heredoc)
		{
			if (valid_heredoc(info, temp))
			{
				push_back_unlink(info->unlink, \
						create_temp_file_name(&temp_cnt));
				temp_cnt += 1;
			}
		}
		temp = temp->next;
	}
}

int	heredoc(t_info *info)
{
	pid_t	pid;
	int		ifsignal;

	g_signal = 0;
	save_temp_num(info);
	pid = check_heredoc(info);
	set_signal("HEREDOCWAIT");
	ifsignal = wait_heredoc(pid);
	change_arg_temp_file(info);
	set_signal("SHELL");
	return (ifsignal);
}
