/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaciftci <yaciftci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:20:24 by yaciftci          #+#    #+#             */
/*   Updated: 2024/10/31 17:29:50 by yaciftci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>

typedef struct dynamic_string
{
	char	*str;
	size_t	len;
	size_t	cap;
}	t_dstr;

void	dstr_add(t_dstr *dstr, char ch);

void	dstr_resize(t_dstr *dstr);

void	buff_fill_zero(char *buf, size_t len);

char	*get_next_line(int fd);

#endif
