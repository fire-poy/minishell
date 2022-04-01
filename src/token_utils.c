#include "../minishell.h"

t_token	*ft_create_tk(char *str)
{
	t_token	*adr;

	adr = malloc(sizeof(t_token));
	if (!adr)
		return (NULL);
	adr->info = ft_strdup(str);
	adr->next = NULL;
	return (adr);
}

// t_token	*ft_add_stack(t_token *a, char *str)
// {
// 	t_token	*new_n;

// 	new_n = ft_create_tk(str);
// 	if (new_n == NULL)
// 		return (NULL);
// 	a->size++;
// 	if (a->top == NULL)
// 	{
// 		a->top = new_n;
// 		return (a);
// 	}
// 	if (a->top->next == NULL)
// 	{
// 		a->bot = new_n;
// 		a->top->next = a->bot;
// 		a->bot->prev = a->top;
// 	}
// 	else
// 	{
// 		a->bot->next = new_n;
// 		new_n->prev = a->bot;
// 		a->bot = new_n;
// 	}
// 	return (a);
// }