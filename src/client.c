/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
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
#include "minitalk.h"

int	main(int argc, char **argv)
{
	int		pid;
	char	*cursor;
	int		i;
	int		error;

	if (argc < 3)
		return (0);
	sigcom_init();
	error = ft_atoi_if_valid(argv[1], &pid);
	if (error)
		return (error);
	i = 2;
	while (i < argc)
	{
		cursor = argv[i];
		while (*cursor)
		{
			sigcom_send(*cursor, pid);
			cursor++;
		}
		i++;
	}
	return (0);
}
