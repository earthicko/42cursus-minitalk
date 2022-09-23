#include <signal.h>
#include <unistd.h>
#include "sigcom.h"
#include "ft_printf.h"

t_sigcom	g_sigcom;

void	sigcom_flush_buffer(void)
{
	// ft_printf("flush buffer!\n");
	write(STDOUT_FILENO, &g_sigcom.buffer, 1);
	g_sigcom.cursor = 0;
}

void	sigcom_action_usr1(int sig, siginfo_t *info, void *uap)
{
	char	mask;

	(void) uap;
	(void) info;
	mask = 1 << g_sigcom.cursor;
	if (sig == SIGUSR1)
	{
		mask = ~mask;
		g_sigcom.buffer &= mask;
	}
	else
		g_sigcom.buffer |= mask;
	// ft_printf("Action for SIGUSR: %d\n", sig);
	// ft_printf("info.si_pid=%d\n", info->si_pid);
	// ft_printf("mask:%d\n", mask);
	g_sigcom.cursor++;
	// ft_printf("after %u\n", g_sigcom.buffer);
	if (g_sigcom.cursor == NBIT_PER_BYTE)
		sigcom_flush_buffer();
}

void	sigcom_init(void)
{
	struct sigaction	usr_act;

	usr_act.sa_sigaction = sigcom_action_usr1;
	sigemptyset(&usr_act.sa_mask);
	sigaddset(&usr_act.sa_mask, SIGUSR1);
	sigaddset(&usr_act.sa_mask, SIGUSR2);
	usr_act.sa_flags = SA_SIGINFO;
	usr_act.sa_flags |= SA_NODEFER;
	sigaction(SIGUSR1, &usr_act, NULL);
	sigaction(SIGUSR2, &usr_act, NULL);
	g_sigcom.buffer = 0;
	g_sigcom.cursor = 0;
}
