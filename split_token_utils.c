/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 23:11:07 by suhkim            #+#    #+#             */
/*   Updated: 2023/01/19 23:12:12 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	parse_isspace(char c)
{
	if (c == '\t' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\v' || c == ' ')
		return (1);
	return (0);
}

int	not_env_arg(char c)
{
	if (!ft_isalnum(c) && c != '_' && c != '?' && c != '\'' && c != '\"')
		return (1);
	return (0);
}
