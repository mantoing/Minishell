/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_back_unlink.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 22:17:19 by suhkim            #+#    #+#             */
/*   Updated: 2023/01/18 06:51:02 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static void	push_back_first(t_unlink *unlink, t_unlink_name *new_unlink)
{
	new_unlink->prev = &unlink->head;
	new_unlink->next = &unlink->tail;
	unlink->head.next = new_unlink;
	unlink->tail.prev = new_unlink;
}

static void	push_back_common(t_unlink *unlink, t_unlink_name *new_unlink)
{
	new_unlink->prev = unlink->tail.prev;
	new_unlink->next = &unlink->tail;
	unlink->tail.prev->next = new_unlink;
	unlink->tail.prev = new_unlink;
}

int	push_back_unlink(t_unlink *unlink, char *str)
{
	t_unlink_name	*new_unlink;

	if (!unlink)
		return (0);
	new_unlink = malloc(sizeof(t_unlink));
	if (!new_unlink)
		exit(1);
	new_unlink->temp_file_name = str;
	if (unlink->tail.prev == &unlink->head)
		push_back_first(unlink, new_unlink);
	else
		push_back_common(unlink, new_unlink);
	unlink->temp_file_cnt += 1;
	return (1);
}
