/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 03:34:45 by suhkim            #+#    #+#             */
/*   Updated: 2022/11/30 01:18:09 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	cnt_arg_arr_size(char **arg)
{
	int	i;

	i = 0;
	while (*(arg + i))
		i++;
	return (i);
}

char	**arrange_arg(char **arg, int arg_size)
{
	char	**ret;
	int		i;
	int		ret_size;

	i = 0;
	ret_size = 0;
	while (i < arg_size)
	{
		if (arg[i][0])
			ret_size++;
		i++;
	}
	i = 0;
	ret = malloc(sizeof(char *) * (ret_size + 1));
	ret_size = 0;
	while (i < arg_size)
	{
		if (arg[i][0])
			ret[ret_size++] = ft_strdup(arg[i]);
		i++;
	}
	ret[ret_size] = 0;
	free_arg(arg, arg_size);
	return (ret);
}
