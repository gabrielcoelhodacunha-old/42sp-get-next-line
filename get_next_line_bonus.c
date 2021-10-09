#include "get_next_line_bonus.h"

static char	*check_execution_and_create_empty_line(char **buffer,
			ssize_t *bytes_read, ssize_t *start, int fd);
static char	*copy_from_buffer_to_line_and_find_end_of_line(char *buffer,
			ssize_t *bytes_read, ssize_t *start, char **line);

#ifdef __APPLE__
# define OPEN_MAX 7
#else
# define OPEN_MAX 6
#endif

char	*allocate_buffer(char **buffer, int fd)
{
	if (fd > OPEN_MAX)
		return (NULL);
	if (!buffer[fd])
		buffer[fd] = malloc(BUFFER_SIZE + 1);
	return (buffer[fd]);
}

char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	static ssize_t	bytes_read[OPEN_MAX];
	static ssize_t	start[OPEN_MAX];
	char				*line;

	if (!allocate_buffer(buffer, fd))
		return (NULL);
	line = check_execution_and_create_empty_line(&(buffer[fd]),
			&(bytes_read[fd]), &(start[fd]), fd);
	while (line && bytes_read[fd])
	{
		if (copy_from_buffer_to_line_and_find_end_of_line(buffer[fd],
					&(bytes_read[fd]), &(start[fd]), &line))
			return (line);
		if (start[fd] == bytes_read[fd])
		{
			bytes_read[fd] = read(fd, buffer[fd], BUFFER_SIZE);
			start[fd] = 0;
		}
		if (bytes_read[fd] < 0 || bytes_read[fd] > BUFFER_SIZE)
		{
			free(line);
			return (NULL);
		}
	}
	return (line);
}

static char	*copy_from_buffer_to_line_and_find_end_of_line(char *buffer,
			ssize_t *bytes_read, ssize_t *start, char **line)
{
	size_t	bytes_to_copy;
	size_t	previous_line_len;
	char	*eol;
	char	*previous_line;

	buffer[*bytes_read] = '\0';
	bytes_to_copy = *bytes_read - *start;
	eol = ft_strchr(buffer + *start, '\n');
	if (eol)
		bytes_to_copy = eol - (buffer + *start) + 1;
	previous_line_len = ft_strlen(*line);
	previous_line = *line;
	*line = malloc(previous_line_len + bytes_to_copy + 1);
	if (!*line)
	{
		free(previous_line);
		return (NULL);
	}
	ft_memcpy(*line, previous_line, previous_line_len);
	ft_memcpy(*line + previous_line_len, buffer + *start, bytes_to_copy);
	(*line)[previous_line_len + bytes_to_copy] = '\0';
	free(previous_line);
	*start += bytes_to_copy;
	return (eol);
}

static char	*check_execution_and_create_empty_line(char **buffer,
			ssize_t *bytes_read, ssize_t *start, int fd)
{
	char	*line;

	if (!*bytes_read || *start == *bytes_read)
	{
		*bytes_read = read(fd, *buffer, BUFFER_SIZE);
		*start = 0;
	}
	if (*bytes_read <= 0 || *bytes_read > BUFFER_SIZE)
	{
		*bytes_read = 0;
		free(*buffer);
		*buffer = NULL;
		return (NULL);
	}
	line = malloc(1);
	if (!line)
		return (NULL);
	line[0] = '\0';
	return (line);
}
