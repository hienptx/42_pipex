/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hipham <hipham@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 21:39:32 by hipham            #+#    #+#             */
/*   Updated: 2024/01/29 19:38:43 by hipham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "pipex.h"

void	parent_process(int *pipefd, char **argv, char *envp[])
{
	int	fdo;

	fdo = ft_open(argv[4], 1);
	dup2(fdo, STDOUT_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[1]);
	ft_exec(argv[3], envp);
	close(fdo);
	exit(EXIT_SUCCESS);
}

void	child_process(int *pipefd, char **argv, char *envp[])
{
	int	fdi;

	fdi = ft_open(argv[1], 0);
	dup2(fdi, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	ft_exec(argv[2], envp);
	close(fdi);
	exit(EXIT_SUCCESS);
}

int	main(int argc, char *argv[], char *envp[])
{
	pid_t	pid;
	int		pipefd[2];

	if (argc != 5)
	{
		ft_putstr_fd("./pipex infile \"cmd1\" \"cmd2\" outfile\n", 2);
		return (EXIT_FAILURE);
	}
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == 0)
		child_process(pipefd, argv, envp);
	if (pid > 0)
		parent_process(pipefd, argv, envp);
	perror("fork");
	exit(EXIT_FAILURE);
	return (0);
}

// Leak Check:
// void leaks()
// {
// 	system("leaks pipex");
// }
// leaks(); -> after childprocess
