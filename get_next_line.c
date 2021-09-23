#include "get_next_line.h"
#include "../00-libft/libft.h"

#include <stdio.h>

static void	*free_memory(void *one, void *two, void *three, void *four);

char	*get_next_line(int fd)
{
	static char	*buffer;
	static char	*aux;
	static char	*line;
	static char	*line_ptr;
	static ssize_t	bytes_read;
	static char	*new_line;
	static size_t	line_len;
	static size_t	start;

	if (!buffer)
		buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free_memory(line, NULL, NULL, NULL));
	if (line && new_line)
	{
		free(line);
		line = NULL;
		new_line = NULL;
	}
	if (!line )
		line = ft_strdup("");
	if (!line)
		return (free_memory(buffer, NULL, NULL, NULL));
	if (!bytes_read
		//|| (bytes_read == BUFFER_SIZE
		//&& line_len == bytes_read)
		|| bytes_read - line_len - start > 0
		)
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
		line_len = bytes_read - start;
		if (new_line)
			line_len = new_line - (buffer + start) + 1;
		aux = malloc(line_len + 1);
		if (!aux)
			return (free_memory(buffer, line, NULL, NULL));
		ft_memcpy(aux, buffer + start, line_len);
		aux[line_len] = '\0';
		
		line_ptr = line;
		line = ft_strjoin(line, aux);
		free_memory(aux, line_ptr, NULL, NULL);

		/*
		if (new_line && line_len < bytes_read)
			start += line_len - 1;
		else
			start = 0;
		*/
		if (start + line_len < bytes_read)
			start += line_len;
		if (new_line)
		{
			line_len--;
			return (line);
		}
		if (start + line_len == bytes_read)
		{
			bytes_read = read(fd, buffer, BUFFER_SIZE);
			start = 0;
		}
		if (bytes_read < 0 || bytes_read > BUFFER_SIZE)
			return (free_memory(buffer, line, aux, NULL));
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
