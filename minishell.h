#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "./libft/libft.h"
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>

// int	g_exit_status = 0;

//Error
void	err_msg(char *e, char *avant_e, int exit_status);
void	xperror(char *str);
void	print_join(char *s1, char *s2, int fd);

// chained list with minishell input


// chained list to extract env
typedef struct s_env t_env;

struct s_env
{
	char	*initial_env;
	char	*name;
	char	*content;
	t_env	*next;
};

// chained list to order export list

typedef struct s_order
{
	t_env	*newNode;
	t_env	*temp1;
	t_env	*temp2;
}	t_order;

//Token

#define IN_FILE 0
#define OUT_FILE 1
#define APPEND 2
#define HEREDOC 3
#define BUILT_IN 4
#define CMD 5
#define PIPE 6

typedef struct s_token t_token;

struct s_token
{
	char		*content;//cmd, infile, outfile, etc
	char		**tab_cmd;//on fait le tab dans le pipe?
	int			type;
	int			tk_index;//ordre de token
	int			cmd_index;//nro de commande
	char		*export_name;// var name
	char		*export_content; // var content
	t_token	*next;
};

//struct pour garder des info pour remplacer le quotes
typedef struct s_str t_str;

struct s_str
{
	int		start;
	int		len;
};

// lexer
int		ft_c_vs_charset(char c, const char *cs);
int		ft_strchr_set(const char *s, char *set);
int		ft_strchr_char(const char *s, char c);
int		search_next_c(char **s, int *debut, char c);
int		ft_charset_found(const char *s, int* start, char *set);


void	loop_prompt(int ac, char **av, char **envp);
int		lexer(char *input, t_env *liste, t_token *tk);
void	trimer (char *s, int *i);

// QUOTES
void	search_quotes_closed(char *str);
char	detect_and_check_quotes(char *s, int *i);
char	*search_and_replace_quotes(char **input, t_env *liste);
char	*chercher_env(t_env *liste, char *a_trouver);
char	*remplacer_dollar(char **s, int *index, t_env *liste); 
char	*ajouter_au_string(char **s, int *i, int enlever, char *ajouter);
char	*chercher_and_replace_dollar(char **s, int *i, t_env *liste);
char	*remplacer_rest_of_dollar(char **s, t_env *liste);

//TOKENS
void	explore_tokens_err(char **in);
void	search_next_token(char *s, int *start, int *tk_idx, int *type);
t_token	*get_tokens(char *s, t_token *tk);
void	printlist_tk(t_token *node);


//ENV
void	create_node(t_env **head, char *data);
void	printlist(t_env *node);
void	create_env_list(t_env **head, char **envp);
t_env	*ft_sort_list(t_env *head);
t_env	*ft_search_in_list(t_env **head, char *name);
t_env	*ft_create_node(char *name, char *value);
void	ft_add_to_list(t_env **head, t_env *newnode);
int		ft_delete_first_node(t_env **head, t_env *temp, char *name);
void	ft_delete_from_list(t_env **head, char *name);
int		ft_count_list(t_env **head);
void  err_exit(char *e, char *avant_e, int exit_status);
char	*ft_get_line(char *line);
char	*ft_get_name(char *line);
void	ft_env_set_content(t_env *env, char *name, char *new_content);

// BUILT_IN

int		ft_builtin(t_token *token, t_env *liste);
void	ft_exit(t_token *liste_args);
void	ft_cd(char **argv, t_env *env);
int		current_dir(void);
int		my_env(t_env *envp);
int		ft_echo(char **argv);
int		ft_equal(char *var);
int		ft_check_export_var(char *var);
t_env	*ft_export(char **argv, t_env *liste, t_token *token);
void	ft_add_to_list2(t_env **head, t_env *newnode);
void	ft_unset(t_env **env, char **argv);

#endif