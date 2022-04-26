# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhermon- <jhermon-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/23 14:30:30 by mpons             #+#    #+#              #
#    Updated: 2022/04/26 15:38:39 by jhermon-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell 

CC			= gcc
CFLAGS		= -g -Wall -Wextra -Werror -fsanitize=address

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
			  
INC			= -I./gnl/get_next_line.h -I$(HOME)/.brew/opt/readline/include
LIB			= -lreadline -L$(HOME)/.brew/opt/readline/lib
LIBFT		= ./libft/libft.a 

all: $(NAME)

.c.o:
			${CC} ${CFLAGS} ${INC} -c $< -o ${<:.c=.o}

$(NAME):	$(OBJS)
			$(MAKE) -C $(LIBFT_DIR)
			$(CC) $(CFLAGS) $(INC) $(SRC) $(LIB) $(LIBFT) -o $(NAME)

clean:
			$(MAKE) -C $(LIBFT_DIR) clean
		   	$(RM) $(OBJS)

fclean: 
			$(MAKE) -C $(LIBFT_DIR) fclean
		   	$(RM) $(OBJS)
	   		$(RM) $(NAME)

re:			fclean all

.PHONY : all clean fclean re bonus

# SHELL = /bin/sh

# CFLAGS := ${CFLAGS}

# CC     ?= gcc
# LD     ?= gcc

# INC_FLAGS := -Ilibft -Ignl/
# LIBS := -Llibft -lft -lreadline

# UNAME = $(shell uname -s)
# ifeq ($(UNAME), Linux)
# #	NPROC := $(shell nproc)
# else
# #	NPROC := $(shell sysctl -n hw.ncpu)
# 	INC_FLAGS += -I$(HOME)/.brew/opt/readline/include
#     LIBS += -L$(HOME)/.brew/opt/readline/lib
# endif

# MAKEFLAGS += --output-sync=target
# MAKEFLAGS += --no-print-directory

# NAME ?= minish

# BUILD_DIR ?= ./build
# SRC_DIRS 	= src/main.c\
# 				src/error.c\
# 				src/free.c\
# 				lexer/lexer.c\
# 				lexer/ft_strchr_set.c\
# 				lexer/quotes_and_dollars.c\
# 				lexer/other_dollars.c\
# 				lexer/token_err.c\
# 				lexer/token_utils.c\
# 				lexer/token_get.c\
# 				lexer/token_create.c\
# 				parser/parser.c\
# 				exec/exec_utils.c\
# 				exec/exec_builtin.c\
# 				exec/executeur.c\
# 				exec/single_cmd.c\
# 				exec/redirection_a.c\
# 				exec/redirection_b.c\
# 				gnl/get_next_line.c\
# 				built_in/env.c\
# 				built_in/echo.c\
# 				built_in/env_list.c\
# 				built_in/pwd.c\
# 				built_in/unset.c\
# 				built_in/cd.c\
# 				built_in/linked_list.c\
# 				built_in/linked_list_sort.c\
# 				built_in/export_support.c\
# 				built_in/exit.c\
# 				built_in/export.c\
# 				built_in/ctrl.c\
# 				# ./built_in/builtin.c\

# INC_DIR ?= .

# SRCS := $(shell find $(SRC_DIRS) -name '*.c')
# OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# INC_DIRS := $(shell find $(INC_DIR) -type d)
# INC_FLAGS += $(addprefix -I,$(INC_DIRS))

# LIB    := libft/libft.a

# CFLAGS += -Wall -Wextra -Werror -g3
# #CFLAGS += -O2 -march=native
# #CFLAGS += -g3

# all:
# 	@$(MAKE) $(NAME)

# $(NAME): $(LIB) $(OBJS)
# 	@echo Linking $@
# 	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

# $(BUILD_DIR)/%.c.o: %.c
# 	@echo Compiling $@
# 	@mkdir -p $(dir $@)
# 	@$(CC) -c  $(CFLAGS) $(INC_FLAGS) $< -o $@

# $(LIB):
# 	@$(MAKE) -C libft
# 	@echo Libft done

# clean:
# 	@rm -rf $(BUILD_DIR)
# 	@$(MAKE) -C libft clean
# 	@echo Clean done

# fclean:
# 	@rm -rf $(BUILD_DIR)
# 	@rm -f $(NAME)
# 	@$(MAKE) -C libft fclean
# 	@echo Fclean done

# re: fclean
# 	@$(MAKE) -j$(NPROC) $(NAME)

# .PHONY: all clean fclean re