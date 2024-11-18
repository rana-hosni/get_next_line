/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relgheit <relgheit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:50:14 by relgheit          #+#    #+#             */
/*   Updated: 2024/11/18 16:24:05 by relgheit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	unsigned int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int				i;
	int				j;
	char			*new;

	i = 0;
	j = 0;
	new = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new)
	{
		free((void *)s1);
		return (NULL);
	}
	while (s1[j])
	{
		new[i] = s1[j];
		i++;
		j++;
	}
	j = 0;
	while (s2[j])
	{
		new[i] = s2[j];
		i++;
		j++;
	}
	new[i] = '\0';
	free((void *)s1);
	return (new);
}

char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if ((char) c == *str)
			return ((char *)str);
		str++;
	}
	if ((char) c == '\0')
		return ((char *)str);
	return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*p;
	unsigned int	s_len;
	size_t			i;

	i = 0;
	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len <= start)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	p = (char *)malloc(sizeof(char) * (len +1));
	if (!p)
		return (NULL);
	if ((len + 1) != 0)
	{
		while (s[i] && i < (len))
		{
			p[i] = s[i];
			i++;
		}
		p[i] = '\0';
	}
	free((void *)s);
	return (p);
}

char	*ft_strdup(const char *s)
{
	char	*p;
	size_t	size;
	size_t	i;

	i = 0;
	size = ft_strlen(s);
	p = malloc(sizeof(char) * (size + 1));
	if (p == NULL)
		return (NULL);
	if ((size + 1) != 0)
	{
		while (s[i] && i < (size))
		{
			p[i] = s[i];
			i++;
		}
		p[i] = '\0';
	}
	return (p);
}
