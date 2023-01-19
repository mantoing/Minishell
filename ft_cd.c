/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:26:22 by jaeywon           #+#    #+#             */
/*   Updated: 2023/01/20 02:40:33 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static int	no_home(t_info *info, char *temp)
{
	free(temp);
	info->exit_code = print_err_with_exit_num("cd", \
			"HOME path does not exist", NULL, 1);
	return (0);
}

static int	run_chdir(t_info *info, char **arg)
{
	char	*temp;

	if (arg[1] == NULL)
	{
		temp = get_env_value(info, "HOME");
		if (chdir(temp) < 0)
			return (no_home(info, temp));
		free(temp);
		return (1);
	}
	else if (arg[1][0] == '~')
	{
		temp = arg[1];
		arg[1] = ft_strjoin(ft_strdup(info->home_dir), ft_strdup(arg[1] + 1));
		free(temp);
	}
	if (chdir(arg[1]) < 0)
	{
		info->exit_code = print_err_with_exit_num("cd", arg[1], \
				strerror(errno), 1);
		return (0);
	}
	return (1);
}

static void	change_oldpwd(t_info *info)
{
	t_node	*target;

	target = info->env_stack->head.next;
	while (target != &info->env_stack->tail)
	{
		if (!ft_strcmp(target->env_name, "OLDPWD"))
			break ;
		target = target->next;
	}
	free(target->env_value);
	target->env_value = get_env_value(info, "PWD");
}

static void	change_pwd(t_info *info)
{
	char	*cwd;
	t_node	*target;

	cwd = getcwd(NULL, 0);
	target = info->env_stack->head.next;
	while (target != &info->env_stack->tail)
	{
		if (!ft_strcmp(target->env_name, "PWD"))
			break ;
		target = target->next;
	}
	if (cwd)
	{
		free(target->env_value);
		target->env_value = ft_strdup(cwd);
	}
	free(cwd);
}

int	ft_cd(char **arg, t_info *info)
{
	if (!run_chdir(info, arg))
		return (0);
	change_oldpwd(info);
	change_pwd(info);
	g_signal = 0;
	return (1);
}
