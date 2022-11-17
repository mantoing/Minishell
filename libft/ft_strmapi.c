/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 18:21:31 by suhkim            #+#    #+#             */
/*   Updated: 2022/03/27 16:24:55 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char			*newstr;
	unsigned int	i;

	if (!s || !f)
		return (0);
	newstr = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!newstr)
		return (0);
	i = 0;
	while (*(s + i))
	{
		*(newstr + i) = f(i, *(s + i));
		i++;
	}
	*(newstr + i) = 0;
	return (newstr);
}
