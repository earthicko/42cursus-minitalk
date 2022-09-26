/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigcom_rx_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 00:48:45 by donghyle          #+#    #+#             */
/*   Updated: 2022/09/26 00:48:45 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sigcom_bonus.h"

static void	write_bit(void)
{
	if (g_sigcom.rx_sig == SIGUSR1)
	{
		g_sigcom.mask = ~g_sigcom.mask;
		g_sigcom.buffer &= g_sigcom.mask;
		g_sigcom.mask = ~g_sigcom.mask;
	}
	else
		g_sigcom.buffer |= g_sigcom.mask;
	g_sigcom.mask = (g_sigcom.mask << 1);
}

int	sigcom_action_rx(void)
{
	if (g_sigcom.rx_pid != g_sigcom.peer_pid)
		return (-1);
	write_bit();
	if (g_sigcom.mask == 0)
	{
		if (g_sigcom.buffer == EOT)
		{
			usleep(DELAY_USEC);
			kill(g_sigcom.rx_pid, SIGUSR1);
			sigcom_setstate_ready();
			return (0);
		}
		write(STDOUT_FILENO, &g_sigcom.buffer, 1);
		g_sigcom.mask = 1;
	}
	usleep(DELAY_USEC);
	kill(g_sigcom.rx_pid, SIGUSR1);
	return (0);
}

void	sigcom_setstate_rx(pid_t peer_pid)
{
	g_sigcom.mask = 1;
	g_sigcom.state = STATE_RX;
	g_sigcom.peer_pid = peer_pid;
}
