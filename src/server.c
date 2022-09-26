/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 12:03:59 by donghyle          #+#    #+#             */
/*   Updated: 2022/09/25 12:04:00 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sigcom.h"

int	main(void)
{
	int	interrupted;

	ft_printf("PID: %d\n", getpid());
	sigcom_init();
	while (1)
	{
		interrupted = usleep(TIMEOUT_USEC);
		if (!interrupted && g_sigcom.state != STATE_READY)
		{
			ft_printf("Timeout (%dus) while receiving\n", TIMEOUT_USEC);
			sigcom_init();
		}
	}
	return (0);
}
