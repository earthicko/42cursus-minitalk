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

#include <signal.h>
#include <unistd.h>
#include "sigcom.h"
#include "libft.h"

t_sigcom	g_sigcom;

void	sigcom_receive_action(int sig, siginfo_t *info, void *uap)
{
	(void) uap;
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
	}
	usleep(DELAY_USECONDS);
	kill(info->si_pid, SIGUSR1);
}

void	sigcom_init_receiver(void)
{
	struct sigaction	usr_act;

	usr_act.sa_sigaction = sigcom_receive_action;
	sigemptyset(&usr_act.sa_mask);
	usr_act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &usr_act, NULL);
	sigaction(SIGUSR2, &usr_act, NULL);
}

void	sigcom_null_action(int sig)
{
	(void) sig;
}

void	sigcom_send(char byte, pid_t pid)
{
	char	mask;
	int		error;

	signal(SIGUSR1, sigcom_null_action);
	signal(SIGUSR2, sigcom_null_action);
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
		if (usleep(TIMEOUT_USECONDS) == 0)
			ft_printf("Timeout (%dus) exceeded, retrying\n", TIMEOUT_USECONDS);
		else
			mask = mask << 1;
	}
	sigcom_init_receiver();
}

void	sigcom_init(void)
{
	sigcom_init_receiver();
	g_sigcom.buffer = 0;
	g_sigcom.mask = 1;
}
