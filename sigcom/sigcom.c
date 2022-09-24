#include <signal.h>
#include <unistd.h>
#include "sigcom.h"
#include "ft_printf.h"

t_sigcom	g_sigcom;

void	sigcom_flush_buffer(void)
{
	write(STDOUT_FILENO, &g_sigcom.buffer, 1);
	g_sigcom.mask = 1;
}

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
		sigcom_flush_buffer();
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

void	sigcom_init(void)
{
	sigcom_init_receiver();
	g_sigcom.buffer = 0;
	g_sigcom.mask = 1;
}
