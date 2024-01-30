/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hipham <hipham@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:12:16 by hipham            #+#    #+#             */
/*   Updated: 2024/01/29 17:37:41 by hipham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*save_rest(char *line)
{
	char	*temp;
	char	*start;
	size_t	len;

	start = ft_strchr(line, '\n');
	if (start != NULL)
	{
		len = ft_strlen(start + 1);
		temp = malloc(len + 1);
		if (temp == NULL)
			return (NULL);
		temp = ft_memcpy(temp, start + 1, len);
		temp[len] = '\0';
	}
	else
		temp = NULL;
	free(line);
	return (temp);
}

static char	*get_line(char *stored_read)
{
	char	*return_line;
	char	*temp;
	int		i;

	i = 0;
	temp = stored_read;
	while (*temp != 0 && *temp != '\n')
	{
		i++;
		temp++;
	}
	if (*temp == '\n')
		i++;
	return_line = malloc(sizeof(char) * (i + 1));
	if (return_line == NULL)
		return (NULL);
	return_line = ft_memcpy(return_line, stored_read, i);
	return_line[i] = '\0';
	return (return_line);
}

static char	*read_line(int fd, char *store, char *buffer)
{
	int		byte_read;
	char	*temp;

	byte_read = 1;
	while (byte_read)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		buffer[byte_read] = '\0';
		temp = store;
		store = ft_strjoin(store, buffer);
		free(temp);
		if (ft_strchr(buffer, '\n') != NULL)
			break ;
	}
	if (byte_read == 0 && store[0] == '\0')
	{
		free(store);
		return (NULL);
	}
	return (store);
}

char	*get_next_line(int fd)
{
	char		*return_line;
	static char	*read_str;
	char		buffer[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read(fd, 0, 0) < 0)
	{
		free(read_str);
		read_str = NULL;
		return (NULL);
	}
	if (!read_str)
	{
		read_str = ft_strdup("");
		if (read_str == NULL)
			return (NULL);
	}
	read_str = read_line(fd, read_str, buffer);
	if (read_str == NULL)
		return (NULL);
	return_line = get_line(read_str);
	read_str = save_rest(read_str);
	return (return_line);
}

// int	main(void)
// {
// 	char	*line;
// 	int		fd;

// 	fd = open("onlynl.txt", O_RDONLY);
// 	if (fd == -1)
// 		return (0);
// 	while ((line = get_next_line(fd)))
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
