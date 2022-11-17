/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 17:54:41 by suhkim            #+#    #+#             */
/*   Updated: 2022/03/27 15:59:45 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	d_len;
	size_t	s_len;

	d_len = ft_strlen(dst);
	s_len = ft_strlen(src);
	i = 0;
	if (d_len >= dstsize)
		return (s_len + dstsize);
	while (*(src + i) != '\0' && d_len + i < dstsize - 1)
	{
		*(dst + d_len + i) = *(src + i);
		i++;
	}
	*(dst + d_len + i) = '\0';
	return (s_len + d_len);
}
