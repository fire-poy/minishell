
NAME		= jo-minishell 

CC			= gcc
CFLAGS		= -g3 -Wall -Wextra -Werror -fsanitize=address

OBJS		= ${SRC:.c=.o}

RM			= rm -f

LIBFT_DIR	= ./libft

SRC 		= ./src/main.c\
				./src/error.c\
				./lexer/lexer.c\
				./lexer/ft_strchr_set.c\
				./lexer/quotes_and_dollars.c\
				./lexer/other_dollars.c\
				./lexer/token_err.c\
				./lexer/token_utils.c\
				./lexer/token_get.c\
				./lexer/token_create.c\
				./parser/parser.c\
				./exec/executeur.c\
				./built_in/env.c\
				./built_in/echo.c\
				./built_in/env_list.c\
				./built_in/export.c\
				./built_in/unset.c\
				./built_in/linked_list.c\
				./built_in/linked_list_sort.c\
				./built_in/pwd.c\
				./built_in/cd.c\
				./built_in/exit.c\
				./built_in/builtin.c\
				./built_in/export_support.c\
				#./built_in/pwd.c\
			  
HOME		= ..
INC			= -I./inc -I $(HOME)/homebrew/Cellar/readline/8.1.2/include

LIB			= -lreadline -L $(HOME)/homebrew/Cellar/readline/8.1.2/lib
LIBFT		= ./libft/libft.a 

all: $(NAME)

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

