/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigcom_tx_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 00:48:54 by donghyle          #+#    #+#             */
/*   Updated: 2022/09/26 00:48:56 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sigcom_bonus.h"

static int	try_connecting(pid_t peer_pid, int n_retry)
{
	int	error;

	error = kill(peer_pid, SIGUSR1);
	if (error)
	{
		ft_printf("%s >>> Error while sending signal\n", __func__);
		return (-1);
	}
	if (usleep(TIMEOUT_TX_USEC))
		return (0);
	if (n_retry > MAX_RETRY)
	{
		ft_printf(MSG_MAX_RETRY_EXCEEDED, __func__, MAX_RETRY);
		sigcom_setstate_ready();
		return (-1);
	}
	return (1);
}

void	sigcom_setstate_tx(pid_t peer_pid, char *str)
{
	int	error;
	int	n_retry;

	g_sigcom.peer_pid = peer_pid;
	g_sigcom.state = STATE_TX;
	ft_printf("%s >>> Trying to connect to pid %d\n", __func__, peer_pid);
	n_retry = 0;
	while (1)
	{
		error = try_connecting(peer_pid, n_retry);
		if (error < 0)
			return ;
		if (error == 0)
			break ;
		ft_printf(MSG_TIMEOUT_EXCEEDED, __func__, TIMEOUT_TX_USEC);
		ft_printf(", retrying\n");
		n_retry++;
	}
	ft_printf(MSG_CONNECTION_ESTABLISHED, __func__, peer_pid);
	if (sigcom_send_string(str))
		ft_printf("%s >>> Error while sending string\n", __func__);
}
