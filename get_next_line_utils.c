/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaciftci <yaciftci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 20:20:27 by yaciftci          #+#    #+#             */
/*   Updated: 2024/11/05 14:27:02 by yaciftci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

static char	*dstr_new(size_t size)
{
	char	*new_area;

	new_area = malloc(size);
	if (NULL == new_area)
		return (NULL);
	buff_fill_zero(new_area, size);
	return (new_area);
}

static void	dstr_area_inc(t_dstr *dstr)
{
	char	*new_area;
	size_t	idx;

	new_area = malloc(dstr->cap);
	if (NULL == new_area)
	{
		free(dstr->str);
		dstr->str = NULL;
		return ;
	}
	idx = dstr->len;
	buff_fill_zero(&new_area[idx], dstr->cap - idx);
	while (0U < idx)
	{
		idx--;
		new_area[idx] = dstr->str[idx];
	}
	free(dstr->str);
	dstr->str = new_area;
}

void	dstr_add(t_dstr *dstr, char ch)
{
	if (NULL == dstr->str)
	{
		dstr->cap = 2U;
		dstr->str = dstr_new(dstr->cap);
		if (NULL == dstr->str)
			return ;
	}
	if (dstr->len == dstr->cap)
	{
		dstr->cap *= 2U;
		dstr_area_inc(dstr);
		if (NULL == dstr->str)
			return ;
	}
	dstr->str[dstr->len] = ch;
	dstr->len++;
}

void	dstr_resize(t_dstr *dstr)
{
	char	*new_area;
	size_t	idx;

	new_area = malloc(dstr->len);
	if (NULL == new_area)
	{
		free(dstr->str);
		dstr->str = NULL;
		return ;
	}
	idx = dstr->len;
	while (0U < idx)
	{
		idx--;
		new_area[idx] = dstr->str[idx];
	}
	free(dstr->str);
	dstr->str = new_area;
}

void	buff_fill_zero(char *buf, size_t len)
{
	while (len)
	{
		len--;
		buf[len] = '\0';
	}
}
