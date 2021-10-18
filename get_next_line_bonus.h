/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  get_next_line_bonus.h                                :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: gcoelho- <gcoelho-@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:03:12 by gcoelho-          #+#    #+#             */
/*  Updated: 2021/10/18 14:06:24 by gcoelho-           ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <unistd.h>
# ifndef MAX_FD
#  define MAX_FD 256
# endif

/* Utils from Libft */
char	*ft_strchr(const char *s, int c);
void	*ft_memcpy(void *dst, const void *src, size_t len);
size_t	ft_strlen(const char *s);

char	*get_next_line(int fd);

#endif
