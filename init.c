/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 22:58:23 by suhkim            #+#    #+#             */
/*   Updated: 2022/11/17 22:59:19 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	init_stack(t_stack *stack)
{
	stack->head.next = &stack->tail;
	stack->tail.prev = &stack->head;
}
