/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 13:43:52 by donghyle          #+#    #+#             */
/*   Updated: 2022/07/08 13:43:53 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf_utils.h"

static size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	idx;

	src_len = ft_strlen(src);
	if (dstsize > 0)
	{
		idx = 0;
		while (src[idx] != '\0' && idx < dstsize - 1)
		{
			dst[idx] = src[idx];
			idx++;
		}
		dst[idx] = '\0';
	}
	return (src_len);
}

char	*ft_strdup(const char *s1)
{
	size_t	l_s1;
	char	*dup;

	l_s1 = ft_strlen(s1);
	dup = (char *)malloc(l_s1 + 1);
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s1, l_s1 + 1);
	return (dup);
}
