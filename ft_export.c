/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 07:16:45 by jaeywon           #+#    #+#             */
/*   Updated: 2023/01/17 22:24:01 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	ft_export(char **arg, t_info *info)
{
	if (arg[1] == NULL)
		info->exit_code = ft_export_solo(info);
	else
		info->exit_code = ft_export_with_arg(info, arg);
	return (info->exit_code);
}
