/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 05:49:32 by jaeywon           #+#    #+#             */
/*   Updated: 2023/01/20 01:25:08 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	check_exist_file(char *file)
{
	if (access(file, F_OK) != -1)
	{
		if (access(file, R_OK) != -1 && access(file, X_OK) != -1)
			return (1);
		else
			return (2);
	}
	return (0);
}

static char	*handle_cmd_absol_path(t_info *info, char *path, char **arg)
{
	char	**temp;
	char	*res;
	char	*sla;
	int		i;

	i = 0;
	temp = ft_split(path, ':');
	sla = ft_strjoin(ft_strdup("/"), ft_strdup(arg[0]));
	res = NULL;
	while (temp[i])
	{
		res = ft_strjoin(ft_strdup(temp[i]), ft_strdup(sla));
		if (check_exist_file(res))
			break ;
		free(res);
		++i;
	}
	if (!temp[i])
		info->exit_code = print_err_with_exit_num(arg[0], \
				"command not found", NULL, 127);
	free(sla);
	if (temp[i] == NULL)
		res = NULL;
	free_temp(temp);
	return (res);
}

static char	*find_env_name(t_info *info)
{
	t_node	*tmp;

	tmp = info->env_stack->head.next;
	while (tmp != &info->env_stack->tail)
	{
		if (!ft_strcmp("PATH", tmp->env_name))
			return (ft_strdup(tmp->env_value));
		tmp = tmp->next;
	}
	return (NULL);
}

static int	check_file_valid(char **arg, t_info *info)
{
	int	file_valid;
	int	ret;

	ret = 0;
	if (ft_strchr(arg[0], '/'))
	{
		file_valid = check_exist_file(arg[0]);
		if (file_valid != 1)
		{
			if (file_valid == 0)
				info->exit_code = print_err_with_exit_num(arg[0], \
						"No such file or directory", NULL, 127);
			if (file_valid == 2)
				info->exit_code = print_err_with_exit_num(arg[0], \
						"Permission denied", NULL, 126);
			ret = 1;
		}
		else
			ret = is_dir(info, arg[0]);
	}
	return (ret);
}

char	*check_absol_path(char **arg, t_info *info)
{
	char	*res;
	char	*path;
	int		ret;

	res = NULL;
	ret = check_file_valid(arg, info);
	path = find_env_name(info);
	if (ret == 1)
		return (0);
	else if (ret == 2)
		return (ft_strdup(arg[0]));
	if (path != NULL)
		res = handle_cmd_absol_path(info, path, arg);
	else
		info->exit_code = print_err_with_exit_num(arg[0], \
				"No such file or directory", NULL, 1);
	if (res == NULL && check_exist_file(arg[0]))
		return (ft_strdup(arg[0]));
	return (res);
}
