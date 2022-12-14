/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 12:03:52 by donghyle          #+#    #+#             */
/*   Updated: 2022/09/25 12:03:53 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sigcom_bonus.h"
#include "libft_extension.h"

int	main(int argc, char **argv)
{
	int		pid;
	int		error;
	int		i;

	if (argc < 3)
		return (0);
	error = ft_atoi_if_valid(argv[1], &pid);
	if (error)
		return (error);
	sigcom_init();
	i = 2;
	while (i < argc)
	{
		sigcom_setstate_tx(pid, argv[i]);
		i++;
	}
	return (0);
}
