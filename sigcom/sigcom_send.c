#include <unistd.h>
#include <signal.h>
#include "sigcom.h"
#include "ft_printf.h"

void	sigcom_null_action(int sig)
{
	(void) sig;
}

void	sigcom_init_sender(void)
{
	signal(SIGUSR1, sigcom_null_action);
	signal(SIGUSR2, sigcom_null_action);
}

void	sigcom_send(char byte, pid_t pid)
{
	char	mask;
	int		error;

	sigcom_init_sender();
	ft_printf("Sending %c\n", byte);
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
