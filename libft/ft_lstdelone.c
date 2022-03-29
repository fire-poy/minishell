/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpons <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 19:01:41 by mpons             #+#    #+#             */
/*   Updated: 2021/12/21 18:09:02 by mpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!del)
		return ;
	if (lst)
	{
		(*del)(lst->content);
		free(lst);
	}
}
/*
 * del = calloc p.ex
 * if (!lst || !del)
 * 	return ;
	1 l'element a free
	2 l'adresse de la fonction permettant de supprimer le contenu de l'element.
*/
