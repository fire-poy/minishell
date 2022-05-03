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
		*s = (ajouter_au_string(s, index, len + 1, remplacer)); //remplazo y avanzo
		free (remplacer);
		return (*s);
	}
	env_var = ft_substr(*s, (unsigned int)*index + 1, len); //$ ou apres $???
	remplacer = chercher_env(liste, env_var);
	if (remplacer == NULL)
		return (ajouter_au_string(s, index, len + 1, "")); // remplazo, i avanza
	else
	{
		*s = (ajouter_au_string(s, index, ft_strlen(env_var) + 1, remplacer)); //remplazo y avanzo
		free (env_var);
		return (*s);
	}
}
//return string avec le $ remplacé deja, et i et mis sur la position du 2eme " pour continuer
// char	*remplacer_dollar(char **s, int *index, t_env *liste) 
// {
// 	int		len;
// 	char	*env_var;
// 	char	*remplacer;

// 	len = ft_strchr_set(*s + (unsigned int)*index + 1, 
//	" \t\n\v\f\r\"'");
// 	if (len == 0)
// 	{
// 		(*index)++;
// 		return (*s);
// 	}
// 	else
// 	{
// 		env_var = ft_substr(*s, (unsigned int)*index + 1, len); //$ ou apres $???
// 		remplacer = chercher_env(liste, env_var);
// 		// if (len == 1 && (*s)[(*index) + 1] == '?')
// 		// 	remplacer = ft_itoa(info->exit_status);
// 		if (remplacer == NULL)
// 			return (ajouter_au_string(s, index, len + 1, "")); // remplazo, i avanza
// 		else
// 		{
// 			*s = (ajouter_au_string(s, index, ft_strlen(env_var) + 1, remplacer)); //remplazo y avanzo
// 			free (env_var);
// 			return (*s);
// 		}
// 	}
// }

//on commence in the "
char	*chercher_and_replace_dollar(char **s, int *i, t_env *liste, t_info *info)
{
	(*i)++;
	while ((*s)[*i] && (*s)[*i] != '\"')
	{
		if((*s)[*i] == '$')//si hay dollar me fijo
			*s = remplacer_dollar(s, i, liste, info);
		else
			(*i)++;
	}
	return (*s); 	
}

//return char le quote simple ou double, selon trouvé
//rendre à partir de info l'index ou il'y a le premier ' et le 2eme a partir du premier
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

// void	chercher_dollar(char *s, t_str *info, t_env *liste)
// {
// 	int		i;
// 	int		len;
// 	char	*env_var;
// 	char	*remplacer;

// 	i = info->start;
// 	while (s[i])
// 	{
// 		if(s[i] == '$')//si hay dollar me fijo
// 		{
// 			len =	ft_strchr_set(s + i + 1, " \t\n\v\f\r\"");//busco siguiente espacio o fin dsp de dolar"
// 			if (len = 0)
// 				s = ajouter_au_string(s, &i, 1, "'$'"); // remplazo, i avanza
// 			else
// 			{
// 				env_var = ft_substr(s, &i, len); //$ ou apres $???
// 				remplacer = chercher_env(liste, env_var);
// 				if (remplacer == NULL)
// 					i += len + 1; //avanzo
// 				else
// 					s = ajouter_au_string(s, &i, ft_strlen(env_var), remplacer); //remplazo y avanzo
// 				free (env_var);
// 			}
// 		}
// 	}
// 	return (s); 	
// }
