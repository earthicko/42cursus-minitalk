/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigcom_ready_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 00:49:03 by donghyle          #+#    #+#             */
/*   Updated: 2022/09/26 00:49:04 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sigcom_bonus.h"

int	sigcom_action_ready(void)
{
	int	error;

	if (g_sigcom.rx_pid == 0)
		return (-1);
	if (g_sigcom.rx_sig == SIGUSR1)
	{
		usleep(DELAY_USEC);
		error = kill(g_sigcom.rx_pid, SIGUSR2);
		if (error)
			return (-1);
		sigcom_setstate_rx(g_sigcom.rx_pid);
	}
	return (0);
}

void	sigcom_setstate_ready(void)
{
	g_sigcom.buffer = 0;
	g_sigcom.mask = 1;
	g_sigcom.state = STATE_READY;
	g_sigcom.peer_pid = getpid();
}
