/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 05:49:32 by jaeywon           #+#    #+#             */
/*   Updated: 2022/12/02 07:43:09 by suhkim           ###   ########.fr       */
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
	int	fd;

	fd = open(file, O_RDONLY);
	close(fd);
	if (fd == -1)
		return (0);
	else
		return (1);
}

static char	*handle_cmd_absol_path(char *path, char **arg)
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
		printf("cmd not found\n");
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

	res = NULL;
	path = find_env_name(info);
	if (ft_strchr(arg[0], '/'))
	{
		if (!check_exist_file(arg[0]))
		{
			printf("search not file\n");
			return (0);
		}
		else
			return (ft_strdup(arg[0]));
	}
	if (path != NULL)
		res = handle_cmd_absol_path(path, arg);
	if (res == NULL && check_exist_file(arg[0]))
		return (ft_strdup(arg[0]));
	return (res);
}

