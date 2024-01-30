/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hipham <hipham@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 21:39:32 by hipham            #+#    #+#             */
/*   Updated: 2024/01/29 20:15:40 by hipham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_pipex.h"
#include "libft/includes/libft.h"

// Leak Check:
// void leaks()
// {
// 	system("leaks pipex");
// }

void	end_process(int argc, char **argv, char *envp[])
{
	int	fdo;

	fdo = ft_open(argv[argc - 1], 1);
	dup2(fdo, 1);
	close(fdo);
	ft_exec(argv[argc - 2], envp);
}

void	middle_proccesses(char *argv, char *envp[])
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		perror_exit("pipe");
	pid = fork();
	if (pid < 0)
		perror_exit("fork");
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		ft_exec(argv, envp);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		waitpid(pid, NULL, 0);
	}
}

void	start_process(int argc, char **argv, char *envp[])
{
	int	fd;
	int	i;

	if (ft_strnstr(argv[1], "here_doc", 8))
	{
		i = 3;
		while (i < argc - 2)
			heredoc_proccess(argv[2], argv[i++], envp);
	}
	else
	{
		i = 2;
		fd = ft_open(argv[1], 0);
		dup2(fd, 0);
		close(fd);
		while (i < argc - 2)
			middle_proccesses(argv[i++], envp);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	if (ft_strnstr(argv[1], "here_doc", 8) && argc < 6)
	{
		ft_putstr_fd("./pipex here_doc LIMITER cmd cmd1 file\n", 2);
		return (0);
	}
	if (argc < 5)
	{
		ft_putstr_fd("./pipex infile \"cmd1\"... \"cmdn\" outfile\n", 2);
		return (0);
	}
	start_process(argc, argv, envp);
	end_process(argc, argv, envp);
	return (0);
}

// leaks(); -> after childprocess
