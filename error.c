/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:36:54 by jaeywon           #+#    #+#             */
/*   Updated: 2023/01/12 02:11:39 by jaeywon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

//:3개가 나와야 할 경우 ex)ls: an: No such file or directory
void	print_err(char *s1, char *s2, char *s3)
{
	ft_putstr_fd(s1, STDERR_FILENO);
	if (!s1)
		exit(2);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(s2, STDERR_FILENO);
	if (!s2)
		exit(2);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(s3, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

// 에러 넘버만 가지기 위한 코드
void	print_err_with_exit_num(char *s1, char *s2, char *s3, char exit_code)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(s1, STDERR_FILENO);
	if (!s2)
		exit(2);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(s2, STDERR_FILENO);
	if (!s3)
		exit(2);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(s3, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit_code = 1;
	// g_errnum = exit_code;
}