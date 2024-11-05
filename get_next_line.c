/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaciftci <yaciftci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 20:20:24 by yaciftci          #+#    #+#             */
/*   Updated: 2024/11/05 16:46:59 by yaciftci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif

static ssize_t	update_fstr_buf(int fd, char *buf)
{
	ssize_t	n;

	n = read(fd, buf, BUFFER_SIZE);
	if (n >= 0)
		buf[n] = '\0';
	return (n);
}

static int	get_line_fstr_buf(char *buf, t_dstr *line)
{
	static int	i;
	int			line_flag;

	line_flag = 1;
	while (('\n' != buf[i]) && ('\0' != buf[i]))
	{
		dstr_add(line, buf[i]);
		if (NULL == line->str)
			return (-1);
		i++;
	}
	if ('\n' == buf[i])
	{
		line_flag = 0;
		dstr_add(line, buf[i]);
		if (NULL == line->str)
			return (-1);
		i++;
	}
	if (('\0' == buf[i]))
	{
		i = 0;
		buff_fill_zero(buf, BUFFER_SIZE);
	}
	return (line_flag);
}

static bool	get_one_line(int fd, t_dstr *line)
{
	int			line_flag;
	static char	fstr_buf[BUFFER_SIZE + 1];

	line_flag = 1;
	while (0 < line_flag)
	{
		if ('\0' == fstr_buf[0])
			line_flag = update_fstr_buf(fd, fstr_buf);
		else
			line_flag = get_line_fstr_buf(fstr_buf, line);
	}
	if ((-1 == line_flag) || ((0 == line_flag) && (0U == line->len)))
		return (false);
	return (true);
}

char	*get_next_line(int fd)
{
	bool	ret;
	t_dstr	line;

	line.len = 0U;
	line.cap = 0U;
	line.str = NULL;
	if ((fd < 0) || (BUFFER_SIZE <= 0))
		return (NULL);
	ret = get_one_line(fd, &line);
	if (false == ret)
	{
		if (NULL != line.str)
			free(line.str);
		return (NULL);
	}
	dstr_add(&line, '\0');
	if (NULL != line.str)
		dstr_resize(&line);
	return (line.str);
}
