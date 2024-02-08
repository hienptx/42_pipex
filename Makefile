# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hipham <hipham@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/27 16:27:01 by hipham            #+#    #+#              #
#    Updated: 2024/02/06 18:15:45 by hipham           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# $@ or $< is automatic variables 
# -c: This option tells the compiler to generate an object file, not an executable.
# $<: This is an automatic variable that represents the first prerequisite 
# (dependency). In this context, it is the source file (%.c) that the rule is 
# operating on.

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I./libft -I./includes 
# LEAKS = -L../LeakSanitizer -llsan -lc++ -Wno-gnu-include-next -I ../LeakSanitize

SRCS = 	pipex.c pipex_utils.c path_parsing.c
BONUS_SRCS = bonus_pipex.c pipex_utils.c path_parsing.c bonus_pipex_heredoc.c 

HEADERS = pipex.h bonus_pipex.h
LIBFT_PATH = libft

OBJCS = $(SRCS:.c=.o)
BONUS_OBJCS = $(BONUS_SRCS:.c=.o)

NAME = pipex

.PHONY: all clean fclean re

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@	

all: $(NAME)

bonus: $(BONUS_OBJCS) $(LIBFT_PATH)/libft.a
	$(CC) $(CFLAGS) -o $(NAME) $(BONUS_OBJCS) $(LIBFT_PATH)/libft.a
	
$(NAME): $(OBJCS) $(LIBFT_PATH)/libft.a
	$(CC) $(CFLAGS) -o $@ $(OBJCS) $(LIBFT_PATH)/libft.a

$(LIBFT_PATH)/libft.a:
	make -C $(LIBFT_PATH)

clean:
	rm -f $(OBJCS) $(BONUS_OBJCS)
	make -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(NAME) bonus
	make -C $(LIBFT_PATH) fclean

re: fclean all

# ./pipex pipex.h "sort -r" "grep int" "wc -l" outfile
# < pipex.h  sort -r | grep int | wc -l > outfile

# ./pipex pipex.h "sleep 3" "sort -r" "grep int" "sleep 3" "wc -l" outfile
# < pipex.h sleep 3 | sort -r | grep int | sleep 3 | wc -l > outfile

# ./pipex test.txt "cat test.txt" "grep 90" "sort -r" outfile
# < test.txt | cat test.txt | grep 90 | sort -r > outfile

# ./pipex Makefile "ls -l" "sleep 3" "sort -r" outfile
# < Makefile ls -l | sleep 3 | sort -r > outfile

# ./pipex Makefile "sleep 3" "ls -l" "sort -r" outfile
# < Makefile sleep 3 | ls -l | sort -r > outfile

# ./pipex here_doc stop "sleep 3" "ls -l" "wc -l" outfile
# sleep 3 << stop | ls -l | wc -l >> outfile

# ./pipex pipex.h "cat /dev/urandom" "ls -l" "sleep 3" outfile
# < pipex.h cat /dev/urandom | ls -l | sleep 3 > outfile