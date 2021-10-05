#include "get_next_line.h"

static char	*check_execution_and_create_empty_line(t_execution *ex, int fd);
static char	*copy_from_buffer_to_line_and_find_end_of_line(
				t_execution *ex, char **line);

char	*get_next_line(int fd)
{
	static t_execution	ex;
	char				*line;

	line = check_execution_and_create_empty_line(&ex, fd);
	while (line && ex.bytes_read)
	{
		if (copy_from_buffer_to_line_and_find_end_of_line(&ex, &line))
			return (line);
		if (ex.start == ex.bytes_read)
		{
			ex.bytes_read = read(fd, ex.buffer, BUFFER_SIZE);
			ex.start = 0;
		}
		if (ex.bytes_read < 0 || ex.bytes_read > BUFFER_SIZE)
		{
			free(line);
			return (NULL);
		}
	}
	return (line);
}

static char	*copy_from_buffer_to_line_and_find_end_of_line(
				t_execution *ex, char **line)
{
	size_t	bytes_to_copy;
	size_t	previous_line_len;
	char	*eol;
	char	*previous_line;

	ex->buffer[ex->bytes_read] = '\0';
	bytes_to_copy = ex->bytes_read - ex->start;
	eol = ft_strchr(ex->buffer + ex->start, '\n');
	if (eol)
		bytes_to_copy = eol - (ex->buffer + ex->start) + 1;
	previous_line_len = ft_strlen(*line);
	previous_line = *line;
	*line = malloc(previous_line_len + bytes_to_copy + 1);
	if (!*line)
	{
		free(previous_line);
		return (NULL);
	}
	ft_memcpy(*line, previous_line, previous_line_len);
	ft_memcpy(*line + previous_line_len, ex->buffer + ex->start, bytes_to_copy);
	(*line)[previous_line_len + bytes_to_copy] = '\0';
	free(previous_line);
	ex->start += bytes_to_copy;
	return (eol);
}

static char	*check_execution_and_create_empty_line(t_execution *ex, int fd)
{
	char	*line;

	if (!ex->bytes_read || ex->start == ex->bytes_read)
	{
		ex->bytes_read = read(fd, ex->buffer, BUFFER_SIZE);
		ex->start = 0;
	}
	if (ex->bytes_read <= 0 || ex->bytes_read > BUFFER_SIZE)
	{
		ex->bytes_read = 0;
		return (NULL);
	}
	line = malloc(1);
	if (!line)
		return (NULL);
	line[0] = '\0';
	return (line);
}
