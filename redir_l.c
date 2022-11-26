/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_l.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 04:51:16 by suhkim            #+#    #+#             */
/*   Updated: 2022/11/27 05:14:03 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static int	valid_redir_l(t_info *info, t_token *temp)
{
	if (temp->next == &info->input->tail || temp->next->pipe \
			|| temp->next->redir_r || temp->next->redir_l \
			|| temp->next->heredoc || temp->next->append)
		return (0);
	else
		return (1);
}

char	**redir_l(t_info *info, t_token *pipe)
{
	int		fd;
	int		i;
	int		arg_size;
	char	**arg;
	t_token	*target;

	target = get_first_arg(info, pipe);
	arg_size = get_arg_size(info, target, pipe);
	arg = malloc(sizeof(char *) * (arg_size + 1));
	if (!arg)
		return (0);
	conv_arg(target, arg, arg_size);
	i = 0;
	while (target != &info->input->tail && target != pipe)
	{
		if (target->redir_r)
		{
			if (valid_redir_l(info, target))
			{
				 fd = open(target->next->token,\
						 O_WRONLY | O_CREAT | O_TRUNC, 0644);
				 if (fd < 0)
				 {
					 //error
				 }
				 ft_dup2(fd, STDOUT_FILENO);
				 target = target->next->next;
				 arg[i][0] = 0;
				 i++;
				 arg[i][0] = 0;
			}
			else
			{
				//error
			}
		}
		else
			target = target->next;
		i++;
	}
	arg = arrange_arg(arg, arg_size);
	return (arg);

}
