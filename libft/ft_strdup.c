/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 18:21:40 by suhkim            #+#    #+#             */
/*   Updated: 2022/03/27 16:12:26 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*dstr;

	len = ft_strlen(s1);
	dstr = (char *)malloc(sizeof(char) * (len + 1));
	if (dstr == 0)
		return (0);
	ft_strlcpy(dstr, (char *)s1, len + 1);
	return (dstr);
}
