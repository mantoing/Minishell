/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 00:26:59 by suhkim            #+#    #+#             */
/*   Updated: 2022/11/18 04:08:35 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	parse(t_info *info, char *line)
{
	divide_space(&info->input, line);
	printf("cmd = %s\n", info->input.cmd);
	printf("opt = %s\n", info->input.opt);
	printf("arg = %s\n", info->input.arg);
	printf("after split cmd = %s\n",split_quote(info, info->input.cmd));
	printf("after split opt = %s\n",split_quote(info, info->input.opt));
	printf("after split arg = %s\n",split_quote(info, info->input.arg));
}
