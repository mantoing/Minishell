/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 18:42:13 by suhkim            #+#    #+#             */
/*   Updated: 2023/01/09 18:51:44 by suhkim           ###   ########.fr       */
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
