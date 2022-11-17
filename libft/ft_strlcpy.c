/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 21:45:35 by suhkim            #+#    #+#             */
/*   Updated: 2022/03/27 15:59:19 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(src);
	i = 0;
	if (dstsize == 0)
		return (len);
	while (*(src + i) != '\0')
	{
		if (i == dstsize - 1)
			break ;
		*(dst + i) = *(src + i);
		i++;
	}
	*(dst + i) = '\0';
	return (len);
}
