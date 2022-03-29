/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpons <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:21:36 by mpons             #+#    #+#             */
/*   Updated: 2021/12/21 18:05:19 by mpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstadd_front(t_list **alst, t_list *new)
{
	if (*alst)
		new->next = *alst;
	*alst = new;
}	
/*
	alst = adresse du pointeur vers le premier element de la liste
	new  = adresse du pointeur vers l'element a rajouter a la liste.

	ajoute l'elemnt new au debut de la liste
*/
