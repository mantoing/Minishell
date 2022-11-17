/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 23:04:27 by suhkim            #+#    #+#             */
/*   Updated: 2022/11/17 23:36:30 by suhkim           ###   ########.fr       */
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

void	parse(char *line)
{
	unsigned int	i;
	unsigned int	j;
	char			*cmd;
	char			*opt;
	char			*arg;

	i = 0;
	j = 0;
	while (*(line + i) && isspace(*(line + i)))
		i++;
	while (*(line + i + j) && !isspace(*(line + i + j)))
		j++;
	cmd = ft_substr(line, i, j);
	i += j;
	while (*(line + i) && isspace(*(line + i)))
		i++;
	j = 0;
	while (*(line + i + j) && !isspace(*(line + i + j)))
		j++;
	opt = ft_substr(line, i, j);
	i += j;
	while (*(line + i) && isspace(*(line + i)))
		i++;
	j = 0;
	while (*(line + i + j) && !isspace(*(line + i + j)))
		j++;
	arg = ft_substr(line, i, j);
	i += j;
	while (*(line + i) && isspace(*(line + i)))
		i++;
	printf("cmd = %s\n", cmd);
	printf("opt = %s\n", opt);
	printf("arg = %s\n", arg);
	if (i != ft_strlen(line))
	{
		printf("\nNot Valid input\n");
		//not_valid();
	}
}
