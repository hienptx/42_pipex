/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hipham <hipham@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 16:31:06 by hipham            #+#    #+#             */
/*   Updated: 2024/01/29 20:47:01 by hipham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include <unistd.h>

// pipex utilities
int		ft_open(char *argv, int in_out);
void	ft_free(char **arr);
void	error_message(char *argv, char *text);
void	ft_putstr_fd(char *s, int fd);

// parsing
char	*get_env(char **envp);
char	*get_dir(char *cmd, char **envp);
void	ft_exec(char *argv, char **envp);

// pipex
void	child_process(int *pipefd, char **argv, char *envp[]);
void	parent_process(int *pipefd, char **argv, char *envp[]);

#endif
