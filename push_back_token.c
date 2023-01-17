/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_back_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 22:17:19 by suhkim            #+#    #+#             */
/*   Updated: 2023/01/18 06:41:41 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static void	push_back_first(t_input *input, t_token *new_token)
{
	new_token->prev = &input->head;
	new_token->next = &input->tail;
	new_token->pipe = 0;
	new_token->heredoc = 0;
	new_token->redir_r = 0;
	new_token->redir_l = 0;
	new_token->append = 0;
	input->head.next = new_token;
	input->tail.prev = new_token;
}

static void	push_back_common(t_input *input, t_token *new_token)
{
	new_token->prev = input->tail.prev;
	new_token->next = &input->tail;
	new_token->pipe = 0;
	new_token->heredoc = 0;
	new_token->redir_r = 0;
	new_token->redir_l = 0;
	new_token->append = 0;
	input->tail.prev->next = new_token;
	input->tail.prev = new_token;
}

int	push_back_token(t_input *input, char *str)
{
	t_token	*new_token;

	if (!input)
		return (0);
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		exit(1);
	new_token->token = str;
	if (input->tail.prev == &input->head)
		push_back_first(input, new_token);
	else
		push_back_common(input, new_token);
	input->token_size += 1;
	return (1);
}
