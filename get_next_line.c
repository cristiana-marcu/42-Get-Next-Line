/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:19:09 by cmarcu            #+#    #+#             */
/*   Updated: 2021/02/04 16:08:16 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <sys/stat.h>
#include <fcntl.h>

char	*ft_strdup(const char *s1)
{
	char			*copy;
	unsigned int	a;

	copy = (char*)malloc(sizeof(*s1) * (ft_strlen(s1) + 1));
	if (!copy)
		return (NULL);
	a = 0;
	while (s1[a] != '\0')
	{
		copy[a] = s1[a];
		a++;
	}
	copy[a] = '\0';
	return (copy);
}

int		get_next_line(int fd, char **line)
{
	size_t		re;
	char		buf[BUFFER_SIZE + 1];
	char		*temp;
	static char	*read_acu;

	if (fd < 0 || fd > 123 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (!read_acu)
		read_acu = (char *)malloc(1);
	while (!ft_strchr(read_acu, '\n') && (re = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[re] = '\0';
		temp = ft_strjoin(read_acu, buf);
		//printf("Temp is: %s\n", temp);
		free(read_acu);
		read_acu = temp;
	}
	//printf("Current line is: %s\n", read_acu);
	//printf("Re is: %zu\n", re);
	if (re == 0)
		*line = ft_strdup(read_acu);
	else if (re > 0)
	{
		size_t length = ft_strchr(read_acu, '\n') - read_acu;
		*line = ft_substr(read_acu, 0, length);
		//printf("Line is: %s\n", *line);
	}
	else
		return (-1);
	temp = ft_substr(read_acu, ft_strlen(*line) + 1, ft_strlen(read_acu));
	free(read_acu);
	read_acu = temp;
	return (re == 0 ? 0 : 1);
}

/*int main(void)
{
	int fd = open("test.txt", 0);
	printf("File descriptor is: %d\n", fd);
	char *str = "Primera linea";
	char **line = &str;
	int i = 1;
	while (i > 0)
	{
		i = get_next_line(fd, line);
		printf("Ended operation with exit code: %d\n", i);
		free(*line);
	}
	system("leaks a.out");
	return (0);
}
*/
