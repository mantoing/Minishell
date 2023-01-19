/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 01:46:44 by suhkim            #+#    #+#             */
/*   Updated: 2023/01/19 23:20:43 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static char	*if_quotes(t_info *info, char *target, int *i, char *str)
{
	if (*(target + *i) == '\'')
	{
		if (info->quote == 0)
			info->quote = 1;
		else if (info->quote == 1)
			info->quote = 0;
		else
			return (ft_strjoin(str, ft_substr(target, *i, 1)));
	}
	else if (*(target + *i) == '\"')
	{
		if (info->quote == 0)
			info->quote = 2;
		else if (info->quote == 1)
			return (ft_strjoin(str, ft_substr(target, *i, 1)));
		else
			info->quote = 0;
	}
	return (str);
}

static int	if_pipe(t_info *info, char *str)
{
	if (ft_strlen(str))
		return (1);
	else
	{
		push_back_token(info->input, ft_strdup("|"));
		info->input->tail.prev->pipe = 1;
		info->pipe_cnt++;
		free(str);
		return (0);
	}
}

static char	*if_dollor(t_info *info, char *target, int *i, char *str)
{
	if (info->quote != 1)
	{
		if (*(target + *i) != '$')
			str = ft_strjoin(str, ft_substr(target, *i, 1));
		else if (*(target + *i + 1) == 0 || not_env_arg(*(target + *i \
						+ 1)))
			str = ft_strjoin(str, ft_substr(target, *i, 1));
		else
		{
			if (*(target + *i + 1) != '\'' && *(target + *i + 1) != '\"')
				str = ft_strjoin(str, get_env(info, target, &*i));
			else
			{
				if (info->quote == 0)
					str = ft_strjoin(str, ft_strdup(""));
				else
					str = ft_strjoin(str, ft_substr(target, *i, 1));
			}
		}
	}
	else
		str = ft_strjoin(str, ft_substr(target, *i, 1));
	return (str);
}

static int	check_split_token(t_info *info, char *target, int *i, char **str)
{
	if (*(target + *i) == '\'' || *(target + *i) == '\"')
		*str = if_quotes(info, target, i, *str);
	else if (parse_isspace(*(target + *i)) && info->quote == 0)
			*i += 1;
	else if (*(target + *i) == '|' && info->quote == 0)
	{
		if (if_pipe(info, *str))
			return (0);
		return (1);
	}
	else if ((*(target + *i) == '<' || *(target + *i) == '>') && \
			info->quote == 0)
	{
		if (ft_strlen(*str))
			return (0);
		else
		{
			free(*str);
			return (2);
		}
	}
	else
		*str = if_dollor(info, target, i, *str);
	*i += 1;
	return (3);
}

int	split_token(t_info *info, char *target)
{
	int		i;
	char	*str;
	int		flag;

	i = 0;
	info->quote = 0;
	str = ft_strdup("");
	while (*(target + i) && !(info->quote == 0 && parse_isspace(*(target + i))))
	{
		flag = check_split_token(info, target, &i, &str);
		if (flag == 0)
			break ;
		else if (flag == 1)
			return (1);
		else if (flag == 2)
			return (is_redir(info, target + i));
	}
	if (i != 0)
		push_back_token(info->input, ft_strdup(str));
	free(str);
	if (info->quote != 0)
		return (-1);
	return (i);
}
