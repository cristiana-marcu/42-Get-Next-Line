/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:19:09 by cmarcu            #+#    #+#             */
/*   Updated: 2021/02/02 16:35:12 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

# define BUFFER_SIZE 3

size_t	ft_strlen(const char *str)
{
	size_t result;

	result = 0;
	while (*str != '\0')
	{
		result++;
		str++;
	}
	return (result);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	a;
	size_t	length;

	length = ft_strlen(s);
	a = 0;
	while (a <= length)
	{
		if (s[a] == (char)c)
			return ((char*)(s + a));
		a++;
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	int		a;
	int		b;

	if (!s1 || !s2)
		return (NULL);
	p = (char*)malloc(sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!p)
		return (NULL);
	a = 0;
	while (s1[a] != '\0')
	{
		p[a] = s1[a];
		a++;
	}
	b = a;
	a = 0;
	while (s2[a] != '\0')
	{
		p[b] = s2[a];
		a++;
		b++;
	}
	p[b] = '\0';
	return (p);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	a;

	if (!s)
		return (NULL);
	a = 0;
	if ((size_t)start >= ft_strlen(s))
		start = ft_strlen(s);
	p = (char*)malloc(sizeof(*s) * (len + 1));
	if (!p)
		return (NULL);
	while (a < len)
	{
		p[a] = s[start + a];
		a++;
	}
	p[a] = '\0';
	return (p);
}

int		get_next_line(int fd, char **line)
{
	size_t		re;
	char		buf[BUFFER_SIZE + 1];
	char		*temp;
	static char	*current_line;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (!current_line)
		current_line = (char *)malloc(1);
	while (!ft_strchr(current_line, '\n') && (re = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[re] = '\0';
		temp = ft_strjoin(current_line, buf);
		printf("Temp is: %s\n", temp);
		free(current_line);
		current_line = temp;
	}
	printf("Current line is: %s\n", current_line);
	printf("Re is: %zu\n", re);
	if (re == 0)
		return (0);
	else if (re > 0)
	{
		size_t length = ft_strchr(current_line, '\n') - current_line;
		*line = ft_substr(current_line, 0, length);
		printf("Line is: %s\n", *line);
	}
	else
		return (-1);
	temp = *line;
	free(current_line);
	current_line = temp;
	return (1);
}

int main(void)
{
	int fd = open("test.txt", 0);
	printf("File descriptor is: %d\n", fd);
	char *str = "Primera linea";
	char **line = &str;
	int a = get_next_line(fd, line);
	printf("Ended operation with exit code: %d\n", a);
	int b = get_next_line(fd, line);
	printf("Ended operation with exit code: %d\n", b);
	return (0);
}
