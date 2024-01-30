# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hipham <hipham@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/27 16:27:01 by hipham            #+#    #+#              #
#    Updated: 2024/01/29 20:15:14 by hipham           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# $@ or $< is automatic variables 
# -c: This option tells the compiler to generate an object file, not an executable.
# $<: This is an automatic variable that represents the first prerequisite 
# (dependency). In this context, it is the source file (%.c) that the rule is 
# operating on.

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I./libft -I./includes

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

# ./pipex test.txt "sort -r" "grep 87" "wc -l" outfile
# < test.txt "sort -r" | "grep 87" | "wc -l" > outfile

# ./pipex test.txt "sleep 3" "sort -r" "grep i" "sleep 3" "wc -l" outfile
# < test.txt sleep 3 | sort -r | grep i | sleep 3 | wc -l > outfile

# ./pipex test.txt "cat test.txt" "grep 90" "sort -r" outfile
# < test.txt | cat test.txt | grep 90 | sort -r > outfile