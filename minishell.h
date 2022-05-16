/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpons <mpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:19:48 by mpons             #+#    #+#             */
/*   Updated: 2022/05/16 12:03:18 by mpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"
# include "./gnl/get_next_line.h"
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
# include <signal.h>
# include <termios.h>
# include <sys/types.h> 
# include <sys/stat.h>
# include <errno.h>

/* terminal colors */
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define DEFAULT "\033[0m"

# define MSG_IS_DIRECTORY "is a directory"
# define MSG_IS_NOT_DIRECTORY "Not a directory"
# define MSG_FILE_NOT_FOUND "not such file or directory"
# define MSG_COMMAND_NOT_FOUND "command not found"
# define MSG_PERMISSION_DENIED "permission denied"

//Token
# define IN_FILE 0
# define OUT_FILE 1
# define APPEND 2
# define HEREDOC 3
# define BUILT_IN 4
# define CMD 5
# define PIPE 6

pid_t					g_pid[255];
typedef struct s_tk_info
{
	int		type;
	int		mem;
	int		i;
	int		st;
}	t_tk_info;

// chained list to extract env
typedef struct s_env	t_env;
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
	t_env	*new_node;
	t_env	*temp1;
	t_env	*temp2;
}	t_order;

// chained list with minishell input
typedef struct s_token	t_token;

struct s_token
{
	char		*content;
	int			type;
	int			cmd_index;
	int			in_index;
	int			out_index;
	int			export_vars;
	char		*export_name;
	char		*export_content;
	t_token		*next;
};

typedef struct s_info
{
	t_token	*tk;
	t_env	*liste;
	char	**envp;
	char	**full_cmd;
	char	***split_cmd;
	char	*input;
	int		err;
	int		q_in;
	int		q_out;
	int		cmd_i;
	int		q_cmd;
	int		pipe_i;
	int		**pipes;
	int		*pids;
	int		exit_status;
}	t_info;

//Error
void	err_msg(char *e, char *avant_e, int exit_status);
void	xperror(char *str);
void	print_join(char *s1, char *s2, int fd);
int		cmd_err(t_info *info, char *cmd, char *msg, int exit_status);

// redirection
void	redirect_in_out(t_info *info, int i);
int		find_last_in(t_token *tk, int i);
int		find_last_out(t_token *tk, int i);
int		get_q_in(t_token *tk, int i);
int		get_q_out(t_token *tk, int i);
int		redirect_in_bi(t_info *info, int i);
int		redirect_out_bi(t_info *info, int i);
int		redirect_in_out_bi(t_info *info, int i);
int		open_trunc_close(t_token *tk, int last_out);

// heredoc
int		create_heredocs(t_token *tk);
void	get_heredoc(char *flag, int i);
int		get_heredoc_fd(int cmd_index);
int		destroy_heredocs(int q_cmd);
char	*ft_strjoin_whit_int(char *s1, int n);

// pipe
int		create_pipes(t_info *info);
void	close_pipes(t_info *shell);
void	free_pipes(int **pipes, int q);

// pid
void	create_pids(t_info *shell);
void	wait_pids(t_info *shell);
void	wait_pids_heredoc(t_info *info, int i);

// EXEC
char	*ft_strjoin_whit_space(char *s1, char const *s2);
int		is_builtin(char *cmd);
int		exec_builtin(char **tab_cmd, t_info *liste, int fd);
char	*ft_get_last_arg(char *src);
int		slash_case(char *cmd, t_info *info, int i, char **path);
int		find_path(char *cmd, char **envp, t_env *liste);
void	execution_main(t_info *info);
int		exec_single_cmd(t_info *info);

// access
int		access_ok(char *cmd, t_info *info, char **path, int i);
int		is_invalid_command(t_info *info, char *cmd);

// free
void	free_tab(char **tab);
void	free_tokens(t_token **tk);
void	free_all(t_info *info);
void	free_info_simple(t_info *info);
char	*ft_strjoin_free(char *s1, char const *s2);
void	print_tab(char **tab);
void	print_tab_tab(char ***tab);

// parser
void	parser(t_info *info);
t_info	*init_info(t_env *liste, int last_exit, char *input);
// t_info	*init_info(t_env *liste, char **envp, int last_exit, char *input);

