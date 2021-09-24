#include "get_next_line.h"

static void	*free_memory(char **one);
static char	*check_execution_and_create_empty_line(t_execution *ex, int fd);
static char	*copy_from_buffer_to_line(t_execution *ex, char **line);

char	*get_next_line(int fd)
{
	static t_execution	ex;
	char				*line;

	line = check_execution_and_create_empty_line(&ex, fd);
	while (ex.bytes_read)
	{
		if (copy_from_buffer_to_line(&ex, &line))
			return (line);
		if (ex.start == ex.bytes_read)
		{
			ex.bytes_read = read(fd, ex.buffer, BUFFER_SIZE);
			ex.start = 0;
		}
		if (ex.bytes_read < 0 || ex.bytes_read > BUFFER_SIZE)
		{
			free(line);
			return (free_memory(&ex.buffer));
		}
	}
	return (line);
}

static char	*copy_from_buffer_to_line(t_execution *ex, char **line)
{
	char	*aux;
	char	*previous_line;
	char	*new_line;
	size_t	bytes_to_copy;

	ex->buffer[ex->bytes_read] = '\0';
	new_line = ft_strchr(ex->buffer + ex->start, '\n');
	bytes_to_copy = ex->bytes_read - ex->start;
	if (new_line)
		bytes_to_copy = new_line - (ex->buffer + ex->start) + 1;
	aux = malloc(bytes_to_copy + 1);
	if (!aux)
	{
		free(*line);
		return (free_memory(&ex->buffer));
	}
	ft_memcpy(aux, ex->buffer + ex->start, bytes_to_copy);
	aux[bytes_to_copy] = '\0';
	previous_line = *line;
	*line = ft_strjoin(previous_line, aux);
	free(aux);
	free(previous_line);
	ex->start += bytes_to_copy;
	return (new_line);
}

static char	*check_execution_and_create_empty_line(t_execution *ex, int fd)
{
	char	*line;

	if (!ex->buffer)
		ex->buffer = malloc(BUFFER_SIZE + 1);
	if (!ex->buffer)
		return (NULL);
	if (!ex->bytes_read || ex->start == ex->bytes_read)
	{
		ex->bytes_read = read(fd, ex->buffer, BUFFER_SIZE);
		ex->start = 0;
	}
	if (ex->bytes_read <= 0 || ex->bytes_read > BUFFER_SIZE)
	{
		ex->bytes_read = 0;
		return (free_memory(&ex->buffer));
	}
	line = malloc(1);
	if (!line)
		return (free_memory(&ex->buffer));
	line[0] = '\0';
	return (line);
}

static void	*free_memory(char **one)
{
	if (one)
	{
		free(*one);
		*one = NULL;
	}
	return (NULL);
}
