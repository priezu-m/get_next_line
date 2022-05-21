/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: priezu-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:02:58 by priezu-m          #+#    #+#             */
/*   Updated: 2022/05/08 19:00:56 by priezu-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

static t_line	realloc_line(t_line line, size_t size)
{
	const char	*new_str = malloc(size);

	if (new_str)
	{
		ft_memcpy((char *)new_str, line.str, ft_min(line.cursor, size));
	}
	free(line.str);
	line.str = (char *)new_str;
	line.size = size;
	return (line);
}

static t_line	update_line(t_line line, int fd)
{
	ssize_t	read_return;

	read_return = 1;
	while ((*line_end(line) != '\n') && read_return > 0)
	{
		if ((line.cursor + BUFFER_SIZE) > line.size)
			line = realloc_line(line, line.size + BUFFER_SIZE);
		if (!line.str)
		{
			errno = ENOMEM;
			return (line);
		}
		read_return = read(fd, &line.str[line.cursor], BUFFER_SIZE);
		if (read_return < 0)
		{
			free(line.str);
			line.str = NULL;
			return (line);
		}
		line.cursor += (size_t)read_return;
	}
	return (line);
}

static char	*make_new_line(t_line line)
{
	const char		*new_line_end = line_end(line);
	char			*new_line;
	const size_t	new_line_size = (size_t)(new_line_end - line.str) + 2;

	if (line.cursor == 0)
		return (NULL);
	new_line = malloc(new_line_size);
	if (!new_line)
		return (NULL);
	ft_memcpy(new_line, line.str, (size_t)(new_line_end - line.str) + 1);
	new_line[new_line_size - 1] = '\0';
	return (new_line);
}

static t_line	remove_old_line(t_line line)
{
	const char	*old_line_end = line_end(line);
	char		*remaining_line;
	size_t		size;

	size = (size_t)(&line.str[line.cursor - 1] - old_line_end);
	if (size == 0)
	{
		free(line.str);
		return ((t_line){0});
	}
	remaining_line = malloc(size);
	if (!remaining_line)
	{
		errno = ENOMEM;
		line.str = NULL;
		return (line);
	}
	ft_memcpy(remaining_line, old_line_end + 1, size);
	free(line.str);
	line.str = remaining_line;
	line.size = size;
	line.cursor = size;
	return (line);
}

char	*get_next_line(int fd)
{
	static t_line	line;
	char			*new_line;

	if (!line.str && !line.size && !line.cursor)
		line = init_line();
	if (line.str == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	line = update_line(line, fd);
	if (line.str == NULL)
		return (NULL);
	new_line = make_new_line(line);
	if (!new_line)
	{
		errno = ENOMEM;
		free(line.str);
		line.str = NULL;
		return (new_line);
	}
	line = remove_old_line(line);
	return (new_line);
}

/*int	main(void)
{
	const int	fd = open("./gnlTester/files/nl", O_RDWR);

	printf ("%d\n", fd);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
}*/
