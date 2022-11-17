/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 17:14:14 by suhkim            #+#    #+#             */
/*   Updated: 2022/03/27 16:08:48 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	idx;

	idx = 0;
	if (*needle == 0)
		return ((char *)haystack);
	while (*(haystack + idx) && idx + ft_strlen(needle) <= len)
	{
		if (!ft_strncmp(haystack + idx, needle, ft_strlen(needle)))
			return ((char *)haystack + idx);
		idx++;
	}
	return (0);
}
