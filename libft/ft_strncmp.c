/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 19:28:16 by suhkim            #+#    #+#             */
/*   Updated: 2022/03/27 16:05:04 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				i;
	const unsigned char	*sptr1;
	const unsigned char	*sptr2;

	sptr1 = (const unsigned char *)s1;
	sptr2 = (const unsigned char *)s2;
	i = 0;
	while (i < n && *(sptr1 + i) != 0 && *(sptr2 + i) != 0)
	{
		if (*(sptr1 + i) != *(sptr2 + i))
			return (*(sptr1 + i) - *(sptr2 + i));
		i++;
	}
	if (i < n)
		return (*(sptr1 + i) - *(sptr2 + i));
	return (0);
}
