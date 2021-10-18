/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcoelho- <gcoelho-@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 14:15:17 by gcoelho-          #+#    #+#             */
/*   Updated: 2021/10/18 14:15:17 by gcoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*allocate_buffer(char **buffer, int fd);
static char	*check_execution_and_create_empty_line(char **buffer,
				ssize_t *bytes_read, ssize_t *start, int fd);
static char	*copy_from_buffer_to_line_and_find_end_of_line(char **buffer,
				ssize_t *bytes_read, ssize_t *start,
				char **line);

char	*get_next_line(int fd)
{
	static char	*buffer[MAX_FD];
	ssize_t		bytes_read;
	ssize_t		start;
	char		*line;

	if (!allocate_buffer(buffer, fd))
		return (NULL);
	line = check_execution_and_create_empty_line(&(buffer[fd]),
			&bytes_read, &start, fd);
	while (line && bytes_read)
	{
		if (copy_from_buffer_to_line_and_find_end_of_line(&(buffer[fd]),
				&bytes_read, &start, &line))
			break ;
		free(check_execution_and_create_empty_line(&(buffer[fd]),
				&bytes_read, &start, fd));
	}
	if (start == bytes_read)
	{
		buffer[fd] -= start;
		free(--(buffer[fd]));
		buffer[fd] = NULL;
	}
	return (line);
}

static char	*copy_from_buffer_to_line_and_find_end_of_line(char **buffer,
			ssize_t *bytes_read, ssize_t *start, char **line)
{
	size_t	bytes_to_copy;
	size_t	previous_line_len;
	char	*eol;
	char	*previous_line;

	bytes_to_copy = *bytes_read - *start;
	eol = ft_strchr(*buffer, '\n');
	if (eol)
		bytes_to_copy = eol - *buffer + 1;
	previous_line_len = ft_strlen(*line);
	previous_line = *line;
	*line = malloc(previous_line_len + bytes_to_copy + 1);
	if (!*line)
	{
		free(previous_line);
		return (NULL);
	}
	ft_memcpy(*line, previous_line, previous_line_len);
	ft_memcpy(*line + previous_line_len, *buffer, bytes_to_copy);
	(*line)[previous_line_len + bytes_to_copy] = '\0';
	free(previous_line);
	*buffer += bytes_to_copy;
	return (eol);
}

static char	*check_execution_and_create_empty_line(char **buffer,
			ssize_t *bytes_read, ssize_t *start, int fd)
{
	char	*line;
	char	*ptr;

	ptr = *buffer - 1;
	while (*ptr)
		ptr--;
	*bytes_read = ft_strlen(++ptr);
	*start = *buffer - ptr;
	if (!*bytes_read || *start == *bytes_read)
	{
		*buffer = ptr;
		*bytes_read = read(fd, *buffer, BUFFER_SIZE);
		(*buffer)[*bytes_read] = '\0';
		*start = 0;
	}
	if (*bytes_read <= 0 || *bytes_read > BUFFER_SIZE)
	{
		*bytes_read = 0;
		return (NULL);
	}
	line = malloc(1);
	if (!line)
		return (NULL);
	line[0] = '\0';
	return (line);
}

static char	*allocate_buffer(char **buffer, int fd)
{
	if (fd < 0 || fd > MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	if (buffer[fd])
		return (buffer[fd]);
	buffer[fd] = malloc(BUFFER_SIZE + 2);
	if (!buffer[fd])
		return (NULL);
	buffer[fd][0] = '\0';
	buffer[fd][1] = '\0';
	return (buffer[fd]++);
}
