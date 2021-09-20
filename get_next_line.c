#include "get_next_line.h"

#include <stdio.h>

char	*read_line(int fd);

char	*get_next_line(int fd)
{
	char	*line;

	line = read_line(fd);
	return (line);
}

char	*read_line(int fd)
{
	char	*buffer;
	size_t	line_size;

	buffer = malloc(BUFFER_SIZE * sizeof(char));
	if (!buffer || read(fd, buffer, 1) <= 0)
		return (NULL);
	line_size = 0;
	if (BUFFER_SIZE > 1)
	{
		while (line_size < BUFFER_SIZE - 1
			&& read(fd, buffer + line_size, 1) > 0
			&& *(buffer + line_size) != '\n')
			line_size++;
		if (line_size < BUFFER_SIZE
			&& *(buffer + line_size) == '\n')
			*(buffer + line_size++) = '\n';
	}
	*(buffer + line_size) = '\0';
	return (buffer);
}
