#include "../minishell.h"

//erase quotes
// if (!dst)
		// return (NULL);
//erase quotes and envoie data to create node
char	*get_content_tk(char *s, int start, int *tk_i)
{
	char	dst[9999];
	int		i;
	int		j;
	char	c;

	i = start;
	j = 0;
	// if (*tk_i == -1)
	// 	*tk_i = ft_strlen(s);
	while (s[i] && i < *tk_i)
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

void	tk_create_node(t_token **head, char *data, int type)//, char c)
{
	t_token	*new_node;
	t_token	*last;

	last = *head;
	new_node = malloc(sizeof(t_token));
	new_node->content = data;
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

void	printlist_tk(t_token *node)
{
	while (node != NULL)
	{
		printf("%s = type ", node->content);
		printf("%d\n", node->type);
		node = node->next;
	}
}

t_token	*get_tokens(char *s, t_token *tk)
{
	int		i;
	int		start;
	int		type;
	char	c;
	char	*content;
	
	start = 0;
	tk = NULL;
	i =	search_next_token(s, &c, &type);
	if (i == -1)
		i = ft_strlen(s);
	content = get_content_tk(s, start, &i);
	tk_create_node(&tk, content, CMD);
	// while (search_next_token(s, &c, &type)
	// printf("GT token->content = %s\n", tk->content);
	return (tk);
}

























