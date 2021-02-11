/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 10:14:47 by cmarcu            #+#    #+#             */
/*   Updated: 2021/02/11 16:07:36 by cmarcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line_bonus.h"

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

int		mount_next_line(int re, int fd, char *temp, char **re_acu, char **line)
{
	int aux;

	if (re > 0)
		aux = 1;
	else
		aux = 0;
	temp = ft_substr(re_acu[fd], ft_strlen(*line) + aux, ft_strlen(re_acu[fd]));
	delmem(&re_acu[fd]);
	re_acu[fd] = temp;
	if (re == 0)
	{
		delmem(&re_acu[fd]);
		return (0);
	}
	return (1);
}

int		get_next_line(int fd, char **line)
{
	size_t		re;
	char		buf[BUFFER_SIZE + 1];
	char		*temp;
	static char	*re_acu[MAX_FD];

	re = 1;
	if (fd < 0 || fd > 123 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (!re_acu[fd])
		re_acu[fd] = ft_strdup("");
	while (!ft_strchr(re_acu[fd], '\n') && (re = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[re] = '\0';
		temp = ft_strjoin(re_acu[fd], buf);
		delmem(&re_acu[fd]);
		re_acu[fd] = temp;
	}
	if (re == 0)
		*line = ft_strdup(re_acu[fd]);
	else if (re > 0)
		*line = ft_substr(re_acu[fd], 0, (ft_strchr(re_acu[fd], '\n') - re_acu[fd]));
	else
		return (-1);
	return (mount_next_line(re, fd, temp, re_acu, line));
}
