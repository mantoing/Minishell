/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 01:46:44 by suhkim            #+#    #+#             */
/*   Updated: 2023/01/19 19:03:15 by jaeywon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static	int	parse_isspace(char c)
{
	if (c == '\t' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\v' || c == ' ')
		return (1);
	return (0);
}

static	int	not_env_arg(char c)
{
	if (!ft_isalnum(c) && c != '_' && c != '?' && c != '\'' && c != '\"')
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
	while (*(target + i) && !(quote == 0 && parse_isspace(*(target + i))))
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
		else if (parse_isspace(*(target + i)) && quote == 0)
				i++;
		else if (*(target + i) == '|' && quote == 0)
		{
			if (ft_strlen(str))
				break ;
			else
			{
				push_back_token(info->input, ft_strdup("|"));
				info->input->tail.prev->pipe = 1;
				info->pipe_cnt++;
				free(str);
				return (1);
			}
		}
		else if ((*(target + i) == '<' || *(target + i) == '>') && \
				quote == 0)
		{
			if (ft_strlen(str))
				break ;
			else
			{
				free(str);
				return (is_redir(info, target + i));
			}
		}
		else
		{
			if (quote != 1)
			{
				if (*(target + i) != '$')
					str = ft_strjoin(str, ft_substr(target, i, 1));
				else if (*(target + i + 1) == 0 || not_env_arg(*(target + i \
								+ 1)))
					str = ft_strjoin(str, ft_substr(target, i, 1));
				else
				{
					if (*(target + i + 1) != '\'' && *(target + i + 1) != '\"')
						str = ft_strjoin(str, get_env(info, target, &i));
					else
					{
						if (quote == 0)
							str = ft_strjoin(str, ft_strdup(""));
						else
							str = ft_strjoin(str, ft_substr(target, i, 1));
					}
				}
			}
			else
				str = ft_strjoin(str, ft_substr(target, i, 1));
		}
		i++;
	}
	if (i != 0)
		push_back_token(info->input, ft_strdup(str));
	free(str);
	if (quote != 0)
		return (-1);
	return (i);
}
