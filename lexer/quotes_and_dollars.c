/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_and_dollars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpons <mpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:54:47 by mpons             #+#    #+#             */
/*   Updated: 2022/05/04 20:03:39 by mpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// return string avec le $ remplacé deja, 
// i et mis sur la position du 2eme " pour continuer
char	*remplacer_dollar(char **s, int *index, t_env *liste, t_info *info)
{
	int		len;
	char	*env_var;
	char	*remplacer;

	len = ft_strchr_set(*s + (unsigned int)*index + 1, " \t\n\v\f\r\"'");
	if (len == 0)
	{
		(*index)++;
		return (*s);
	}
	else if (len == 1 && (*s)[(*index) + 1] == '?')
	{
		remplacer = ft_itoa(info->exit_status);
		*s = (ajouter_au_string(s, index, len + 1, remplacer));
		free (remplacer);
		return (*s);
	}
	env_var = ft_substr(*s, (unsigned int)*index + 1, len);
	remplacer = chercher_env(liste, env_var);
	if (remplacer == NULL)
	{
		free (env_var);
		return (ajouter_au_string(s, index, len + 1, ""));
	}
	return (ajouter_env(s, index, env_var, remplacer));
}

//on commence in the "
char	*chercher_and_replace_dollar(char **s, int *i,
			t_env *liste, t_info *info)
{
	(*i)++;
	while ((*s)[*i] && (*s)[*i] != '\"')
	{
		if ((*s)[*i] == '$')
			*s = remplacer_dollar(s, i, liste, info);
		else
			(*i)++;
	}
	return (*s);
}

//return char le quote simple ou double, selon trouvé
//rendre à partir de info l'index ou il'y a le premier '
//et le 2eme a partir du premier
//check si sont le quotes fermes
char	detect_and_check_quotes(char *s, int *idx)
{
	char	c;
	int		i;

	*idx += ft_strchr_set(s + *idx, "'\"");
	i = *idx;
	c = s[i];
	if (c)
	{
		if (search_next_c(&s, &i, c) == 0)
			c = 'e';
	}
	return (c);
}

char	*search_and_replace_quotes(char **input, t_env *liste, t_info *info)
{
	char	c;
	int		i;

	i = -1;
	while ((*input)[++i])
	{
		c = 0;
		c = detect_and_check_quotes(*input, &i);
		if (c == '\'')
			search_next_c(input, &i, c);
		if (c == '\"')
			*input = chercher_and_replace_dollar(input, &i, liste, info);
		if (c == 0)
			return (*input);
		if (c == 'e')
			return (NULL);
	}
	return (*input);
}
