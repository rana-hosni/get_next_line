/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relgheit <relgheit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 12:48:13 by rana              #+#    #+#             */
/*   Updated: 2024/11/10 18:24:04 by relgheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
// https://github.com/Yaten/42-get_next_line/blob/master/get_next_line.c

static char	*read_fun(int fd, char *tmp, char *buffer)
{
	ssize_t	byte_read;
	char *nline;
	int	i;
	// ssize_t	size;

	
	i = 0;
	byte_read = 1;
	// str = (char*)malloc(sizeof(char) * BUFFER_SIZE + 1);
	// if (str == NULL)
	// 	return(NULL);
	nline = ft_strchr(buffer, '\n');
	while (nline == NULL)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		printf("this is a test :%s\n", buffer);
		printf("byte read :%zd\n", byte_read);
		if (byte_read == -1)
		{
			return (NULL);
			free(tmp);
		}
		else if (byte_read == 0)
			break;
		else
		{
			buffer[BUFFER_SIZE] = '\0';
			tmp = ft_strjoin(tmp, buffer);
			printf("this is tmp :%s\n", tmp);
			nline = ft_strchr(buffer, '\n');
		}
		
		i++;
	}
	return(tmp);
}
char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	// ssize_t	byte_read;
	// char	*line;
	char	*temp;

	// byte_read = 1;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp = (char*)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	
	temp = read_fun(fd, temp, buffer);
	printf("this is a tmp :%s\n", temp);
	return(temp);
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
	printf("second : %s", line);
	line = get_next_line(fd);
	printf("third :%s", line);
	return 0;
}