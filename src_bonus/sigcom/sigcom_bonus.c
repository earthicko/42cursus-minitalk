/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigcom_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 12:04:11 by donghyle          #+#    #+#             */
/*   Updated: 2022/09/25 12:04:12 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "sigcom_bonus.h"
#include "libft.h"

t_sigcom	g_sigcom;

void	sigcom_sigaction(int sig, siginfo_t *info, void *uap)
{
	(void) uap;
	if (sig == 0)
		return ;
	g_sigcom.rx_sig = sig;
	g_sigcom.rx_pid = info->si_pid;
}

void	sigcom_init(void)
{
	struct sigaction	usr_act;

	ft_memset(&g_sigcom, 0, sizeof(t_sigcom));
	sigemptyset(&usr_act.sa_mask);
	usr_act.sa_flags = SA_SIGINFO;
	usr_act.sa_sigaction = sigcom_sigaction;
	sigaction(SIGUSR1, &usr_act, NULL);
	sigaction(SIGUSR2, &usr_act, NULL);
	sigcom_setstate_ready();
}
