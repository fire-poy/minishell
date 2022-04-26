# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpons <mpons@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/23 14:30:30 by mpons             #+#    #+#              #
#    Updated: 2022/04/26 16:02:21 by mpons            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell 

CC			= gcc
CFLAGS		= -g3 -Wall -Wextra -Werror -fsanitize=address

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
				./exec/exec_utils.c\
				./exec/exec_builtin.c\
				./exec/executeur.c\
				./exec/single_cmd.c\
				./exec/redirection_a.c\
				./exec/redirection_b.c\
				./exec/pipe.c\
				./exec/pid.c\
				./gnl/get_next_line.c\
				./built_in/env.c\
				./built_in/echo.c\
				./built_in/env_list.c\
				./built_in/pwd.c\
				./built_in/unset.c\
				./built_in/cd.c\
				./built_in/linked_list.c\
				./built_in/linked_list_sort.c\
				./built_in/export_support.c\
				./built_in/exit.c\
				./built_in/export.c\
				./built_in/ctrl.c\
				# ./built_in/builtin.c\
			  
#INC			= -I./gnl/get_next_line.h -I $(HOME)/homebrew/Cellar/readline/8.1.2/include
#LIB			= -lreadline -L $(HOME)/homebrew/Cellar/readline/8.1.2/lib
#LIBFT		= ./libft/libft.a 

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

