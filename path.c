/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 05:49:32 by jaeywon           #+#    #+#             */
/*   Updated: 2023/01/18 04:21:47 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	free_temp(char **temp)
{
	size_t	i;

	i = 0;
	if (!temp)
		return ;
	if (!*temp)
	{
		free(temp);
		return ;
	}
	while (temp[i])
		free(temp[i++]);
	free (temp);
}

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
	sla = ft_strjoin("/", arg[0]);
	res = NULL;
	while (temp[i])
	{
		res = ft_strjoin(temp[i], sla);
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
		if (!ft_strncmp("PATH", tmp->env_name, ft_strlen(tmp->env_name)))
			return (ft_strdup(tmp->env_value));
		tmp = tmp->next;
	}
	return (NULL);
}

char	*check_absol_path(char **arg, t_info *info)
{
	char	*res;
	char	*path;
	int		file_valid;

	res = NULL;
	path = find_env_name(info);
	if (ft_strchr(arg[0], '/'))
	{
		file_valid = check_exist_file(arg[0]);
		if (file_valid != 1)
		{
			if (file_valid == 0)
				info->exit_code = print_err_with_exit_num(arg[0],\
						"No such file or directory", NULL, 1);
			if (file_valid == 2)
				info->exit_code = print_err_with_exit_num(arg[0], \
						"Permission denied", NULL, 126);
			return (0);
		}
		else
			return (ft_strdup(arg[0]));
	}
	if (path != NULL)
		res = handle_cmd_absol_path(info, path, arg);
	else
		info->exit_code = print_err_with_exit_num(arg[0], \
				"No such file or directory", NULL, 1);
	if (res == NULL && check_exist_file(arg[0]))
		return (ft_strdup(arg[0]));
	return (res);
}
