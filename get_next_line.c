/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 00:05:01 by ysarsar           #+#    #+#             */
/*   Updated: 2018/11/01 01:21:52 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		cat_line(int fd, char **line, char **str)
{
	int		i;

	i = 0;
	while (str[fd][i] != '\n' && str[fd][i])
		i++;
	if (str[fd][i] == '\n')
	{
		*line = ft_strsub(str[fd], 0, i);
		str[fd] = ft_strdup(str[fd] + i + 1);
	}
	else if (str[fd][i] == '\0')
	{
		*line = ft_strdup(str[fd]);
		ft_strdel(&str[fd]);
	}
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static	char	*str[4096];
	char			buff[BUFF_SIZE + 1];
	int				res;

	if (fd < 0 || line == NULL || fd > 4096)
		return (-1);
	while ((res = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[res] = '\0';
		if (str[fd] == NULL)
			str[fd] = ft_strnew(1);
		str[fd] = ft_strjoin(str[fd], buff);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	if (res == -1)
		return (-1);
	else if (res == 0 && (str[fd] == NULL || str[fd][0] == '\0'))
		return (0);
	return (cat_line(fd, line, str));
}
