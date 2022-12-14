/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigcom.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 12:04:11 by donghyle          #+#    #+#             */
/*   Updated: 2022/09/25 12:04:12 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sigcom.h"

t_sigcom	g_sigcom;

void	sigcom_action_receive(int sig, siginfo_t *info, void *uap)
{
	(void) uap;
	g_sigcom.state = STATE_RX;
	if (info->si_pid == 0)
		return ;
	if (sig == SIGUSR1)
	{
		g_sigcom.mask = ~g_sigcom.mask;
		g_sigcom.buffer &= g_sigcom.mask;
		g_sigcom.mask = ~g_sigcom.mask;
	}
	else
		g_sigcom.buffer |= g_sigcom.mask;
	g_sigcom.mask = (g_sigcom.mask << 1);
	if (g_sigcom.mask == 0)
	{
		write(STDOUT_FILENO, &g_sigcom.buffer, 1);
		g_sigcom.mask = 1;
		g_sigcom.state = STATE_READY;
	}
}

void	sigcom_setstate_receive(void)
{
	struct sigaction	usr_act;

	usr_act.sa_sigaction = sigcom_action_receive;
	sigemptyset(&usr_act.sa_mask);
	usr_act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &usr_act, NULL);
	sigaction(SIGUSR2, &usr_act, NULL);
}

void	sigcom_send_byte(char byte, pid_t pid)
{
	char	mask;
	int		error;

	mask = 1;
	while (mask != 0)
	{
		if (byte & mask)
			error = kill(pid, SIGUSR2);
		else
			error = kill(pid, SIGUSR1);
		if (error < 0)
		{
			ft_printf("Error while sending signal, abort\n");
			break ;
		}
		usleep(DELAY_USEC);
		mask = mask << 1;
	}
}

void	sigcom_init(void)
{
	sigcom_setstate_receive();
	g_sigcom.buffer = 0;
	g_sigcom.mask = 1;
	g_sigcom.state = STATE_READY;
}
