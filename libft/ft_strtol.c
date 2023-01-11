/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 02:41:49 by suhkim            #+#    #+#             */
/*   Updated: 2022/11/12 02:42:13 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

long long	ft_strtol(char *str)
{
	long long	ans;
	int			sign;
	int			count;

	count = 0;
	ans = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t' || *str == '\v' || *str == '\r'
		|| *str == '\n' || *str == '\f')
		str++;
	if (*str == '-' || *str == '+')
		if (*(str++) == '-')
			sign = -1;
	while (++count && *str && *str >= '0' && *str <= '9')
	{
		ans = 10 * ans + (*str++ - '0');
		if ((count > 19 && sign == -1) || (ans < 0 && sign == -1))
			return ((-9223372036854775807 - 1));
		else if ((count > 19 && sign == 1) || (ans < 0 && sign == 1))
			return (9223372036854775807);
	}
	return (sign * ans);
}
