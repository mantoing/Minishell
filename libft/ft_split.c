/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:14:36 by suhkim            #+#    #+#             */
/*   Updated: 2022/03/27 16:22:37 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	check_set(char target, char set)
{
	return (target == set);
}

static int	cnt_word(const char *s, char c, int mode)
{
	int	cnt;
	int	words;

	words = 1;
	cnt = 0;
	while (*s)
	{
		if (!check_set(*s, c) && (*(s + 1) == 0 || check_set(*(s + 1), c)))
		{
			cnt++;
			if (*(s + 1) == 0 && mode == 0)
				return (cnt);
			if (mode)
				return (words);
		}
		words++;
		s++;
	}
	return (cnt);
}

static char	**freeall(char **carr, int cnt)
{
	while (cnt--)
		free(carr[cnt]);
	free(carr);
	return (0);
}

static int	set_words(char *set, const char *s, char c)
{
	int	i;

	i = 0;
	while (*(s + i) && !check_set(*(s + i), c))
	{
		*(set + i) = *(s + i);
		i++;
	}
	*(set + i) = 0;
	return (i);
}

char	**ft_split(const char *s, char c)
{
	int		cnt;
	char	**carr;

	if (!s)
		return (0);
	cnt = 0;
	carr = (char **)malloc(sizeof(char *) * (cnt_word(s, c, 0) + 1));
	if (!carr)
		return (0);
	while (*s)
	{
		if (!check_set(*s, c))
		{
			carr[cnt] = (char *)malloc(sizeof(char) * (cnt_word(s, c, 1) + 1));
			if (!carr[cnt])
				return (freeall(carr, cnt));
			s += set_words(carr[cnt++], s, c);
		}
		else
			s++;
	}
	carr[cnt] = 0;
	return (carr);
}
