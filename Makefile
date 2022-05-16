
NAME		= minishell 

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror -fsanitize=address -g3

OBJS		= ${SRC:.c=.o}

RM			= rm -f

LIBFT_DIR	= ./libft

SRC 		=   ./src/main.c\
				./src/error.c\
				./src/free.c\
				./lexer/lexer.c\
				./lexer/ft_strchr_set.c\
				./lexer/quotes_and_dollars.c\
				./lexer/other_dollars.c\
				./lexer/token_err.c\
				./lexer/token_utils.c\
				./lexer/token_get.c\
				./lexer/token_create.c\
				./parser/parser.c\
				./parser/split_token.c\
				./exec/access_1.c\
				./exec/access_2.c\
				./exec/exec_utils.c\
				./exec/exec_builtin.c\
				./exec/executeur.c\
				./exec/single_cmd.c\
				./exec/redirection_a.c\
				./exec/redirection_b.c\
				./exec/redirection_builtin.c\
				./exec/heredoc.c\
				./exec/pipe.c\
				./exec/pid.c\
				./exec/convert_env.c\
				./gnl/get_next_line.c\
				./built_in/env.c\
				./built_in/echo.c\
				./built_in/env_set.c\
				./built_in/env_list.c\
				./built_in/env_list_2.c\
				./built_in/pwd.c\
				./built_in/unset.c\
				./built_in/cd.c\
				./built_in/linked_list.c\
				./built_in/linked_list_sort.c\
				./built_in/export_support.c\
				./built_in/exit.c\
				./built_in/export.c\
				./built_in/ctrl.c\
				./built_in/ctrl_signal.c\

INC			= -I./gnl/get_next_line.h -I$(HOME)/.brew/opt/readline/include
LIB			= -lreadline -L$(HOME)/.brew/opt/readline/lib
LIBFT		= ./libft/libft.a 

all: $(NAME)

.c.o:
			${CC} ${CFLAGS} ${INC} -c $< -o ${<:.c=.o}
			
$(NAME):	$(OBJS)
			$(MAKE) -C $(LIBFT_DIR)
			$(CC) $(CFLAGS) -o $(NAME) $(INC) $(SRC) $(LIB) $(LIBFT)

clean:
			$(MAKE) -C $(LIBFT_DIR) clean
		   	$(RM) $(OBJS)

fclean: 
			$(MAKE) -C $(LIBFT_DIR) fclean
		   	$(RM) $(OBJS)
	   		$(RM) $(NAME)

re:			fclean all

.PHONY : all clean fclean re bonus
