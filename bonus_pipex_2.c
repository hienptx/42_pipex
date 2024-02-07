/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hipham <hipham@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:53:59 by hipham            #+#    #+#             */
/*   Updated: 2024/02/06 18:10:41 by hipham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_pipex.h"
#include "libft/includes/libft.h"

static void	child2_process(int argc, char **argv, char *envp[])
{
	int	fdo;

	fdo = ft_open(argv[argc - 1], 1);
	dup2(fdo, STDOUT_FILENO);
	ft_exec(argv[argc - 2], envp);
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

static void fork_loop(int argc, char **argv, char **envp)
{
	int i;
	pid_t pids;
	int	pipefd[2];

	i = 2;
	while(++i < argc - 2)
	{
		if (pipe(pipefd) == -1)
			perror_exit("pipe");
		pids = fork();
		if (pids < 0)
			perror_exit("fork");
		if (pids == 0)
		{
			close(pipefd[0]);
			dup2(pipefd[1], 1);
			ft_exec(argv[i], envp);
			exit(EXIT_SUCCESS);
		}
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		//waitpid(pids, NULL, 0);
	}
}

static void	parent_process(pid_t pid, int argc, char **argv, char **envp)
{
	pid_t	pid2;

	fork_loop(argc, argv, envp);
	pid2 = fork();
	if (pid2 == -1)
		perror_exit("fork");
	if (pid2 == 0)
		child2_process(argc, argv, envp);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
}

int	main(int argc, char *argv[], char *envp[])
{
	pid_t	pid;
	int		pipefd[2];

	if (ft_strnstr(argv[1], "here_doc", 8) && argc < 6)
		put_error_string("./pipex here_doc LIMITER cmd cmd1 file\n");
	if (argc < 5)
		put_error_string("./pipex infile \"cmd1\"... \"cmdn\" outfile\n");
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
	parent_process(pid, argc, argv, envp);
	return (0);
}
