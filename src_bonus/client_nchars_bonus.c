/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_nchars_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 12:03:52 by donghyle          #+#    #+#             */
/*   Updated: 2022/09/25 12:03:53 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extension.h"
#include "sigcom_bonus.h"
#include <stdlib.h>

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
	int		error;
	int		n_chars;
	char	*str;

	if (argc < 3)
		return (0);
	error = ft_atoi_if_valid(argv[1], &pid);
	if (error)
		return (error);
	error = ft_atoi_if_valid(argv[2], &n_chars);
	if (error)
		return (error);
	sigcom_init();
	str = build_str(n_chars);
	if (!str)
		return (-1);
	ft_printf("Sending %s\n", str);
	sigcom_setstate_tx(pid, str);
	return (0);
}
