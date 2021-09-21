#include "get_next_line.h"
#include "../00-libft/libft.h"

#include <stdio.h>

char	*get_next_line(int fd)
{
	static char	*buffer;
	char	*aux;
	char	*line;
	static ssize_t	bytes_read;
	char	*new_line;
	size_t	line_len;

	if (!buffer)
		buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	aux = NULL;
	line = ft_strdup("");
	if (!bytes_read || bytes_read == BUFFER_SIZE)
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (!bytes_read)
	{
		free(buffer);
		free(line);
		return (NULL);
	}
	new_line = NULL;
	while (bytes_read)
	{
		if (bytes_read < 0 || bytes_read > BUFFER_SIZE)
		{
			free(buffer);
			free(aux);
			free(line);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		
		new_line = ft_strchr(buffer, '\n');
		if (!new_line)
			new_line = buffer + bytes_read;
		line_len = new_line - buffer + 1;
		aux = malloc(line_len + 1);
		if (!aux)
			return (NULL);
		ft_memcpy(aux, buffer, line_len);
		aux[line_len] = '\0';
		line = ft_strjoin(line, aux);
	
		if (new_line)
		{
			bytes_read = 0;
			continue ;
		}

		bytes_read = read(fd, buffer, BUFFER_SIZE);
		free(aux);
	}
	return (line);
}
