/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 01:46:44 by suhkim            #+#    #+#             */
/*   Updated: 2022/11/18 05:04:31 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

/*
static int	quote_check(int	quote, int *i)
{
	if (quote == 1)
	{
		*i += 1;
		return (0);
	}
	else if (quote == 2)
		return (2);
	else
	{
		*i += 1;
		return (1);
	}
}

static int	double_quote_check(int quote, int *i)
{
	if (quote == 1)
		return (1);
	else if (quote == 2)
	{
		*i += 1;
		return (0);
	}
	else
	{
		*i += 1;
		return (2);
	}
}*/

char	*split_quote(t_info *info, char *target)
{
	int	quote;
	int	i;
	char	*str;

	quote = 0;
	i = 0;
	str = ft_strdup("");
	/*
	while (*(target + i))
	{
		if (*(target + i) == '\'')
			quote = quote_check(quote, &i);
		else if (*(target + i) == '\"')
			quote = double_quote_check(quote, &i);
		if (quote == 1) // in single quote
			str = ft_strjoin(str, ft_substr(target, i, 1));
		else if (quote == 2) // in double quote
		{
			if (*(target + i) != '$')
				str = ft_strjoin(str, ft_substr(target, i, 1));
			else
				str = ft_strjoin(str, get_env(info, target + i, &i));
		}
		else if (*(target + i))
			str = ft_strjoin(str, ft_substr(target, i, 1));
		i++;
	}*/
	while (*(target + i))
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
		else
		{
			if (quote != 1)
			{
				if (*(target + i) != '$')
					str = ft_strjoin(str, ft_substr(target, i, 1));
				else
					str = ft_strjoin(str, get_env(info, target, &i));
			}
			else
				str = ft_strjoin(str, ft_substr(target, i, 1));
		}
		i++;
	}
	return (str);
}
