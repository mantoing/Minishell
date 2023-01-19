/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:06:39 by suhkim            #+#    #+#             */
/*   Updated: 2023/01/19 17:09:33 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	valid_heredoc(t_info *info, t_token *temp)
{
	if (temp->next == &info->input->tail || temp->next->pipe \
			|| temp->next->redir_r || temp->next->redir_l \
			|| temp->next->heredoc || temp->next->append)
		return (0);
	else
		return (1);
}

char	*create_temp_file_name(size_t *temp_cnt)
{
	char	*n;
	char	*temp_file_name;
	char	*ret;
	int		fd;

	n = ft_itoa(*temp_cnt);
	temp_file_name = ft_strjoin(ft_strdup("/tmp/minishell_tmp_"), n);
	fd = open(temp_file_name, O_RDONLY);
	while (fd >= 0)
	{
		close(fd);
		*temp_cnt += 1;
		free(temp_file_name);
		n = ft_itoa(*temp_cnt);
		temp_file_name = ft_strjoin(ft_strdup("/tmp/minishell_tmp_"), n);
		fd = open(temp_file_name, O_RDONLY);
	}
	ret = ft_strdup(temp_file_name);
	free(temp_file_name);
	close(fd);
	return (ret);
}

int	wait_heredoc(int pid)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	while (waitpid(-1, 0, 0) != -1)
		;
	if (WIFSIGNALED(status))
	{
		printf("\n");
		return (0);
	}
	return (1);
}

void	change_heredoc_file_name(t_token *arg, char *temp_file_name)
{
	free(arg->token);
	arg->token = ft_strdup(temp_file_name);
}

void	change_arg_temp_file(t_info *info)
{
	t_token			*temp;
	t_unlink_name	*temp_unlink;
	size_t			temp_cnt;

	temp_cnt = 0;
	temp = info->input->head.next;
	temp_unlink = info->unlink->head.next;
	while (temp != &info->input->tail)
	{
		if (temp->heredoc)
		{
			if (valid_heredoc(info, temp))
			{
				change_heredoc_file_name(temp->next, \
				temp_unlink->temp_file_name);
				temp_unlink = temp_unlink->next;
			}
			else
				return ;
		}
		temp = temp->next;
	}
}
