/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 00:21:58 by suhkim            #+#    #+#             */
/*   Updated: 2022/11/27 02:44:05 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	del_token(t_input *input, t_token *target, int *arg_size)
{
	t_token	*temp;

	if (!target)
		return ;
	temp = target;
	target->prev->next = target->next;
	target->next->prev = target->prev;
	free(temp);
	temp = NULL;
	input->token_size -= 1;
	*arg_size -= 1;
}
