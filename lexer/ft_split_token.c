#include "../minishell.h"

int	ft_space_out_of_quotes_found(char *s, int* start, char *set)
{
	int	i;

	i = *start;
	while (s[i] && ft_c_vs_charset(s[i], set))//trim espaces debut
			i++;
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')//si quotes Skip
			search_next_c(&s, &i, s[i]);
		if (ft_c_vs_charset(s[i], set))// si espaces MOT
		{
			*start = i;
			return (1);
		}
		i++;
	}
	if (s[i] == 0)		
		return (0);
	else
		*start = i;
	return (1);
}

int	ft_words(const char *s, char *set)
{	
	int	i;
	int	word;

	word = 0;
	i = 0;
	if (set == NULL)
		return (1);
	while (s[i])
	{	
		if (ft_space_out_of_quotes_found(s, &i, set))
		{
			word++;
		}
	}
	return (word);
}

int	ft_words(const char *s, char *set)
{	
	int	i;
	int	word;

	word = 0;
	i = 0;
	if (set == NULL)
		return (1);
	while (s[i])
	{	
		while (s[i] && ft_c_vs_charset(s[i], set))
			i++;
		if (!s[i])
			return (word);
		word++;
		while (s[i] && ft_c_vs_charset(s[i], set) == 0)//si ce n'est pas des espaces
		{
			if (s[i] == '\"' || s[i] == '\'')
				search_next_c(&s, &i, s[i]);
			i++;
		}
	}
	return (word);
}

void	ft_w_copy(char **tab, const char *s, char c)
{	
	int	i;
	int	j;
	int	debut;
	int	len;

	i = 0;
	j = 0;
	while (s[i])
	{	
		// while (s[i] && ft_c_vs_charset(s[i], set))
		// 	i++;
		debut = i;
		if (!s[i])
			break ;
		while (s[i] && ft_c_vs_charset(s[i], set) == 0)
		{
			if (s[i] == '\"' || s[i] == '\'')
				search_next_c(&s, &i, s[i]);
			i++;
		}
		while (s[i] && s[i] != c)
			i++;
		len = i - debut;
		tab[j] = malloc((len + 1) * sizeof(char));
		if (!tab[j])
			free (tab[j]);
		ft_strlcpy(tab[j], s + debut, len + 1);
		j++;
	}
	tab[j] = NULL;
}

char	**ft_split_token(const char *s, char c)
{
	char	**tab;
	int		words;

	if (!s)
		return (NULL);
	words = ft_words(s, c);
	tab = malloc((words + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	ft_w_copy(tab, s, c);
	tab[words] = NULL;
	return (tab);
}
/*
	printf("words = %d\n", ac);
int	main(int ac, char **av)
{
	char	sep;
	char	**split;
	int		i;

	(void)ac;
	i = 0;
	sep = ' ';
	split = ft_split(av[1], sep);
	while (split[i])
	{
		printf("%s\n", split[i]);
		i++;
	}
	free(split);
	return (0);
}
*/
