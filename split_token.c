/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 01:46:44 by suhkim            #+#    #+#             */
/*   Updated: 2022/11/24 22:49:40 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static	int	isspace(char c)
{
	if (c == '\t' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\v' || c == ' ')
		return (1);
	return (0);
}

int	split_token(t_info *info, char *target)
{
	int		quote;
	int		i;
	char	*str;

	quote = 0;
	i = 0;
	str = ft_strdup("");

	while (*(target + i) && !(quote == 0 && isspace(*(target + i))))
	{
		if (*(target + i) == '\'')
		{
			if (quote == 0)
				quote = 1;
			else if (quote == 1)
				quote = 0;
			else
				str = ft_strjoin(str, ft_substr(target, i, 1));
		}
		else if (*(target + i) == '\"')
		{
			if (quote == 0)
				quote = 2;
			else if (quote == 1)
				str = ft_strjoin(str, ft_substr(target, i, 1));
			else
				quote = 0;
		}
		else if (isspace(*(target + i)) && quote == 0)
				i++;
		else if (*(target + i) == '|' && quote == 0)
		{
			if (ft_strlen(str))
				break ;
			else
			{
				push_back_token(info->input, "|");
				info->input->tail.prev->pipe = 1;
				info->pipe_cnt++;
				return (1);
			}
		}
		else
		{
			if (quote != 1)
			{
				if (*(target + i) != '$')
					str = ft_strjoin(str, ft_substr(target, i, 1));
				else
				{
					if (*(target + i + 1) != '\'' && *(target + i + 1) != '\"')
						str = ft_strjoin(str, get_env(info, target, &i));
					else
						str = ft_strjoin(str, ft_substr(target, i, 1));
				}
			}
			else
				str = ft_strjoin(str, ft_substr(target, i, 1));
		}
		i++;
	}
	if (i != 0)
		push_back_token(info->input, str);
	return (i);
}
