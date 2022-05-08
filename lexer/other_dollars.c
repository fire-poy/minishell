/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_dollars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpons <mpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:54:53 by mpons             #+#    #+#             */
/*   Updated: 2022/05/04 19:51:43 by mpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//index dollar, combien a enlever , quoi ajouter
char	*ajouter_au_string(char **s, int *i, int enlever, char *ajouter)
{
	char	*debut;
	char	*fin;
	int		e;

	e = *i;
	debut = ft_substr(*s, 0, e);
	fin = ft_substr(*s, *i + enlever, 1000);
	debut = ft_strjoin_free(debut, ajouter);
	debut = ft_strjoin_free(debut, fin);
	free (fin);
	free (*s);
	*s = NULL;
	*i += ft_strlen(ajouter);
	return (debut);
}

char	*ajouter_env(char **s, int *index, char *env_var, char *remplacer)
{
	*s = (ajouter_au_string(s, index, ft_strlen(env_var) + 1, remplacer));
	free (env_var);
	return (*s);
}

//return 0 si en arrive a \0 sans trouver le char
//avance le idx au suivante char trouve apres l'envoie
int	search_next_c(char **s, int *debut, char c)
{
	(*debut)++;
	(*debut) += ft_strchr_char(*s + *debut, c);
	if ((*s)[*debut] == 0)
		return (0);
	else
		return (1);
}

char	*remplacer_rest_of_dollar(char **s, t_env *liste, t_info *info)
{
	int		i;

	i = 0;
	while ((*s)[i])
	{	
		if ((*s)[i] == '\"' || (*s)[i] == '\'')
			search_next_c(s, &i, (*s)[i]);
		if ((*s)[i] == '$')
			*s = remplacer_dollar(s, &i, liste, info);
		else
			i++;
	}
	return (*s);
}
