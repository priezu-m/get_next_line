/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: priezu-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:03:42 by priezu-m          #+#    #+#             */
/*   Updated: 2022/05/08 18:43:20 by priezu-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <errno.h>
# include <stdint.h>
# include <stddef.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

typedef struct s_line
{
	size_t	size;
	size_t	cursor;
	char	*str;
}t_line;

t_line		init_line(void);
char		*line_end(t_line line);
char		*get_next_line(int fd);
void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
uintmax_t	ft_min(uintmax_t x, uintmax_t y);

#endif
