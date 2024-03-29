/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hipham <hipham@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:49:55 by hipham            #+#    #+#             */
/*   Updated: 2024/02/06 18:46:07 by hipham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_pipex.h"
#include "libft/includes/libft.h"
#include "pipex.h"

void heredoc_process(char *arg2)
{
	char *str;
	int		i;

	i = ft_strlen(arg2);
	while (1)
	{
		ft_putstr_fd("pipe heredoc> ", 0);
		str = get_next_line(0);
		if (str != NULL)
		{
			if (ft_strncmp(str, arg2, ft_strlen(arg2)) == 0 && str[i] == '\n')
			{
				free(str);
				break;
			}
			ft_putstr_fd(str, STDOUT_FILENO);
			free(str);
		}
	}
}

// void	limiter_handling(char *arg2, int *pipefd)
// {
// 	char	*str;
// 	int		i;

// 	i = ft_strlen(arg2);
// 	while (1)
// 	{
// 		ft_putstr_fd("pipe heredoc> ", 0);
// 		str = get_next_line(0);
// 		if (str != NULL)
// 		{
// 			if (ft_strncmp(str, arg2, ft_strlen(arg2)) == 0 && str[i] == '\n')
// 		{
//  				free(str);
// 			break ;
// 			}
//  			ft_putstr_fd(str, pipefd[1]);
// 			free(str);
// 		}
// 		exit(0); 
// 	}
// }

// void	heredoc_process(char *arg2)
// {
// 	pid_t	pid;
// 	int		pipefd[2];

// 	if (pipe(pipefd) == -1)
// 		perror_exit("pipe");
// 	pid = fork();
// 		close(pipefd[1]);
// 		dup2(pipefd[0], 0);
// 		waitpid(pid, NULL, 0);
// 	}
// }
