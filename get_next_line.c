#include "get_next_line.h"
#include "../00-libft/libft.h"

#include <stdio.h>

static void	*free_memory(void *one, void *two, void *three, void *four);

char	*get_next_line(int fd)
{
	static char	*buffer;
	char	*aux;
	static char	*line;
	static ssize_t	bytes_read;
	static char	*new_line;
	size_t	line_len;
	static size_t	start;

	if (!buffer)
		buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free_memory(line, NULL, NULL, NULL));
	if (line)
		free(line);
	line = ft_strdup("");
	if (!line)
		return (free_memory(buffer, NULL, NULL, NULL));
	if (!bytes_read
		|| (new_line
		&& bytes_read == BUFFER_SIZE))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		start = 0;
	}
	if (!bytes_read)
		return (free_memory(buffer, line, NULL, NULL));
	while (bytes_read)
	{
		if (bytes_read < 0 || bytes_read > BUFFER_SIZE)
			return (free_memory(buffer, aux, line, NULL));
		buffer[bytes_read] = '\0';
		
		new_line = ft_strchr(buffer + start, '\n');
		if (!new_line)
			line_len = bytes_read + 1;
		else
			line_len = new_line - (char *)(buffer + start) + 1;
		aux = malloc(line_len + 1);
		if (!aux)
			return (free_memory(buffer, line, NULL, NULL));
		ft_memcpy(aux, buffer + start, line_len);
		aux[line_len] = '\0';
		if (!ft_strlen(aux))
			return (free_memory(buffer, line, aux, NULL));
		line = ft_strjoin(line, aux);
	
		if (new_line)
		{
			start += line_len;
			free(aux);
			break ;
		}

		bytes_read = read(fd, buffer, BUFFER_SIZE);
		start = 0;
		free(aux);
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
