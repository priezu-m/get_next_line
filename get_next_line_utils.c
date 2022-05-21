/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: priezu-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 17:54:15 by priezu-m          #+#    #+#             */
/*   Updated: 2022/05/08 18:43:22 by priezu-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_line	init_line(void)
{
	t_line	line;

	line.size = BUFFER_SIZE;
	line.cursor = 0;
	line.str = calloc(BUFFER_SIZE, sizeof(char));
	return (line);
}

char	*line_end(t_line line)
{
	const char	*line_end = ft_memchr(line.str, '\n', line.cursor);

	if (line_end)
		return ((char *)line_end);
	if (line.cursor == 0)
	{
		*line.str = !'\n';
		return (line.str);
	}
	return (&line.str[line.cursor - 1]);
}

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*pp;

	pp = (const char *)s;
	while (n && (*pp != (char)c))
	{
		pp++;
		n--;
	}
	if (!n)
		return (NULL);
	return ((char *)pp);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dst_pp;
	const char	*src_pp;

	dst_pp = (char *)dst;
	src_pp = (const char *)src;
	if (!src && !dst)
		return (dst);
	while (n)
	{
		*dst_pp = *src_pp;
		dst_pp++;
		src_pp++;
		n--;
	}
	return (dst);
}

uintmax_t	ft_min(uintmax_t x, uintmax_t y)
{
	if (x < y)
		return (x);
	return (y);
}
