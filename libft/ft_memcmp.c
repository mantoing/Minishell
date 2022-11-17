/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 14:52:20 by suhkim            #+#    #+#             */
/*   Updated: 2022/03/27 16:08:10 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*sptr1;
	const unsigned char	*sptr2;

	sptr1 = (const unsigned char *)s1;
	sptr2 = (const unsigned char *)s2;
	while (n)
	{
		if (*sptr1 != *sptr2)
			return (*sptr1 - *sptr2);
		sptr1++;
		sptr2++;
		n--;
	}
	return (0);
}
