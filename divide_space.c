/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 23:04:27 by suhkim            #+#    #+#             */
/*   Updated: 2022/11/18 00:41:10 by suhkim           ###   ########.fr       */
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

static int	save_input(t_input *input, char *substr, int flag)
{
	if (flag == 0)
		input->cmd = ft_strdup(substr);
	else if (flag == 1)
		input->opt = ft_strdup(substr);
	else if (flag == 2)
		input->arg = ft_strdup(substr);
	else 
		return (0);
	free(substr);
	return (1);
}

void	divide_space(t_input *input, char *line)
{
	unsigned int	i;
	unsigned int	j;
	int				flag;

	flag = 0;
	i = 0;
	while (*(line + i))
	{
		if (!isspace(*(line + i)))
		{
			if (flag >= 3)
				break ;
				//not_valid();
			j = 0;
 	 		while (*(line + i + j) && !isspace(*(line + i + j)))
 	 			j++;
 	 		save_input(input, ft_substr(line, i, j), flag++);
 	 		i += j;
		}
		else
			i++;
	}
	if (i != ft_strlen(line))
	{
		printf("\nNot Valid input\n");
		//not_valid();
	}
}
