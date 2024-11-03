/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rana <rana@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 12:48:13 by rana              #+#    #+#             */
/*   Updated: 2024/11/03 21:35:56 by rana             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
// https://github.com/Yaten/42-get_next_line/blob/master/get_next_line.c

char	*read_fun(int fd, size_t BUFFER_SIZE,)
{
	static char	*buffer;
	

}
char	*get_next_line(int fd)
{
	char	*str;
	size_t BUFFER_SIZE;

	BUFFER_SIZE = 5;
	if (fd < 0)
		return (NULL);
	*str = (char*)malloc(sizeof(char) * 256 + 1);
	if (str == NULL)
		return (NULL);
	

}