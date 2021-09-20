#include "get_next_line.h"

#include <stdio.h>

ssize_t	fill_buffer(char **buffer, int fd);
char	*get_content(char *buffer);

char	*get_next_line(int fd)
{
	char	*buffer;
	char	*line;

	bytes_read = fill_buffer(&buffer, fd);
	line = get_content(buffer);
	while (!ft_strrchr(line, '\n'))
	{
	}
	free(buffer);
	return (line);
}

char	*get_content(char *buffer)
{
	size_t	idx;
	char	*content;

	idx = -1;
	while (buffer[++idx])
		;
	content = malloc((idx + 1) * sizeof(char));
	if (!content)
		return (NULL);
	idx = -1;
	while (buffer[++idx])
		content[idx] = buffer[idx];
	return (content);
}

ssize_t	fill_buffer(char **buffer, int fd)
{
	ssize_t	bytes_read;

	*buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!*buffer)
		return (NULL);
	bytes_read = read(fd, *buffer, BUFFER_SIZE);
	if (bytes_read <= 0 || bytes_read > BUFFER_SIZE)
	{
		free(*buffer);
		return (NULL);
	}
	(*buffer)[bytes_read] = '\0';
	return (bytes_read);
}
