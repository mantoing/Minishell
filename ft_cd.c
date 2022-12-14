/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:26:22 by jaeywon           #+#    #+#             */
/*   Updated: 2022/12/22 20:54:12 by jaeywon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static void	get_both_pwd(char **env, char **pwd_value, char **oldpwd_value)
{
	int	i;

	i = 0;
	*pwd_value = NULL;
	*oldpwd_value = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD", 3) == 0)
			*pwd_value = env[i];
		if (ft_strncmp(env[i], "OLDPWD", 6) == 0)
			*oldpwd_value = env[i];
		i++;
	}
}

static int run_chdir(char **arg, char *home)
{
	if (arg[1] == NULL || !ft_strcmp(arg[1], "~"))
	{
		if (chdir(home) < 0)
		{
			printf("cd error home\n");
			return (1);
		}
	}
	else
	{
		if (chdir(arg[1]) < 0)
		{
			printf("cd error\n");
			return (1);
		}
	}
	return (0);
}

static void	change_oldpwd(char *cur, char *old_pwdvalue, t_info *info)
{
	char **arg;
	char *tmp;

	if (!old_pwdvalue)
		return ;
	tmp = ft_strjoin("OLDPWD=", cur);
	arg = malloc(sizeof(char *) * 3);
	arg[0] = ft_strdup("export");
	arg[1] = tmp;
	arg[2] = NULL;
	ft_export(arg, info);
	free(arg[0]);
	free(arg[1]);
	free(arg);
}
static void change_pwd(char *pwd_value, t_info *info)
{
	char *tmp;
	char *cwd;
	char **arg;

	if (!pwd_value)
		return ;
	cwd = getcwd(NULL, 0);
	tmp = ft_strjoin("PWD=", cwd);
	arg = malloc(sizeof(char *) * 3);
	arg[0] = ft_strdup("export");
	arg[1] = tmp;
	arg[2] = NULL;
	ft_export(arg, info);
	free(arg[0]);
	free(arg[1]);
	free(arg);
}

int	ft_cd(char **arg, t_info *info)
{
	char	*cur;
	char	*pwd_value;
	char	*old_pwd_value;
	char	**env;

	env = change_list_to_arr_env(info);
	cur = getcwd(NULL, 0);
	get_both_pwd(env, &pwd_value, &old_pwd_value);
	if (run_chdir(arg, find_home(info)))
	{
		free(cur);
		return (1);
	}
	change_pwd(pwd_value, info);
	change_oldpwd(cur, old_pwd_value, info);
	free(cur);
	return (0);
}