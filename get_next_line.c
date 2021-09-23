#include "get_next_line.h"
#include "../00-libft/libft.h"

#include <stdio.h>

static void	*free_memory(void *one, void *two, void *three, void *four);

char	*get_next_line(int fd)
{
	static char	*buffer;
	char	*aux;
	static char	*line;
	char	*line_ptr;
	static ssize_t	bytes_read;
	char	*new_line;
	size_t	bytes_to_copy;
	static size_t	start;

	if (!buffer)
		buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free_memory(line, NULL, NULL, NULL));
	if (line)
		free_memory(line, NULL, NULL, NULL);
	line = ft_strdup("");
	if (!line)
		return (free_memory(buffer, NULL, NULL, NULL));
	if (!bytes_read || start == bytes_read)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		start = 0;
	}
	if (bytes_read <= 0 || bytes_read > BUFFER_SIZE)
		return (free_memory(buffer, line, NULL, NULL));
	while (bytes_read)
	{
		buffer[bytes_read] = '\0';
		
		new_line = ft_strchr(buffer + start, '\n');
		bytes_to_copy = bytes_read - start;
		if (new_line)
			bytes_to_copy = new_line - (buffer + start) + 1;
		aux = malloc(bytes_to_copy + 1);
		if (!aux)
			return (free_memory(buffer, line, NULL, NULL));
		ft_memcpy(aux, buffer + start, bytes_to_copy);
		aux[bytes_to_copy] = '\0';
		
		line_ptr = line;
		line = ft_strjoin(line, aux);
		free_memory(aux, line_ptr, NULL, NULL);

		start += bytes_to_copy;
		if (new_line)
			return (line);
		if (start == bytes_read)
		{
			bytes_read = read(fd, buffer, BUFFER_SIZE);
			start = 0;
		}
		if (bytes_read < 0 || bytes_read > BUFFER_SIZE)
			return (free_memory(buffer, line, NULL, NULL));
	}
	return (line);
}

static void	*free_memory(void *one, void *two, void *three, void *four)
{
	free(one);
	free(two);
	free(three);
	free(four);
	one = NULL;
	two = NULL;
	three = NULL;
	four = NULL;
	return (NULL);
}
