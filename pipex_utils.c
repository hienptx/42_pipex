/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hipham <hipham@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:21:58 by hipham            #+#    #+#             */
/*   Updated: 2024/02/05 18:44:01 by hipham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_pipex.h"
#include "libft/includes/libft.h"
#include "pipex.h"

void	perror_exit(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

int	put_error_string(char *str)
{
	ft_putstr_fd(str, 2);
	return (0);
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
		fd = open(argv, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (in_out == 2)
		fd = open(argv, O_CREAT | O_RDWR | O_APPEND, 0777);
	if (fd == -1)
	{
		error_message(argv, "zsh: no such file or directory: ");
		exit(EXIT_FAILURE);
	}
	return (fd);
}
