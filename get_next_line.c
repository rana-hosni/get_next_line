/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relgheit <relgheit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 12:48:13 by rana              #+#    #+#             */
/*   Updated: 2024/11/08 20:03:37 by relgheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
// https://github.com/Yaten/42-get_next_line/blob/master/get_next_line.c

static char	*read_fun(int fd, char *tmp, char *buffer)
{
	ssize_t	byte_read;
	// char *str;
	int	i;
	// ssize_t	size;

	
	// size = 0;
	byte_read = 1;
	// str = (char*)malloc(sizeof(char) * BUFFER_SIZE + 1);
	// if (str == NULL)
	// 	return(NULL);
	while ((byte_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		// size += byte_read;
		if (byte_read == -1)
		{
			return(NULL);
			free(buffer);
		}
		if (byte_read == 0)
			break;
		else
		{
			buffer[byte_read] = '\0';
			tmp = ft_strjoin(tmp, buffer);
		}
	}
	return(tmp);
}
char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	// ssize_t	byte_read;
	char	*line;
	char	*temp;

	// byte_read = 1;
	
	if (fd < 0 || BUFFER_SIZE <= 0 || (read(fd, 0, 0) < 0))
		return (NULL);
	temp = (char*)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (temp== NULL)
		return (NULL);
	line = read_fun(fd, temp, buffer);
	printf("this is a test :%s\n", line);
	return(line);
}

int	main(void)
{
	int	fd;
	char	*line;
	fd = open("text.txt", O_RDWR);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	return 0;
}