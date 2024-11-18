/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relgheit <relgheit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 12:48:13 by rana              #+#    #+#             */
/*   Updated: 2024/11/18 16:25:00 by relgheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*clean_buffer(char *buffer)
{
	int	k;
	int	j;

	j = 0;
	k = 0;
	while (buffer[k])
	{
		if (buffer[k] == '\n')
		{
			while (buffer[k])
			{
				buffer[j] = buffer[k + 1];
				j++;
				k++;
			}
		}
		else
			k++;
	}
	return (buffer);
}

static char	*clean_fun(char *str, char *buffer)
{
	size_t	i;
	char	*line;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			line = ft_substr(str, 0, i + 1);
			buffer = clean_buffer(buffer);
			return (line);
		}
		else
			i++;
	}
	return (str);
}

static char	*read_fun(int fd, char *tmp, char *buffer)
{
	ssize_t	byte_read;
	char	*nline;
	int		i;

	i = 0;
	byte_read = 1;
	nline = ft_strchr(buffer, '\n');
	while (nline == NULL)
	{
		while (buffer[i])
		{
			buffer[i] = '\0';
			i++;
		}
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(tmp);
			return (NULL);
		}
		else if (byte_read == 0)
			break ;
		else
		{
			buffer[BUFFER_SIZE] = '\0';
			tmp = ft_strjoin(tmp, buffer);
			nline = ft_strchr(buffer, '\n');
		}
	}
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	ssize_t		i;
	char		*line;
	char		*temp;

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp = (char *)malloc (sizeof(char) * BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	if (*buffer)
	{
		while (temp[i])
		{
			temp[i] = '\0';
			i++;
		}
		temp = ft_strjoin(temp, buffer);
	}
	temp = read_fun(fd, temp, buffer);
	line = clean_fun(temp, buffer);
	return (line);
}

int	main(void)
{
	int	fd;
	char	*line = malloc(1 * sizeof(char));
	fd = open("text.txt", O_RDWR);
	// while (line != NULL)
	// {
	// 	free(line);
	// 	line = get_next_line(fd);
	// 	printf("%s", line);
	// }
	line = get_next_line(fd);
	printf("first call :%s", line);
	line = get_next_line(fd);
	printf("second :%s", line);
	line = get_next_line(fd);
	printf("third :%s\n", line);
	free(line);
	return 0;
}