#include <signal.h>
#include <unistd.h>
#include "sigcom.h"
#include "ft_printf.h"

t_sigcom	g_sigcom;

void	sigcom_flush_buffer(void)
{
	// ft_printf("flush buffer!\n");
	// ft_printf("Flush buffer :%c\n", g_sigcom.buffer);
	write(STDOUT_FILENO, &g_sigcom.buffer, 1);
	g_sigcom.cursor = 0;
}

void	sigcom_receive_action(int sig, siginfo_t *info, void *uap)
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
	// ft_printf("Received %d, cursor at %d\n", sig, g_sigcom.cursor);
	// ft_printf("Action for SIGUSR: %d\n", sig);
	// ft_printf("info.si_pid=%d\n", info->si_pid);
	// ft_printf("mask:%d\n", mask);
	g_sigcom.cursor++;
	// ft_printf("after %u\n", g_sigcom.buffer);
	if (g_sigcom.cursor == NBIT_PER_BYTE)
		sigcom_flush_buffer();
	usleep(DELAY_USECONDS);
	kill(info->si_pid, SIGUSR1);
}

void	sigcom_null_action(int sig)
{
	(void) sig;
}

void	sigcom_init_handlers(void)
{
	struct sigaction	usr_act;

	usr_act.sa_sigaction = sigcom_receive_action;
	sigemptyset(&usr_act.sa_mask);
	usr_act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &usr_act, NULL);
	sigaction(SIGUSR2, &usr_act, NULL);
}

void	sigcom_disable_handlers(void)
{
	signal(SIGUSR1, sigcom_null_action);
	signal(SIGUSR2, sigcom_null_action);
}

void	sigcom_init(void)
{
	sigcom_init_handlers();
	g_sigcom.buffer = 0;
	g_sigcom.cursor = 0;
}
