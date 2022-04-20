#include "../minishell.h"

// return 1 si trouve `metachar`
// return -1 s'il n'y a pas de meta
// avance *idx jusq meta si trouve
// sinon avance jusq strlen
void	search_next_token(char *s, int *start, int *tk_idx, int *type)
{
	int	i;

	if (*start != 0)
	{
		if ((s[(*start) + 1] == '<' || s[(*start) + 1] == '>') && s[(*start)] != '|')
			(*start) += 2;
		else
			(*start)++;
	}
	i = *start;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')//si hay quotes las salteo
			search_next_c(&s, &i, s[i]);
		if (s[i] == '<' || s[i] == '>' || s[i] == '|')//si encuentro token 
		{
			*type = set_type(s, i, s[i]);
			*tk_idx = i;
			return ;
		}
		i++;
	}
	*type = -1;
	*tk_idx = i;
}

//trime spaces and send data to create node
char	*get_content_tk(char *s, int start, int tk_i)
{
	char	dst[1000];
	int		i;
	int		j;

	i = start;
	j = 0;
	while (s[i] && i < tk_i)
		dst[j++] = s[i++];
	dst[j] = '\0';
	return (ft_strtrim(dst, " \t"));
	// return (ft_substr(dst, 0, ft_strlen(dst)));
}



char	*get_first(char *s, int *st, int *i, int *mem, int *type)
{
	int add;

	if (*type == 0 || *type == 1)
		add = 1;
	if (*type == 2)
		add = 2;
	(*st)+= add;
	*mem = *type;
	// printf ("type = %d\n", *type);
	search_next_token(s, st, i, type);
	return (get_content_tk(s, (*st) -1, *i));
}

// while (search_next_token(s, &st, &i, &type) != -1)//avance i jusqu'au token et st a la pos apres du token si != 0
//fais un truc generic et apres un pour le premier
// tk = NULL;
//marche
t_token	*get_tokens(char *s, t_token *tk)
{
	char	*content;
	int		type;
	int		mem;
	int		i;
	int		st;
	
	st = 0;
	i = 0;
	while ((unsigned long)i < ft_strlen(s))
	{
		search_next_token(s, &st, &i, &type); //avance i jusqu'au token et st a la pos apres du token si != 0. ou \0
		// printf("apres search st %d \n", st);
		// printf("apres search i %d \n", i);
		if (i == 0)
			content = get_first(s, &st, &i, &mem, &type);		
		else
			content = get_content_tk(s, st , i);
		if (st == 0)
			tk_create_node(&tk, &content, CMD);
		else
			tk_create_node(&tk, &content, mem);
		// printf("%d\n", i);
		st = i;
		mem = type;
	}
	return (tk);
}

// t_token	*get_tokens(char *s, t_token *tk)
// {
// 	char	*content;
// 	int		type;
// 	int		mem;
// 	int		i;
// 	int		st;
	
// 	tk = NULL;
// 	st = 0;
// 	while (1)
// 	{
// 		search_next_token(s, &st, &i, &type); //avance i jusqu'au token et st a la pos apres du token si != 0. ou \0
// 		if (i == st)
// 			i++;
// 		content = get_content_tk(s, st , i);
// 		if (st == 0)
// 			tk_create_node(&tk, &content, CMD);
// 		else
// 			tk_create_node(&tk, &content, mem);
// 		st = i;
// 		mem = type;
// 		if ((unsigned long)i == ft_strlen(s))
// 			break;
// 	}
// 	return (tk);
// }

// void	split_token(t_token *tk);
// {
// 	char **tab;

// 	while (tk)
// 	{
// 		if (tk->type == 0 || tk->type == 1)//si sont different je continue a chercher
// 		{
// 			tab = ft_split(tk->content);
// 			if(tab[1] != NULL)

// 		}
// 		else
// 			tk = tk->next;
// 	}
// 	return (NULL);
// }

// name
// A word consisting solely of letters, numbers, and underscores, 
// beginning with a letter or underscore. 
// Names are used as shell variable and function names. 
// Also referred to as an identifier.

// token
// A sequence of characters considered a single unit by the shell. 
// It is either a word or an operator.

// metacharacter
// A character that, when unquoted, separates words. 
// A metacharacter is a space, tab, newline, 
// or one of the following characters: ‘|’, ‘&’, ‘(’, ‘)’, ‘<’, or ‘>’. ‘;’, 

//erase quotes and envoie data to create node
// char	*get_content_tk(char *s, int start, int tk_i)
// {
// 	char	dst[1000];
// 	int		i;
// 	int		j;
// 	char	c;

// 	i = start;
// 	j = 0;
// 	// if (tk_i == start)
// 	// 	dst[j++] = s[i];
// 	while (s[i] && i < tk_i)
// 	{
// 		if (s[i] != '\'' && s[i] != '\"')//si il n'ya pas de quotes je copie et avance;
// 			dst[j++] = s[i++];
// 		else
// 		{
// 			c = s[i];
// 			i++;
// 			while (s[i] && s[i] != c)
// 				dst[j++] = s[i++];
// 			i++;
// 		}
// 	}
// 	dst[j] = '\0';
// 	return (ft_strtrim(dst, " \t"));
// 	// return (ft_substr(dst, 0, ft_strlen(dst)));
// }






