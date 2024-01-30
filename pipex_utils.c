/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hipham <hipham@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:21:58 by hipham            #+#    #+#             */
/*   Updated: 2024/01/29 19:44:17 by hipham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "bonus_pipex.h"
#include "libft/includes/libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	while (*s != '\0')
	{
		write(fd, s, 1);
		s++;
	}
}

void	perror_exit(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	error_message(char *argv, char *text)
{
	ft_putstr_fd(text, 2);
	ft_putstr_fd(argv, 2);
	ft_putstr_fd("\n", 2);
}

int	ft_open(char *argv, int in_out)
{
	int	fd;

	fd = 0;
	if (in_out == 0)
		fd = open(argv, O_RDONLY);
	if (in_out == 1)
		fd = open(argv, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		error_message(argv, "zsh: no such file or directory: ");
		exit(EXIT_FAILURE);
	}
	return (fd);
}
