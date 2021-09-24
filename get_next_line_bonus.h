#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <unistd.h>

/* Utils from Libft */
char	*ft_strchr(const char *s, int c);
void	*ft_memcpy(void *dst, const void *src, size_t len);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);

/* Mandatory */
typedef struct s_execution
{
	char	*buffer;
	ssize_t	bytes_read;
	ssize_t	start;
}	t_execution;
char	*get_next_line(int fd);

/* Bonus */

#endif
