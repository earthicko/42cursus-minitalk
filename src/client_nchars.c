/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_nchars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 12:03:52 by donghyle          #+#    #+#             */
/*   Updated: 2022/09/25 12:03:53 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "sigcom.h"
#include "ft_atoi_if_valid.h"

static char	*build_str(int n_chars)
{
	int		i;
	char	*str;

	str = (char *)malloc(n_chars + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < n_chars)
	{
		str[i] = (i % 95) + 32;
		i++;
	}
	str[n_chars] = '\0';
	return (str);
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*cursor;
	int		error;
	int		n_chars;
	char	*str;

	if (argc < 3)
		return (0);
	sigcom_init();
	error = ft_atoi_if_valid(argv[1], &pid);
	if (error)
		return (error);
	error = ft_atoi_if_valid(argv[2], &n_chars);
	if (error)
		return (error);
	str = build_str(n_chars);
	cursor = str;
	while (*cursor)
	{
		sigcom_send(*cursor, pid);
		cursor++;
	}
	return (0);
}