// lexer
int		ft_c_vs_charset(char c, const char *cs);
int		ft_strchr_set(const char *s, char *set);
int		ft_strchr_char(const char *s, char c);
int		search_next_c(char **s, int *debut, char c);
int		ft_charset_found(const char *s, int *start, char *set);
void	loop_prompt(t_env *liste);
int		lexer(char *input, t_info *info);
void	trimer(char *s, int *i);

// QUOTES
void	search_quotes_closed(char *str);
char	detect_and_check_quotes(char *s, int *i);
char	*search_and_replace_quotes(char **input, t_env *liste, t_info *info);
char	*chercher_env(t_env *liste, char *a_trouver);

char	*remplacer_dollar(char **s, int *index, t_env *liste, t_info *info);
char	*ajouter_au_string(char **s, int *i, int enlever, char *ajouter);
char	*chercher_and_replace_dollar(char **s, int *i,
			t_env *liste, t_info *info);
char	*remplacer_rest_of_dollar(char **s, t_env *liste, t_info *info);
char	*ajouter_au_string(char **s, int *i, int enlever, char *ajouter);
char	*ajouter_env(char **s, int *index, char *env_var, char *remplacer);

//TOKENS
void	explore_tokens_err(char **in, t_info *info);
void	search_next_token(char *s, int *start, int *tk_idx, int *type);
t_token	*get_tokens(char *s, t_token *tk);
void	printlist_tk(t_token *node);
char	**ft_split_from_charset(char *s, char *set);
void	tk_create_second(t_token **head, char **data, int type);
void	tk_create_node(t_token **head, char **data, int type);
int		set_type(char *s, int i, char c);
char	*erase_quotes(char *s);
void	erase_quotes_tk(t_token *node);
char	**ft_split_token(char *s, char *c);

//ENV
void	create_node(t_env **head, char *data);
void	printlist(t_env *node, int fd);
void	create_env_list(t_env **head, char **envp);
t_env	*ft_sort_list(t_env *head);
t_env	*ft_search_in_list(t_env **head, char *name);
t_env	*ft_create_node(char *name, char *value);
void	ft_add_to_list(t_env **head, t_env *newnode);
int		ft_delete_first_node(t_env **head, t_env *temp, char *name);
void	ft_delete_from_list(t_env **head, char *name);
int		ft_count_list(t_env **head);
void	err_exit(char *e, char *avant_e, int exit_status);
char	*ft_get_line(char *line);
char	*ft_get_name(char *line);
void	ft_env_set_content(t_env *env, char *name, char *new_content);
void	free_env(t_env **env);
void	ft_free_list(t_env **head_a);
void	env_create_node(t_env **head, char *data);
void	ft_free(char *head);
char	**get_env_tab(t_env *node);

// BUILT_IN
int		ft_builtin(t_token *token, t_env *liste);
void	ft_exit(char **tab_cmd, t_info *info);
int		ft_cd(char **argv, t_info *liste);
int		current_dir(int fd);
int		my_env(t_env *envp, int fd);
int		ft_echo(char **argv, int fd);
int		ft_equal(char *var);
int		ft_check_export_var(char *var);
int		ft_export(char **argv, t_env *liste, t_info *info, int fd);
void	ft_add_to_list2(t_env **head, t_env *newnode);
int		ft_unset(t_env **env, char *argv);
void	ft_replace_var(t_env **head, char *name, char *content, char *var);
void	ft_free_flag(t_info *info, t_env *liste, char *var);
void	ft_update_var(t_env *liste, t_info *info, char *var);
int		ft_info_init(t_info *info, char *var);
int		ft_check_c(char c, t_info *liste, int i, int fd);
int		str_compare(char *str1, char *str2);
int		array_length(char *arr[]);

// SIGNALS
void	signal_h(int signal);
void	ft_stop(char *input, int last_exit);
void	ft_stop2(char *input);
void	signal_q(int sig);
void	ft_get_pid(int i);
void	signal_here(int signal);
void	signal_2(int signal);
void	save_exit_status(t_info *shell);
void	init_signals(int redisplay);

#endif
