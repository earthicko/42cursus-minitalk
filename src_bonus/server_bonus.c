/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 12:03:59 by donghyle          #+#    #+#             */
/*   Updated: 2022/09/25 12:04:00 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sigcom_bonus.h"

int	main(void)
{
	int	interrupt;

	ft_printf("PID: %d\n", getpid());
	sigcom_init();
	while (1)
	{
		interrupt = usleep(TIMEOUT_RX_USEC);
		if (interrupt)
		{
			if (g_sigcom.state == STATE_READY)
				sigcom_action_ready();
			else if (g_sigcom.state == STATE_RX)
				sigcom_action_rx();
			else
				return (-1);
		}
		else if (g_sigcom.state != STATE_READY)
		{
			ft_printf(MSG_TIMEOUT_EXCEEDED, __func__, TIMEOUT_RX_USEC);
			sigcom_setstate_ready();
		}
	}
	return (0);
}
