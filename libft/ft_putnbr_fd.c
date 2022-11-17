/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 18:39:15 by suhkim            #+#    #+#             */
/*   Updated: 2022/03/27 16:29:03 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void	ft_putu_fd(unsigned int num, int fd)
{
	char	c;

	if (num / 10)
	{
		ft_putu_fd(num / 10, fd);
	}
	c = num % 10 + '0';
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	num;

	num = n;
	if (n < 0)
	{
		num = -n;
		write(fd, "-", 1);
	}
	ft_putu_fd(num, fd);
}
