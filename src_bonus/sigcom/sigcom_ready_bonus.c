#include <signal.h>
#include <unistd.h>
#include "libft.h"
#include "sigcom_bonus.h"

void	sigcom_receive_action_ready_default(int sig, siginfo_t *info, void *u)
{
	(void) u;
	if (info->si_pid == 0)
		return ;
	ft_printf("sigcom_receive_action_ready_default >>> sig: %d, pid: %d\n", sig, info->si_pid);
	if (sig == SIGUSR1 || sig == SIGUSR2)
	{
		usleep(DELAY_USECONDS);
		kill(info->si_pid, SIGUSR1);
	}
	if (sig == SIGUSR1)
		sigcom_ready(0, info->si_pid, ENQ);
	else if (sig == SIGUSR2)
		sigcom_ready(1, info->si_pid, ENQ);
}

void	sigcom_receive_action_ready(int sig, siginfo_t *info, void *uap)
{
	ft_printf("SIGNAL %d\n", sig);
	(void) uap;
	if (info->si_pid == 0 || info->si_pid != g_sigcom.peer_pid)
		return ;
	ft_printf("sigcom_receive_action_ready >>> before\n");
	print_sigcom_state();
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
		if (g_sigcom.buffer == g_sigcom.expecting)
			g_sigcom.state = STATE_RECEIVE_EXPECTED;
		else
			g_sigcom.state = STATE_RECEIVE_UNEXPECTED;
		g_sigcom.mask = 1;
	}
	ft_printf("sigcom_receive_action_ready >>> after\n");
	print_sigcom_state();
	usleep(DELAY_USECONDS);
	kill(info->si_pid, SIGUSR1);
}

void	sigcom_ready_default(void)
{
	struct sigaction	usr_act;

	g_sigcom.expecting = 0;
	g_sigcom.buffer = 0;
	g_sigcom.mask = 1;
	g_sigcom.state = 0;
	g_sigcom.peer_pid = getpid();
	usr_act.sa_sigaction = sigcom_receive_action_ready_default;
	sigemptyset(&usr_act.sa_mask);
	usr_act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &usr_act, NULL);
	sigaction(SIGUSR2, &usr_act, NULL);
	ft_printf("sigcom_ready_default >>>\n");
	print_sigcom_state();
}

void	sigcom_ready(int last_bit, pid_t peer_pid, char expecting)
{
	struct sigaction	usr_act;
	int					interrupted;

	if (last_bit == 0)
	{
		g_sigcom.mask = ~g_sigcom.mask;
		g_sigcom.buffer &= g_sigcom.mask;
		g_sigcom.mask = ~g_sigcom.mask;
	}
	else
		g_sigcom.buffer |= g_sigcom.mask;
	g_sigcom.mask = g_sigcom.mask << 1;
	g_sigcom.expecting = expecting;
	g_sigcom.peer_pid = peer_pid;
	usr_act.sa_sigaction = sigcom_receive_action_ready;
	sigemptyset(&usr_act.sa_mask);
	usr_act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &usr_act, NULL);
	sigaction(SIGUSR2, &usr_act, NULL);
	ft_printf("sigcom_ready >>> before\n");
	print_sigcom_state();
	interrupted = 1;
	while (!g_sigcom.state && interrupted)
	{
		ft_printf("sigcom_ready >>> while loop start, interrupted: %d\n", interrupted);
		interrupted = usleep(TIMEOUT_RX_USECONDS);
		if (interrupted)
			break ;
	}
	if (!interrupted)
	{
		ft_printf("sigcom_ready >>> timeout\n");
		sigcom_ready_default();
	}
	else
	{
		if (g_sigcom.state == STATE_RECEIVE_EXPECTED)
		{
			ft_printf("sigcom_ready >>> Received expected char\n");
			sigcom_ready_default();
		}
		else
		{
			ft_printf("sigcom_ready >>> Not received expected char\n");
			sigcom_ready_default();
		}
	}
}
