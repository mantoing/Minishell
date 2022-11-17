/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 19:30:27 by suhkim            #+#    #+#             */
/*   Updated: 2022/03/27 16:35:49 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*temp;

	if (!lst || !f)
		return (0);
	newlst = ft_lstnew(f(lst->content));
	if (!newlst)
		return (0);
	lst = lst->next;
	temp = newlst;
	while (lst)
	{
		temp->next = ft_lstnew(f(lst->content));
		if (!(temp->next))
		{
			ft_lstclear(&newlst, del);
			return (0);
		}
		temp = temp->next;
		lst = lst->next;
	}
	return (newlst);
}
