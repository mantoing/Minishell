/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:18:54 by jaeywon           #+#    #+#             */
/*   Updated: 2023/01/19 22:13:10 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static int	count_dup_arg(char *str, char target)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (*(str + i))
	{
		if (*(str + i) == target)
			cnt++;
		else
			break ;
		i++;
	}
	return (cnt);
}

static int	cnt_is_three(t_info *info, char *target, int cnt)
{
	int		ret;
	char	*str;

	ret = 0;
	if (cnt >= 3)
	{
		if (cnt > 3)
			cnt = 2;
		else
			cnt -= 2;
		str = ft_substr(target, 0, cnt);
		info->exit_code = put_err_redir(str, 258);
		g_signal = 0;
		free(str);
		ret = -2;
	}
	return (ret);
}

static int	cnt_is_two_one(t_info *info, int flag)
{
	if (flag == 0)
	{
		push_back_token(info->input, ft_strdup("<<"));
		info->input->tail.prev->heredoc = 1;
		return (2);
	}
	else if (flag == 1)
	{
		push_back_token(info->input, ft_strdup(">>"));
		info->input->tail.prev->append = 1;
		return (2);
	}
	else if (flag == 2)
	{
		push_back_token(info->input, ft_strdup("<"));
		info->input->tail.prev->redir_l = 1;
		return (1);
	}
	else if (flag == 3)
	{
		push_back_token(info->input, ft_strdup(">"));
		info->input->tail.prev->redir_r = 1;
		return (1);
	}
	return (0);
}

static int	sep_cnt(t_info *info, char *target, int cnt, int flag)
{
	int	ret;

	ret = 0;
	if (flag == 0)
	{
		if (cnt >= 3)
			ret = cnt_is_three(info, target, cnt);
		else if (cnt == 2)
			ret = cnt_is_two_one(info, 0);
		else
			ret = cnt_is_two_one(info, 2);
	}
	if (flag == 1)
	{
		if (cnt >= 3)
			ret = cnt_is_three(info, target, cnt);
		else if (cnt == 2)
			ret = cnt_is_two_one(info, 1);
		else
			ret = cnt_is_two_one(info, 3);
	}
	return (ret);
}

int	is_redir(t_info *info, char *target)
{
	int		cnt;
	int		ret;

	ret = 0;
	if (*target == '<')
	{
		cnt = count_dup_arg(target, '<');
		ret = sep_cnt(info, target, cnt, 0);
	}
	else if (*target == '>')
	{
		cnt = count_dup_arg(target, '>');
		ret = sep_cnt(info, target, cnt, 1);
	}
	else
		return (-2);
	return (ret);
}
