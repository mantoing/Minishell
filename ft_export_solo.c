/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_solo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 07:35:13 by jaeywon           #+#    #+#             */
/*   Updated: 2023/01/20 02:13:47 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static char	**sort_name_arr(char **name)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;

	i = 0;
	len = sort_len(name);
	while (i < len)
	{
		j = 1;
		while (j < len)
		{
			if (ft_strcmp(name[j - 1], name[j]) > 0)
			{
				tmp = name[j - 1];
				name[j - 1] = name[j];
				name[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (name);
}

static char	**put_env_name_to_arr(t_info *info)
{
	char	**name_arr;
	t_node	*tmp;
	int		list_size;
	int		i;

	i = 0;
	list_size = cnt_list_size(info);
	tmp = info->env_stack->head.next;
	name_arr = (char **)malloc((sizeof(char *) * (list_size + 1)));
	while (i < list_size)
	{
		name_arr[i] = ft_strdup(tmp->env_name);
		tmp = tmp->next;
		i++;
	}
	name_arr[i] = 0;
	return (name_arr);
}

static char	*find_name_and_value(char *str, t_info *info)
{
	t_node	*tmp;

	tmp = info->env_stack->head.next;
	while (tmp != &info->env_stack->tail)
	{
		if (!ft_strcmp(str, tmp->env_name))
		{
			if (tmp->env_value)
				return (tmp->env_value);
			return (NULL);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

static void	only_print_export(t_info *info, char *sorted, int flag)
{
	char	*temp;

	if (flag == 1)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(sorted, 1);
	}
	if (flag == 2)
	{
		ft_putstr_fd("=\"", 1);
		temp = find_name_and_value(sorted, info);
		if (temp)
			ft_putstr_fd(temp, 1);
		ft_putstr_fd("\"\n", 1);
	}
}

int	ft_export_solo(t_info *info)
{
	char	**env_name_arr;
	char	**sorted_name_arr;
	int		i;
	int		len;

	i = 0;
	env_name_arr = put_env_name_to_arr(info);
	sorted_name_arr = sort_name_arr(env_name_arr);
	len = sort_len(sorted_name_arr);
	while (i < len)
	{
		only_print_export(info, sorted_name_arr[i], 1);
		if (!find_name_and_value(sorted_name_arr[i], info))
		{
			ft_putstr_fd("\n", 1);
			i++;
			continue ;
		}
		only_print_export(info, sorted_name_arr[i], 2);
		i++;
	}
	free_temp(env_name_arr);
	return (0);
}
