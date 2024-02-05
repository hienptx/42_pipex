/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hipham <hipham@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 21:39:32 by hipham            #+#    #+#             */
/*   Updated: 2024/02/05 17:16:41 by hipham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "pipex.h"

static void	child2_process(char **argv, char *envp[])
{
	int	fdo;

	fdo = ft_open(argv[4], 1);
	dup2(fdo, STDOUT_FILENO);
	ft_exec(argv[3], envp);
	close(fdo);
	exit(EXIT_SUCCESS);
}

static void	child1_process(char **argv, char *envp[])
{
	int	fdi;

	fdi = ft_open(argv[1], 0);
	dup2(fdi, STDIN_FILENO);
	ft_exec(argv[2], envp);
	close(fdi);
	exit(EXIT_SUCCESS);
}

static void	parent_process(pid_t pid, char **argv, char **envp)
{
	pid_t	pid2;

	pid2 = fork();
	if (pid2 == -1)
		perror_exit("fork");
	if (pid2 == 0)
		child2_process(argv, envp);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
}

int	main(int argc, char *argv[], char *envp[])
{
	pid_t	pid;
	int		pipefd[2];

	if (argc != 5)
		put_error_string("./pipex infile \"cmd1\" \"cmd2\" outfile\n");
	if (pipe(pipefd) == -1)
		perror_exit("pipe");
	pid = fork();
	if (pid == -1)
		perror_exit("fork");
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		child1_process(argv, envp);
	}
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	parent_process(pid, argv, envp);
	return (0);
}

// Leak Check:
// void leaks()
// {
// 	system("leaks pipex");
// }
// leaks(); -> after childprocess
