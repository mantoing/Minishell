/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 18:18:50 by suhkim            #+#    #+#             */
/*   Updated: 2022/11/24 18:31:19 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	free_token(t_input *input)
{
	t_token	*temp;

	if (!input || !input->token_size)
		return ;
	temp = input->head.next;
	while (input->token_size)
	{
		temp = input->tail.prev;
		temp->prev->next = &input->tail;
		input->tail.prev = temp->prev;
		input->token_size -= 1;
		free(temp);
	}
}


