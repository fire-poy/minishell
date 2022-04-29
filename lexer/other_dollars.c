#include "../minishell.h"

//return 0 si en arrive a \0 sans trouver le char
//avance le idx au suivante char trouve apres l'envoie
int	search_next_c(char **s, int *debut, char c)
{
	(*debut)++;
	(*debut)+= ft_strchr_char(*s + *debut, c);
	if((*s)[*debut] == 0)
		return (0);
	else
	return (1);
}

char *remplacer_rest_of_dollar(char **s, t_env *liste, t_info *info)
{
	int		i;

	i = 0;
	while ((*s)[i])
	{	
		if((*s)[i] == '\"' || (*s)[i] == '\'')
			search_next_c(s, &i, (*s)[i]);
		if((*s)[i] == '$')//si hay dollar me fijo
			*s = remplacer_dollar(s, &i, liste, info);
		else
			i++;
	}
	return (*s); 	
}

// char *remplacer_rest_of_dollar(char **s, t_env *liste)
// {
// 	char	c[2];
// 	int		i;

// 	i = 0;
// 	while ((*s)[i])
// 	{
// 		if((*s)[i] == '\"' || (*s)[i] == '\'' )
// 		{
// 			c[0] = (*s)[i];
// 			c[1] = '\0';
// 			i++;
// 			i += ft_strchr_set(*s + i, c);
// 		}
// 		if((*s)[i] == '$')//si hay dollar me fijo
// 			*s = remplacer_dollar(s, &i, liste);
// 		else
// 			i++;
// 	}
// 	return (*s); 	
// }
