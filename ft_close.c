/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 06:07:02 by suhkim            #+#    #+#             */
/*   Updated: 2023/01/18 08:23:38 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	ft_close(int fd)
{
	if (fd == 0 || fd == 1 || fd == 2)
		return ;
	dprintf(2, "how closing for %d  %d\n",fd, close(fd));
}
