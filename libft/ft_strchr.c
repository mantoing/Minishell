/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 19:01:36 by suhkim            #+#    #+#             */
/*   Updated: 2022/03/27 16:03:43 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	const char	*sptr;

	sptr = s;
	if (c == 0)
		return ((char *)sptr + ft_strlen(s));
	while (*sptr)
	{
		if (*(char *)sptr == (char)c)
			return ((char *)sptr);
		sptr++;
	}
	return (0);
}
