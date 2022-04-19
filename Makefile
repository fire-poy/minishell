
NAME		= jo-minishell 

CC			= gcc
CFLAGS		= -g3 -Wall -Wextra -Werror -fsanitize=address

OBJS		= ${SRC:.c=.o}

RM			= rm -f

LIBFT_DIR	= ./libft

SRC 		= ./main.c\
			  ./src/prompt.c\
				./src/lexer.c\
				./src/error.c\
				./src/ft_strchr_set.c\
				./src/quotes_and_dollars.c\
				./src/other_dollars.c\
				./src/token_err_and_print.c\
				./src/token_get.c\
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
				./built_in/ctrl.c\
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

