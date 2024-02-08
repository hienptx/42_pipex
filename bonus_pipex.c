/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hipham <hipham@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 21:39:32 by hipham            #+#    #+#             */
/*   Updated: 2024/02/06 18:49:31 by hipham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_pipex.h"
#include "libft/includes/libft.h"

static void child2_process(int argc, char **argv, char *envp[])
{
	int fdo;

	if (ft_strnstr(argv[1], "here_doc", 8))
		fdo = ft_open(argv[argc - 1], 2);
	else
		fdo = ft_open(argv[argc - 1], 1);
	dup2(fdo, STDOUT_FILENO);
	ft_exec(argv[argc - 2], envp);
	close(fdo);
	exit(EXIT_SUCCESS);
}

static void child1_process(int *pipefd, char **argv, char *envp[])
{
	int fdi;

	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	if (ft_strnstr(argv[1], "here_doc", 8))
	{
		heredoc_process(argv[2]);
		ft_exec(argv[3], envp);
		exit(EXIT_SUCCESS);
	}
	else
	{
		fdi = ft_open(argv[1], 0);
		dup2(fdi, STDIN_FILENO);
		ft_exec(argv[2], envp);
		close(fdi);
		exit(EXIT_SUCCESS);
	}
}

static void fork_loop(int i, char **argv, char **envp)
{
	pid_t pids;
	int pipefd[2];

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
}

static void parent_process(int *pipefd, int argc, char **argv, char **envp)
{
	pid_t pid2;
	int i;
	int	nr_cmd;

	i = 2;
	nr_cmd = 0;
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	if (ft_strnstr(argv[1], "here_doc", 8))
		i = 3;
	while (++i < argc - 2)
	{
		fork_loop(i, argv, envp);
		nr_cmd++;
	}
	pid2 = fork();
	if (pid2 == -1)
		perror_exit("fork");
	if (pid2 == 0)
		child2_process(argc, argv, envp);
	while (nr_cmd-- > 0)
		wait(0);
	waitpid(pid2, NULL, 0);
}

// void wait_for_children(int nr_cmd, int argc, char **argv)
// {
// 	int status;

// 	if (ft_strnstr(argv[1], "here_doc", 8))
// 		nr_cmd = argc - 4;
// 	while (nr_cmd > 0)
// 	{
// 		wait(&status);
// 		nr_cmd--;
// 	}
// }

int main(int argc, char *argv[], char *envp[])
{
	pid_t pid;
	int pipefd[2];

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
		child1_process(pipefd, argv, envp);
	parent_process(pipefd, argc, argv, envp);
	waitpid(pid, NULL, 0);
	return (0);
}
