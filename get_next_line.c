/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relgheit <relgheit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 12:48:13 by rana              #+#    #+#             */
/*   Updated: 2024/11/27 12:02:30 by relgheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static int	null_check(char *buffer)
{
	int	i;

	i = 0;
	while (i < BUFFER_SIZE)
	{
		if (buffer[i] == 0)
			return (1);
		i++;
	}
	return (0);
}

static char	*clean_buffer(char *buffer)
{
	int	k;
	int	j;

	k = 0;
	while (buffer[k] && buffer[k] != '\n')
		k++;
	if (buffer[k] == '\n' || buffer[k] == '\0')
		k++;
	j = 0;
	if (k == (int)BUFFER_SIZE)
	{
		while (j < BUFFER_SIZE)
			buffer[j++] = '\0';
		return (buffer);
	}
	while (buffer[k])
		buffer[j++] = buffer[k++];
	buffer[j] = '\0';
	return (buffer);
}

static char	*clean_fun(char *str, char *buffer)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!str)
	{
		free (str);
		return (NULL);
	}
	while (str[i])
	{
		if (str[i] == '\n')
		{
			line = ft_substr(str, 0, i + 1);
			free (str);
			buffer = clean_buffer(buffer);
			return (line);
		}
		i++;
	}
	return (str);
}

static char	*read_fun(int fd, char *tmp, char *buffer)
{
	ssize_t	byte_read;
	char	*nline;
	int		i;

	byte_read = 1;
	nline = ft_strchr(buffer, '\n');
	while (nline == NULL) //find away to break when there's no new line
	{
		i = 0;
		while (i < BUFFER_SIZE)
			buffer[i++] = '\0';
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(tmp);
			return (NULL);
		}
		else if (byte_read == 0)
		{
			free (tmp);
			return (NULL);
		}
		if (null_check(buffer))
		{
			tmp = ft_strjoin(tmp, buffer);
			return (tmp);
		}
		buffer[BUFFER_SIZE] = '\0';
		tmp = ft_strjoin(tmp, buffer);
		nline = ft_strchr(buffer, '\n');
	}
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	ssize_t		i;
	char		*line;
	char		*temp;

	i = -1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp = (char *)malloc (sizeof(char) * BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	while (++i <= BUFFER_SIZE)
		temp[i] = 0;
	i = 0;
	if (*buffer)
		temp = ft_strjoin(temp, buffer);
	temp = read_fun(fd, temp, buffer);
	line = clean_fun(temp, buffer);
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	line = malloc(1 * sizeof(char));
// 	fd = open("text.txt", O_RDWR);
// 	while (line != NULL)
// 	{
// 		free(line);
// 		line = get_next_line(fd);
// 		printf("|%s", line);
// 	}
// 	free(line);
// 	return (0);
// }
