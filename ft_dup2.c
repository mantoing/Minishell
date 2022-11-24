/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 06:07:03 by suhkim            #+#    #+#             */
/*   Updated: 2022/11/25 06:13:22 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	ft_dup2(int fd1, int fd2)
{
	if (fd1 == 0 || fd1 == 1 || fd1 == 2)
		return ;
	dup2(fd1, fd2);
	ft_close(fd1);
}
