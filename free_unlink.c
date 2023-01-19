/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_unlink.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeywon <jaeywon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 18:18:50 by suhkim            #+#    #+#             */
/*   Updated: 2023/01/19 16:22:42 by jaeywon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	free_unlink(t_unlink *unlink)
{
	t_unlink_name	*temp;

	if (!unlink || !unlink->temp_file_cnt)
		return ;
	temp = unlink->head.next;
	while (unlink->temp_file_cnt)
	{
		temp = unlink->tail.prev;
		temp->prev->next = &unlink->tail;
		unlink->tail.prev = temp->prev;
		unlink->temp_file_cnt -= 1;
		free(temp->temp_file_name);
		free(temp);
	}
}
