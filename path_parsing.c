/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hipham <hipham@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:26:45 by hipham            #+#    #+#             */
/*   Updated: 2024/01/29 18:54:00 by hipham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "bonus_pipex.h"
#include "libft/includes/libft.h"

char	*get_env(char **envp)
{
	int		i;
	char	**my_env;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strnstr(envp[i], "PATH", 4))
			my_env = ft_split(envp[i], '=');
		i++;
	}
	if (my_env != NULL)
	{
		free(my_env[0]);
		return (my_env[1]);
	}
	else
	{
		ft_free(my_env);
		return (NULL);
	}
}

char	*get_dir(char *cmd, char **envp)
{
	char	*env_path;
	char	**dir;
	char	*full_path;
	char	*ready;
	int		i;

	i = -1;
	env_path = get_env(envp);
	dir = ft_split(env_path, ':');
	while (dir[++i])
	{
		full_path = ft_strjoin(dir[i], "/");
		ready = ft_strjoin(full_path, cmd);
		free(full_path);
		if (access(ready, F_OK | X_OK) == 0)
		{
			ft_free(dir);
			return (ready);
		}
		free(ready);
	}
	ft_free(dir);
	return (NULL);
}

void	ft_exec(char *argv, char **envp)
{
	char	**cmd;
	char	*dir;

	cmd = ft_split(argv, ' ');
	dir = get_dir(cmd[0], envp);
	if (dir == NULL)
	{
		error_message(cmd[0], "zsh: command not found: ");
		ft_free(cmd);
		exit(EXIT_FAILURE);
	}
	if (execve(dir, cmd, envp) == -1)
	{
		perror("execve");
		ft_free(cmd);
		exit(EXIT_FAILURE);
	}
	ft_free(cmd);
}