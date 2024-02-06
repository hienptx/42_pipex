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

static void	middle_proccesses(int *pipefd, char *argv, char *envp[])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror_exit("fork");
	if (pid == 0)
	{
		// Child process
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		ft_exec(argv, envp);
		exit(EXIT_SUCCESS);
	}
	else
	{
		// Parent process
		close(pipefd[1]); // Close the write end of the pipe in the parent
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		waitpid(pid, NULL, 0);
	}
}

static void	child2_process(int argc, char **argv, char *envp[])
{
	int	fdo;

	if (ft_strnstr(argv[1], "here_doc", 8))
		fdo = ft_open(argv[argc - 1], 2);
	else
		fdo = ft_open(argv[argc - 1], 1);
	dup2(fdo, STDOUT_FILENO);
	ft_exec(argv[argc - 2], envp);
	close(fdo);
	exit(EXIT_SUCCESS);
}

static void	child1_process(int *pipefd, int argc, char **argv, char *envp[])
{
	int	fd;
	int	i;

	close(pipefd[0]);
	if (ft_strnstr(argv[1], "here_doc", 8))
	{
		i = 3;
		heredoc_proccess(argv[2]);
	}
	else
	{
		i = 2;
		fd = ft_open(argv[1], 0);
		dup2(fd, 0);
		close(fd);
	}
	while (i < argc - 2)
	{
		middle_proccesses(pipefd, argv[i++], envp);
	}
}

static void	parent_process(pid_t pid, int argc, char **argv, char **envp)
{
	pid_t	pid2;

	pid2 = fork();
	if (pid2 == -1)
		perror_exit("fork");
	if (pid2 == 0)
		child2_process(argc, argv, envp);
	waitpid(pid2, NULL, 0);
	waitpid(pid, NULL, 0);
}

int	main(int argc, char *argv[], char *envp[])
{
	pid_t	pid;
	int		pipefd[2];

	if (argc < 5)
		put_error_string("./pipex infile \"cmd1\"... \"cmdn\" outfile\n");
	if (ft_strnstr(argv[1], "here_doc", 8) && argc < 6)
		put_error_string("./pipex here_doc LIMITER cmd cmd1 file\n");
	if (pipe(pipefd) == -1)
		perror_exit("pipe");
	pid = fork();
	if (pid == -1)
		perror_exit("fork");
	if (pid == 0)
		child1_process(pipefd, argc, argv, envp);
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	parent_process(pid, argc, argv, envp);
	return (0);
}
