#include "get_next_line.h"

typedef struct s_execution
{
	char	*buffer;
	char	*line;
	ssize_t	bytes_read;
	ssize_t	start;
}	t_execution;

static void	*free_memory(char **one, char **two);
static void	*check_for_previous_execution(t_execution *ex, int fd);


char	*get_next_line(int fd)
{
	static t_execution	ex;
	char	*aux;
	char	*line_ptr;
	char	*new_line;
	size_t	bytes_to_copy;

	if (!check_for_previous_execution(&ex, fd))
		return (NULL);
	while (ex.bytes_read)
	{
		ex.buffer[ex.bytes_read] = '\0';
		
		new_line = ft_strchr(ex.buffer + ex.start, '\n');
		bytes_to_copy = ex.bytes_read - ex.start;
		if (new_line)
			bytes_to_copy = new_line - (ex.buffer + ex.start) + 1;
		aux = malloc(bytes_to_copy + 1);
		if (!aux)
			return (free_memory(&ex.buffer, &ex.line));
		ft_memcpy(aux, ex.buffer + ex.start, bytes_to_copy);
		aux[bytes_to_copy] = '\0';
		
		line_ptr = ex.line;
		ex.line = ft_strjoin(line_ptr, aux);
		free_memory(&aux, &line_ptr);

		ex.start += bytes_to_copy;
		if (new_line)
			return (ex.line);
		if (ex.start == ex.bytes_read)
		{
			ex.bytes_read = read(fd, ex.buffer, BUFFER_SIZE);
			ex.start = 0;
		}
		if (ex.bytes_read < 0 || ex.bytes_read > BUFFER_SIZE)
			return (free_memory(&ex.buffer, &ex.line));
	}
	return (ex.line);
}

static void	*check_for_previous_execution(t_execution *ex, int fd)
{
	if (!ex->buffer)
		ex->buffer = malloc(BUFFER_SIZE + 1);
	if (!ex->buffer)
		return (free_memory(&ex->line, NULL));
	if (ex->line)
		free_memory(&ex->line, NULL);
	ex->line = malloc(1);
	if (!ex->line)
		return (free_memory(&ex->buffer, NULL));
	ex->line[0] = '\0';
	if (!ex->bytes_read || ex->start == ex->bytes_read)
	{
		ex->bytes_read = read(fd, ex->buffer, BUFFER_SIZE);
		ex->start = 0;
	}
	if (ex->bytes_read <= 0 || ex->bytes_read > BUFFER_SIZE)
	{
		ex->bytes_read = 0;
		return (free_memory(&ex->buffer, &ex->line));
	}
	return ((void *) 1);
}

static void	*free_memory(char **one, char **two)
{
	if (one)
	{
		free(*one);
		*one = NULL;
	}
	if (two)
	{
		free(*two);
		*two = NULL;
	}
	return (NULL);
}
