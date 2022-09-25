#include <signal.h>
#include <unistd.h>
#include "sigcom_bonus.h"
#include "libft.h"

void	sigcom_null_action(int sig)
{
	(void) sig;
}

void	sigcom_send_byte(char byte, pid_t pid)
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
		if (usleep(TIMEOUT_TX_USECONDS) == 0)
			ft_printf("Timeout (%dus) exceeded, retrying\n", TIMEOUT_TX_USECONDS);
		else
			mask = mask << 1;
	}
	// sigcom_init_receiver();
}
