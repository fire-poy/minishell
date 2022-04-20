# define EMPTY 0
# define CMD 1
# define ARG 2
# define TRUNC 3
# define APPEND 4
# define INPUT 5
# define PIPE 6
# define END 7

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define SKIP 1
# define NOSKIP 0

// typedef struct s_line_info
// {
// 	char *redir_in; 
// 	int	redir_out;
// 	int	q_in; 
// 	int	q_out; 
// 	int	pipe_i;
// 	t_line info *next;
// }	t_line_info;

// struct s_token
// {
// 	char		*content;//cmd, infile, outfile, etc
// 	char		**tab_cmd;//split corrige
// 	int			cmd_index;//ordre de token 0 1 2 ca depend du pipe
// 	t_redir		*redir
// 	char		*export_name;// var name
// 	char		*export_content; // var content
// 	t_token	*next;
// };

// typedef struct s_cmd
// {
// 	char			*name;
// 	char			**args;
// 	char			*redirect_path;
// 	t_bash_token_id	redirect_id;
// 	struct s_cmd	*next;
// }	t_cmd;

// typedef struct s_shell
// {
// 	t_cmd	*cmds;
// 	char	*cmdline;
// 	char	*config;
// 	char	*working_dir;
// 	char	**envs;
// 	int		**pipes;
// 	int		*pids;
// 	int		num_cmds;
// 	int		num_pipes;
// 	int		exit_status;
// 	int		stop;
// }	t_shell;
