/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relgheit <relgheit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 12:48:13 by rana              #+#    #+#             */
/*   Updated: 2024/11/13 16:36:49 by relgheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
// https://github.com/Yaten/42-get_next_line/blob/master/get_next_line.c
static char	*clean_fun(char *str, char *buffer)
{
	size_t	i;
	size_t	j;
	char	*line;
	
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			line = ft_substr(str, 0, i);
			j = 0;
			printf("the clean func: %s\n", line);
			printf("the clean func: %s\n", buffer);
			while (*buffer)
			{
				if (*buffer == '\n')
				{
					buffer[j] = *buffer;
					j++;
				}
				buffer++;
			}
			printf("the clean func buffer: %s\n", buffer);
			return(line);
		}
		else
			i++;
	}
	return(str);
}

static char	*read_fun(int fd, char *tmp, char *buffer)
{
	ssize_t	byte_read;
	char 	*nline;
	// int	i;

	// i = 0;
	byte_read = 1;
	nline = ft_strchr(buffer, '\n');
	while (nline == NULL)
	{
		while (*buffer)
		{
			*buffer = '\0';
			buffer++;
		}
		byte_read = read(fd, buffer, BUFFER_SIZE);
		// printf("this is a test :%s\n", buffer);
		// printf("byte read :%zd\n", byte_read);
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
			printf("nline is :%s\n", nline);
		}
	}
	printf("buffer remaining :%s\n", buffer);
	return(tmp);
}
char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	// ssize_t	byte_read;
	char	*line;
	char	*temp;

	// byte_read = 1;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp = (char*)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	
	temp = read_fun(fd, temp, buffer);
	printf("this is a tmp :%s\n", temp);
	printf("the buffer :%s\n", buffer);
	line = clean_fun(temp, buffer);
	return(line);
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
	printf("first call :%s\n", line);
	line = get_next_line(fd);
	printf("second : %s\n", line);
	line = get_next_line(fd);
	printf("third :%s\n", line);
	return 0;
}