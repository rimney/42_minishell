# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rimney <rimney@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/28 12:27:57 by atarchou          #+#    #+#              #
#    Updated: 2022/06/22 00:28:10 by rimney           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
FLAGS = -Wall -Wextra -Werror -lreadline -g
RL_FLAGS = -L /Users/atarchou/homebrew/opt/readline/lib -I /Users/atarchou/homebrew/opt/readline/include  -g
SRCS = parse.c\
		redir.c\
		parse_token.c\
		utils.c\
		utils_2.c\
		quotes.c\
		ft_middle_operations.c \
		minishell.c\
		../lab/files/libfunctions/*.c \
		../lab/files/redirections/ft_pipe.c \
		../lab/files/redirections/ft_redirect_output.c \
		../lab/files/redirections/ft_heredoc.c \
		../lab/files/redirections/ft_append.c \
		../lab/files/redirections/ft_redirect_input.c \
		


$(NAME) : $(SRCS)
			$(CC) $(SRCS) $(RL_FLAGS) $(FLAGS)  -o $(NAME) 

all : $(NAME)

clean :
		rm -rf $(NAME)

fclean :
		rm -rf minishell

re : fclean all

.PHONY : all clean fclean re