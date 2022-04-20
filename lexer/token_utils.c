#include "../minishell.h"

//cherche string a_trouver dans la liste de ENV
char *chercher_env(t_env *liste, char *a_trouver)
{
	while (liste)
	{
		if (!ft_strncmp(a_trouver, liste->name , ft_strlen(a_trouver)))//si sont different je continue a chercher
			return (liste->content);
		else
			liste = liste->next;
	}
	return (NULL);
}
//ch_env debbug
// 	printf("liste name = %s\n", liste->name);
// 	printf("liste content = %s\n", liste->content);
// 	printf("a_trouver = %s\n", a_trouver);

void	printlist_tk(t_token *node)
{
	int	i;

	i = 0;
	while (node != NULL)
	{
		printf("%d %s = type %d\n", i, node->content, node->type);
		node = node->next;
		i++;
	}
}

// if (tk_i == start)
// 	dst[j++] = s[i];
//erase quotes
char	*erase_quotes(char *s)
{
	char	dst[1000];
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != '\'' && s[i] != '\"')//si il n'ya pas de quotes je copie et avance;
			dst[j++] = s[i++];
		else
		{
			c = s[i];
			i++;
			while (s[i] && s[i] != c)
				dst[j++] = s[i++];
			i++;
		}
	}
	dst[j] = '\0';
	return (ft_substr(dst, 0, ft_strlen(dst)));
}

void	erase_quotes_tk(t_token *node)
{
	int	i;

	i = 0;
	while (node != NULL)
	{
		node->content = erase_quotes(node->content);
		node = node->next;
		i++;
	}
}