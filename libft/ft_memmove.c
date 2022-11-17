/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:33:12 by suhkim            #+#    #+#             */
/*   Updated: 2022/03/27 15:57:00 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dptr;
	unsigned char	*sptr;

	if (dst == src)
		return (dst);
	dptr = (unsigned char *)dst;
	sptr = (unsigned char *)src;
	if (src < dst)
	{
		while (len)
		{
			len--;
			*(dptr + len) = *(sptr + len);
		}
	}
	else
	{
		while (len)
		{
			*dptr++ = *sptr++;
			len--;
		}
	}
	return (dst);
}
