/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:19:09 by cmarcu            #+#    #+#             */
/*   Updated: 2021/02/04 09:48:00 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	temp = ft_substr(current_line, ft_strlen(*line) + 1, ft_strlen(current_line));
	free(current_line);
	current_line = temp;
	return (1);
}

/*int main(void)
{
	int fd = open("test.txt", 0);
	printf("File descriptor is: %d\n", fd);
	char *str = "Primera linea";
	char **line = &str;
	int a = get_next_line(fd, line);
	printf("Ended operation with exit code: %d\n", a);
	int b = get_next_line(fd, line);
	printf("Ended operation with exit code: %d\n", b);
	int c = get_next_line(fd, line);
	printf("Ended operation with exit code: %d\n", c);
	int d = get_next_line(fd, line);
	printf("Ended operation with exit code: %d\n", d);
	int e = get_next_line(fd, line);
	printf("Ended operation with exit code: %d\n", e);
	return (0);
}*/
