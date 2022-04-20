#include "../minishell.h"

//search charset a partir du start, avance l'address si trouve le chset;
//return 0 si ne trouve pas, 1 en succes
int	ft_space_out_quotes_found(char *s, int* start, char *set)
{
	int	i;

	i = *start;
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
			search_next_c(&s, &i, s[i]);
		if (ft_c_vs_charset(s[i], set))
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

//free s == content
char	**ft_split_from_charset(char *s, char *set)
{
	int	i;
	char **tab_ch;

	i = 0;
	if (ft_space_out_quotes_found(s, &i, set))
	{
		tab_ch = malloc(3 * sizeof(char *));
		tab_ch[0] = ft_substr(s, 0, i);
		while (s[i] == ' ' || s[i] == '\t')
			i++;
		tab_ch[1] = ft_substr(s, i, (int)ft_strlen - i);
		tab_ch[2] = NULL;
		return (tab_ch);
	}
	else
		return (NULL);
}

void	tk_create_second(t_token **head, char **data, int type)
{
	t_token	*new_node_a;
	t_token	*new_node_b;
	t_token	*last;
	char	**split_data;

	last = *head;
	new_node_a = malloc(sizeof(t_token));
	new_node_b = malloc(sizeof(t_token));
	split_data = ft_split_from_charset(*data, " \t");
	new_node_a->content = split_data[0];
	new_node_a->type = type;
	new_node_a->next = new_node_b;
	new_node_b->content = split_data[1];
	new_node_b->type = CMD;
	new_node_b->next = NULL;
	if (*head == NULL)
	{
		*head = new_node_a;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new_node_a;
	return ;
}

void    tk_create_node(t_token **head, char **data, int type)//, char c)
{
    t_token *new_node;
    t_token *last;
	int	i;

	i = 0;
	if ((type == 0 || type == 1 || type == 2 || type == 3) 
		&& ft_space_out_quotes_found(*data, &i, " \t"))
	{
		tk_create_second(head, data, type);
		return ;
	}
    last = *head;
    new_node = malloc(sizeof(t_token));
    new_node->content = *data;
    new_node->type = type;
    new_node->next = NULL;
    if (*head == NULL)
    {
        *head = new_node;
        return ;
    }
    while (last->next != NULL)
        last = last->next;
    last->next = new_node;
}
    // if (type == -1)

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
