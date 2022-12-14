/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 07:16:45 by jaeywon           #+#    #+#             */
/*   Updated: 2022/12/22 21:28:30 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	ft_export(char **arg, t_info *info)
{
	int	errno;
	// char **env_arr;

	errno = 0;
	// env_arr = change_list_to_arr_env(info);
	if (arg[1] == NULL)
		errno = ft_export_solo(info);
	// else if (is_valid_export(arg) == -1)
	// 	errno = 1;
	else
		errno = add_change_export(arg, info);
	return (errno);
}
