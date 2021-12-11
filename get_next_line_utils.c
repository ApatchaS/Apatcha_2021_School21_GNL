/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asippy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 07:35:43 by asippy            #+#    #+#             */
/*   Updated: 2021/12/11 19:38:27 by asippy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	ft_find_line(char *buf)
{
	size_t	iter;

	iter = 0;
	while (buf[iter] != '\0' && buf[iter] != '\n')
		iter++;
	if (buf[iter] != '\n')
		return (-1);
	return (iter);
}

size_t	ft_slen(char *str)
{
	size_t	iter;

	iter = 0;
	while (str[iter] != '\0')
		iter++;
	return (iter);
}

size_t	ft_res_to_new(char **new, char **res)
{
	size_t	iter;

	iter = 0;
	while ((*res)[iter] != '\0')
	{
		(*new)[iter] = (*res)[iter];
		iter++;
	}
	free((*res));
	return (iter);
}
