#include "../minishell.h"

void	tk_create_node(t_token **head, char **data, int type)//, char c)
{
	t_token	*new_node;
	t_token	*last;

	last = *head;
	new_node = malloc(sizeof(t_token));
	new_node->content = *data;
	new_node->type = type;
	new_node->next = NULL;
	// if (type == -1)
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
	return ;
}

int	set_type(char *s, int i, char c)
{
	int	type;

	if (c == '<')
		type = IN_FILE;
	if (c == '<' && s[i + 1] == '<')
		type = HEREDOC;
	if (c == '>')
		type = OUT_FILE;
	if (c == '>' && s[i + 1] == '>')
		type = APPEND;
	if (c == '|')
		type = PIPE;
	return (type);
}

// return 1 si trouve `metachar`
// return -1 s'il n'y a pas de meta
// avance *idx jusq meta si trouve
// sinon avance jusq strlen
void	search_next_token(char *s, int *start, int *tk_idx, int *type)
{
	int	i;

	if (*start != 0)
	{
		if (s[(*start) + 1] == '<' || s[(*start) + 1] == '>')
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

//erase quotes and envoie data to create node
char	*get_content_tk(char *s, int start, int tk_i)
{
	char	dst[1000];
	int		i;
	int		j;
	char	c;

	i = start;
	j = 0;
	while (s[i] && i < tk_i)
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
	return (ft_strtrim(dst, " \t"));
	// return (ft_substr(dst, 0, ft_strlen(dst)));
}


	// while (search_next_token(s, &st, &i, &type) != -1)//avance i jusqu'au token et st a la pos apres du token si != 0
//fais un truc generic et apres un pour le premier
t_token	*get_tokens(char *s, t_token *tk)
{
	char	*content;
	int		type;
	int		mem;
	int		i;
	int		st;
	
	tk = NULL;
	st = 0;
	while (1)
	{
		search_next_token(s, &st, &i, &type); //avance i jusqu'au token et st a la pos apres du token si != 0. ou \0
		content = get_content_tk(s, st, i);
		// printf("type = %d\n", type);
		if (st == 0)
			tk_create_node(&tk, &content, CMD);
		else
			tk_create_node(&tk, &content, mem);
		st = i;
		mem = type;
		if ((unsigned long)i == ft_strlen(s))
			break;
	}
	return (tk);
}

	// type = set_type(s, i, s[i]);
	// if (search_next_token(s, &i, &type) == -1)
	// {
	// 	i =	search_next_token(s, &c, &type);
	// 	if (i == -1)
	// 	i = ft_strlen(s);


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
















