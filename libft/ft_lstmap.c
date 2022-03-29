/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpons <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 20:16:21 by mpons             #+#    #+#             */
/*   Updated: 2021/12/21 18:05:16 by mpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*dst;
	t_list	*new_block;

	if (!lst)
		return (NULL);
	dst = NULL;
	while (lst)
	{
		new_block = ft_lstnew(f(lst->content));
		if (!new_block)
			ft_lstclear(&new_block, (*del));
		else
			ft_lstadd_back(&dst, new_block);
		lst = lst->next;
	}
	return (dst);
}
//il manque un break ; ou un return NULL ?
