/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hipham <hipham@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 16:31:06 by hipham            #+#    #+#             */
/*   Updated: 2024/02/05 17:16:19 by hipham           ###   ########.fr       */
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
void	error_message(char *argv, char *text);
void	perror_exit(char *str);
int		put_error_string(char *str);

// parsing
char	*get_env(char **envp);
char	*get_dir(char *cmd, char **envp);
void	ft_exec(char *argv, char **envp);

// pipex
// void	child2_process(char **argv, char *envp[]);
// void	child1_process(char **argv, char *envp[]);
// void	parent_process(pid_t pid, char **argv, char **envp);

#endif
