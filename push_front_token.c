/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_front_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 19:29:48 by suhkim            #+#    #+#             */
/*   Updated: 2023/01/18 06:42:20 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static void	push_front_first(t_input *input, t_token *new_token)
{
	new_token->next = &input->tail;
	input->head.next = new_token;
	new_token->prev = &input->head;
	input->tail.prev = new_token;
}

static void	push_front_common(t_input *input, t_token *new_token)
{
	new_token->next = input->head.next;
	input->head.next->prev = new_token;
	new_token->prev = &input->head;
	input->head.next = new_token;
}

int	push_front_token(t_input *input, char *str)
{
	t_token	*new_token;

	if (!input)
		return (0);
	new_token = malloc(sizeof(t_input));
	if (!new_token)
		exit(1);
	new_token->token = str;
	if (input->head.next == &input->tail)
		push_front_first(input, new_token);
	else
		push_front_common(input, new_token);
	input->token_size += 1;
	return (1);
}
