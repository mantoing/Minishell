/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 17:42:48 by suhkim            #+#    #+#             */
/*   Updated: 2022/11/17 23:56:02 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	cnt_num(int n)
{
	unsigned int	num;
	int				i;

	if (n == 0)
		return (1);
	i = 0;
	num = n;
	if (n < 0)
		num = -n;
	while (num)
	{
		i++;
		num /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*ans;
	int				len;
	unsigned int	num;

	len = cnt_num(n);
	num = n;
	if (n < 0)
	{
		num = -n;
		len++;
	}
	ans = (char *)malloc(sizeof(char) * (len + 1));
	if (!ans)
		return (0);
	ans[len] = 0;
	while (len--)
	{
		ans[len] = num % 10 + '0';
		num /= 10;
	}
	if (n < 0)
		ans[0] = '-';
	return (ans);
}
