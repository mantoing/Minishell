/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 22:04:20 by suhkim            #+#    #+#             */
/*   Updated: 2022/03/27 16:18:51 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	check_set(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*str;
	size_t	len;

	if (!s1)
		return (0);
	if (!set || *set == 0)
		return (ft_strdup(s1));
	while (check_set(*s1, set))
		s1++;
	len = ft_strlen(s1);
	while (len && check_set(*(s1 + len - 1), set))
		len--;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	ft_strlcpy(str, (char *)s1, len + 1);
	return (str);
}
