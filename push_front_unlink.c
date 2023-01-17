/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_front_unlink.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 19:29:48 by suhkim            #+#    #+#             */
/*   Updated: 2023/01/18 06:42:29 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static void	push_front_first(t_unlink *unlink, t_unlink_name *new_unlink)
{
	new_unlink->next = &unlink->tail;
	unlink->head.next = new_unlink;
	new_unlink->prev = &unlink->head;
	unlink->tail.prev = new_unlink;
}

static void	push_front_common(t_unlink *unlink, t_unlink_name *new_unlink)
{
	new_unlink->next = unlink->head.next;
	unlink->head.next->prev = new_unlink;
	new_unlink->prev = &unlink->head;
	unlink->head.next = new_unlink;
}

int	push_front_unlink(t_unlink *unlink, char *str)
{
	t_unlink_name	*new_unlink;

	if (!unlink)
		return (0);
	new_unlink = malloc(sizeof(t_unlink));
	if (!new_unlink)
		exit(1);
	new_unlink->temp_file_name = ft_strdup(str);
	if (unlink->head.next == &unlink->tail)
		push_front_first(unlink, new_unlink);
	else
		push_front_common(unlink, new_unlink);
	unlink->temp_file_cnt += 1;
	return (1);
}
