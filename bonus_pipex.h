/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hipham <hipham@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 19:13:47 by hipham            #+#    #+#             */
/*   Updated: 2024/02/05 17:16:07 by hipham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_PIPEX_H
# define BONUS_PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include <sys/wait.h>
# include <unistd.h>

// pipex utilities
int		ft_open(char *argv, int in_out);
void	error_message(char *argv, char *text);
void	perror_exit(char *str);
int		put_error_string(char *str);

// path parsing
char	*get_env(char **envp);
char	*get_dir(char *cmd, char **envp);
void	ft_exec(char *argv, char **envp);

// pipex bonus
// void	middle_proccesses(char *argv, char *envp[]);
// void	child2_process(int argc, char **argv, char *envp[]);
// void	child1_process(int argc, char **argv, char *envp[]);
// void	parent_process(pid_t pid, int argc,   char **argv, char **envp);

// here_doc
void	limiter_handling(char *arg2, int *pipefd);
void	heredoc_proccess(char *arg2);

#endif
