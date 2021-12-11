/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asippy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 07:12:31 by asippy            #+#    #+#             */
/*   Updated: 2021/12/11 20:06:14 by asippy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_push_all_buf(char **res, char *buf)
{
	char	*new;
	size_t	iter1;
	size_t	iter2;

	new = (char *)malloc(sizeof(char) * (ft_slen(*res) + ft_slen(buf) + 1));
	if (new == (void *)0)
		return ((void *)0);
	iter1 = ft_res_to_new(&new, res);
	iter2 = 0;
	while (buf[iter2] != '\0')
	{
		new[iter1] = buf[iter2];
		iter1++;
		iter2++;
	}
	buf[0] = '\0';
	new[iter1] = '\0';
	return (new);
}

static char	*ft_push_line(size_t lcntr, char **res, char *buf)
{
	char	*new;
	size_t	iter1;
	size_t	iter2;

	new = (char *)malloc(sizeof(char) * (ft_slen(*res) + lcntr + 2));
	if (new == (void *)0)
		return ((void *)0);
	iter1 = ft_res_to_new(&new, res);
	iter2 = 0;
	while (iter2 <= lcntr)
	{
		new[iter1] = buf[iter2];
		iter1++;
		iter2++;
	}
	new[iter1] = '\0';
	iter1 = 0;
	while (buf[iter2] != '\0')
	{
		buf[iter1] = buf[iter2];
		iter1++;
		iter2++;
	}
	buf[iter1] = '\0';
	return (new);
}

static char	*ft_push(size_t *flag, char **res, char *buf)
{
	ssize_t	lcntr;
	char	*new;

	lcntr = ft_find_line(buf);
	if (lcntr == -1)
		new = ft_push_all_buf(res, buf);
	else
	{
		*flag = 1;
		new = ft_push_line((size_t)lcntr, res, buf);
	}
	if (new == (void *)0)
	{
		free((*res));
		return ((void *)0);
	}
	return (new);
}

static size_t	ft_read(int fd, char **res, char *buf)
{
	ssize_t		bytesread;

	bytesread = read(fd, buf, BUFFER_SIZE);
	if (bytesread == -1)
	{
		free ((*res));
		*res = (void *)0;
		return (1);
	}
	if (bytesread == 0)
	{
		if ((*res)[0] == '\0')
		{
			free ((*res));
			*res = (void *)0;
			return (1);
		}
		return (1);
	}
	buf[bytesread] = '\0';
	return (0);
}

char	*get_next_line(int fd)
{
	static char	buf[OPEN_MAX][BUFFER_SIZE + 1];
	char		*res;
	size_t		flag;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return ((void *)0);
	res = (char *)malloc(sizeof(char));
	if (res == (void *)0)
		return ((void *)0);
	res[0] = '\0';
	while (1)
	{
		flag = 0;
		res = ft_push(&flag, &res, buf[fd]);
		if (res == (void *)0)
			return ((void *)0);
		if (flag)
			return (res);
		if (buf[fd][0] == '\0')
			if (ft_read(fd, &res, buf[fd]))
				return (res);
	}	
}
