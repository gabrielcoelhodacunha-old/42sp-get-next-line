#include "get_next_line_bonus.h"

static void	*free_memory(char **one);
static char	*check_execution_and_create_empty_line(char ***buffer, int fd);
static char	*copy_from_buffer_to_line(char ***buffer, char **line);

char	*get_next_line(int fd)
{
	static char	**buffer;
	char	*line;
	ssize_t	bytes_read;
	size_t	buffer_start_idx;

	line = check_execution_and_create_empty_line(&buffer, fd, &bytes_read, &buffer_start_idx);
	while (bytes_read)
	{
		if (copy_from_buffer_to_line(&buffer, &line, bytes_read, &buffer_start_idx))
			return (line);
		if (buffer_start_idx == bytes_read)
		{
			bytes_read = read(fd, buffer, BUFFER_SIZE);
			buffer_start_idx = 0;
		}
		if (bytes_read < 0 || bytes_read > BUFFER_SIZE)
		{
			free(line);
			return (free_memory(&buffer));
		}
	}
	return (line);
}

static char	*copy_from_buffer_to_line(char ***buffer, char **line, ssize_t bytes_read, size_t *buffer_start_idx)
{
	char	*aux;
	char	*previous_line;
	char	*new_line;
	size_t	bytes_to_copy;

	(*buffer)[bytes_read] = '\0';
	new_line = ft_strchr(*buffer + *buffer_start_idx, '\n');
	bytes_to_copy = bytes_read - *buffer_start_idx;
	if (new_line)
		bytes_to_copy = new_line - (*buffer + *buffer_start_idx) + 1;
	aux = malloc(bytes_to_copy + 1);
	if (!aux)
	{
		free(*line);
		return (free_memory(buffer));
	}
	ft_memcpy(aux, *buffer + *buffer_start_idx, bytes_to_copy);
	aux[bytes_to_copy] = '\0';
	previous_line = *line;
	*line = ft_strjoin(previous_line, aux);
	free(aux);
	free(previous_line);
	*buffer_start_idx += bytes_to_copy;
	return (new_line);
}

static char	*check_execution_and_create_empty_line(char ***buffer, int fd, ssize_t *bytes_read, size_t *buffer_start_idx)
{
	char	*line;
	int	fd_idx;
	char	**aux;

	if (!*buffer)
	{
		*buffer = malloc(fd + 2);
		fd_idx = -1;
		while (++fd_idx <= fd)
		{
			(*buffer)[fd_idx] = malloc(BUFFER_SIZE + 1);
			(*buffer)[fd_idx][0] = '\0';
		}
		(*buffer)[fd_idx] = NULL;
	}
	fd_idx = -1;
	while ((*buffer)[++fd_idx])
		;
	if (--fd_idx < fd)
	{
		**aux = *buffer;
		
	}
	if (!*buffer)
		return (NULL);
	*bytes_read = count_bytes_read(*buffer);
	if (!*bytes_read || ex->start == *bytes_read)
	{
		*bytes_read = read(fd, *buffer, BUFFER_SIZE);
		ex->start = 0;
	}
	if (*bytes_read <= 0 || *bytes_read > BUFFER_SIZE)
	{
		*bytes_read = 0;
		return (free_memory(buffer));
	}
	line = malloc(1);
	if (!line)
		return (free_memory(buffer));
	line[0] = '\0';
	return (line);
}

size_t	count_bytes_read(char *buffer)
{
	size_t	bytes_read;

	bytes_read = -1;
	while (buffer[++bytes_read])
		buffer++;
	return (bytes_read);
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
