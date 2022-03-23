# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpons <marvin@42lausanne.ch>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/23 14:30:30 by mpons             #+#    #+#              #
#    Updated: 2022/03/23 14:58:52 by mpons            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell 

CC			= gcc
CFLAGS		= -g -Wall -Wextra -Werror -fsanitize=address

OBJS		= ${SRC:.c=.o}

RM			= rm -f

#LIBFT_DIR	= ./libft

SRC 		= ./main.c\
			  
#INC			= -I./inc 
HOME		= ..
INC			= -I $(HOME)/homebrew/Cellar/readline/8.1.2/include

LIB			= -lreadline -L $(HOME)/homebrew/Cellar/readline/8.1.2/lib
#LIB			= ./libft/libft.a 

all: $(NAME)

$(NAME):	$(OBJS)
#			$(MAKE) -C $(LIBFT_DIR)
			$(CC) $(CFLAGS) -o $(NAME) $(INC) $(SRC) $(LIB)

clean:
#			$(MAKE) -C $(LIBFT_DIR) clean
		   	$(RM) $(OBJS)

fclean: 
#			$(MAKE) -C $(LIBFT_DIR) fclean
		   	$(RM) $(OBJS)
	   		$(RM) $(NAME)

re:			fclean all

.PHONY : all clean fclean re bonus

