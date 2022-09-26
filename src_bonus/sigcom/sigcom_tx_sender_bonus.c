/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigcom_tx_sender_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 00:48:54 by donghyle          #+#    #+#             */
/*   Updated: 2022/09/26 00:48:56 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sigcom_bonus.h"

static int	handle_error_kill(char *func)
{
	ft_printf("%s >>> Error while sending signal\n", func);
	return (-1);
}

static int	handle_error_retry(char *func)
{
	ft_printf(MSG_MAX_RETRY_EXCEEDED, func, MAX_RETRY);
	return (-1);
}

static int	send_bit(pid_t pid, int bit)
{
	if (bit)
		return (kill(pid, SIGUSR2));
	else
		return (kill(pid, SIGUSR1));
}

int	sigcom_send_byte(char byte, pid_t pid)
{
	char	mask;
	int		n_retry;

	n_retry = 0;
	mask = 1;
	while (mask != 0)
	{
		if (send_bit(pid, byte & mask) < 0)
			return (handle_error_kill((char *)__func__));
		if (usleep(TIMEOUT_TX_USEC) == 0)
		{
			if (n_retry > MAX_RETRY)
				return (handle_error_retry((char *)__func__));
			ft_printf(MSG_TIMEOUT_EXCEEDED, __func__, TIMEOUT_TX_USEC);
			ft_printf("%s >>> Retrying...\n", __func__);
			n_retry++;
		}
		else
			mask = mask << 1;
	}
	return (0);
}

int	sigcom_send_string(char *str)
{
	int	error;

	while (*str)
	{
		error = sigcom_send_byte(*str, g_sigcom.peer_pid);
		if (error)
			return (error);
		str++;
	}
	error = sigcom_send_byte(EOT, g_sigcom.peer_pid);
	if (error)
		return (error);
	sigcom_setstate_ready();
	return (0);
}
