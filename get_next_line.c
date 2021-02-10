/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:19:09 by cmarcu            #+#    #+#             */
/*   Updated: 2021/02/10 11:56:12 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <sys/stat.h>
#include <fcntl.h>

void	ft_bzero(char *s, size_t n)
{
	unsigned char	*p;
	size_t			a;

	p = (unsigned char *)s;
	a = 0;
	while (a < n)
	{
		p[a] = '\0';
		a++;
	}
}

int		delmem(char **p)
{
	if (p)
	{
		if (*p)
		{
			ft_bzero(*p, ft_strlen(*p));
			free(*p);
			*p = NULL;
			return (1);
		}
	}
	return (0);
}

char	*ft_strnew(size_t size)
{
	char	*ptr;

	ptr = (char *)malloc((size + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, size);
	return (ptr);
}

int		get_next_line(int fd, char **line)
{
	size_t		re;
	char		buf[BUFFER_SIZE + (re = 1)];
	char		*temp;
	static char	*read_acu;

	if (fd < 0 || fd > 123 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (!read_acu)
		read_acu = ft_strnew(0);
	while (!ft_strchr(read_acu, '\n') && (re = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[re] = '\0';
		temp = ft_strjoin(read_acu, buf);
		//printf("Temp is: %s\n", temp);
		delmem(&read_acu);
		read_acu = temp;
	}
	//printf("Accumulated reading is: %s\n", read_acu);
	//printf("Re is: %zu\n", re);
	if (re == 0)
		*line = ft_strdup(read_acu);
	else if (re > 0)
		*line = ft_substr(read_acu, 0, (ft_strchr(read_acu, '\n') - read_acu));
	//printf("Line is: %s\n", *line);
	else
		return (-1);
	//temp = ft_substr(read_acu, ft_strlen(*line) + ((re > 0) ? +1 : +0), ft_strlen(read_acu));
	temp = ft_strdup(read_acu + (ft_strlen(*line) + ((re > 0) ? +1 : +0)));
	delmem(&read_acu);
	read_acu = temp;
	return (re == 0 ? 0 * delmem(&read_acu): 1);
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
