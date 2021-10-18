/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcoelho- <gcoelho-@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 14:15:17 by gcoelho-          #+#    #+#             */
/*   Updated: 2021/10/18 14:15:17 by gcoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != c && *s)
		s++;
	if (*s == c)
		return ((char *) s);
	return (NULL);
}

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	unsigned char		*p_dst;
	const unsigned char	*p_src;

	if (!dst && !src)
		return (NULL);
	p_dst = dst;
	p_src = src;
	while (len--)
		*(p_dst++) = *(p_src++);
	return (dst);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}
