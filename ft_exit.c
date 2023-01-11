/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 18:42:13 by suhkim            #+#    #+#             */
/*   Updated: 2023/01/12 04:53:19 by jaeywon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	ft_exit(char **arg, int pipe)
{
	int	errno;

	errno = 0;
	if (arg[1])
		errno = ft_atoi(arg[1]);
	if (!pipe)
		printf("exit\n");
	exit(1);
}
