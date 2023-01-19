/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 00:39:39 by suhkim            #+#    #+#             */
/*   Updated: 2023/01/19 16:23:40 by jaeywon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	conv_arg(t_token *temp, char **arg, int arg_size)
{
	int	i;

	i = 0;
	while (i < arg_size)
	{
		*(arg + i) = ft_strdup(temp->token);
		temp = temp->next;
		i++;
	}
	*(arg + i) = NULL;
}

t_token	*get_first_arg(t_info *info, t_token *pipe)
{
	t_token	*temp;

	temp = pipe->prev;
	while (temp->prev != &info->input->head && !temp->prev->pipe)
		temp = temp->prev;
	return (temp);
}

int	get_arg_size(t_info *info, t_token *arg, t_token *pipe)
{
	t_token	*temp;
	int		arg_size;

	arg_size = 0;
	temp = arg;
	while (temp != &info->input->tail && temp != pipe)
	{
		arg_size++;
		temp = temp->next;
	}
	return (arg_size);
}

void	free_arg(char **arg, int arg_size)
{
	int	i;

	if (!arg)
		return ;
	i = 0;
	if (*arg)
	{
		while (i <= arg_size)
		{
			free(*(arg + i));
			i++;
		}
	}
	free(arg);
}

int	is_empty_arg(char **arg)
{
	if (!arg || !*(arg) || !**(arg))
		return (1);
	return (0);
}
