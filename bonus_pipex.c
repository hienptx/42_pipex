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

static void	middle_proccesses(char *argv, char *envp[])
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		perror_exit("pipe");
	pid = fork();
	if (pid == -1)
		perror_exit("fork");
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		ft_exec(argv, envp);
		exit(EXIT_SUCCESS);
	}
	close(pipefd[1]);
	dup2(pipefd[0], 0);
	waitpid(pid, NULL, 0);
}

static void	start_process(int argc, char **argv, char *envp[])
{
	int	fd;
	int	fdo;
	int	i;

	if (ft_strnstr(argv[1], "here_doc", 8))
	{
		i = 3;
		heredoc_proccess(argv[2]);
		fd = ft_open(argv[argc - 1], 2);
		dup2(fd, 1);
		close(fd);
	}
	else
	{
		i = 2;
		fd = ft_open(argv[1], 0);
		dup2(fd, 0);
		close(fd);
		fdo = ft_open(argv[argc - 1], 1);
		dup2(fdo, 1);
		close(fdo);
	}
	while (i < argc - 2)
		middle_proccesses(argv[i++], envp);
	ft_exec(argv[argc - 2], envp);
}

int	main(int argc, char *argv[], char *envp[])
{
	if (ft_strnstr(argv[1], "here_doc", 8) && argc < 6)
		put_error_string("./pipex here_doc LIMITER cmd cmd1 file\n");
	if (argc < 5)
		put_error_string("./pipex infile \"cmd1\"... \"cmdn\" outfile\n");
	start_process(argc, argv, envp);
	return (0);
}

// leaks(); -> after childprocess
