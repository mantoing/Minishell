/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:18:57 by jaeywon           #+#    #+#             */
/*   Updated: 2023/01/20 01:27:47 by jaeywon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	sort_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	is_dir(t_info *info, char *name)
{
	struct stat	statbuf;

	stat(name, &statbuf);
	if (S_ISDIR(statbuf.st_mode))
	{
		info->exit_code = print_err_with_exit_num(name, \
				"Is a directory", NULL, 126);
		return (1);
	}
	return (2);
}
