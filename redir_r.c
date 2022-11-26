/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_r.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 22:41:23 by suhkim            #+#    #+#             */
/*   Updated: 2022/11/27 05:17:17 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static int	valid_redir_r(t_info *info, t_token *temp)
{
	if (temp->next == &info->input->tail || temp->next->pipe \
			|| temp->next->redir_r || temp->next->redir_l \
			|| temp->next->heredoc || temp->next->append)
		return (0);
	else
		return (1);
}

char	**redir_r(t_info *info, t_token *pipe)
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
		//dprintf(2,"%d\n",i);
		if (target->redir_r)
		{
		//dprintf(2,"%d\n",i);
			if (valid_redir_r(info, target))
			{
		//dprintf(2,"%d\n",i);
				 fd = open(target->next->token,\
						 O_WRONLY | O_CREAT | O_TRUNC, 0644);
		//dprintf(2,"%d\n",i);
				 if (fd < 0)
				 {
					 //error
				 }
		//dprintf(2,"%d\n",i);
				 //dprintf(2,"> fd = %d\n", fd);
				 ft_dup2(fd, STDOUT_FILENO);
		//dprintf(2,"%d\n",i);
				 target = target->next->next;
				 //dprintf(2,"> fd = %d\n", fd);
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
