#include <unistd.h>
#include <signal.h>
#include "sigcom.h"
#include "ft_printf.h"

void	sigcom_send(char byte, pid_t pid)
{
	int		i;
	char	mask;

	sigcom_disable_handlers();
	ft_printf("Sending %c\n", byte);
	mask = 1;
	i = 0;
	while (i < NBIT_PER_BYTE)
	{
		if (byte & mask)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		// if (usleep(TIMEOUT_USECONDS) == 0)
		// {
		// 	printf("interrupt failure\n");
		// 	return ;
		// }
		// ft_printf("sent %dth bit %d\n", i, byte & mask);
		pause();
		mask = mask << 1;
		i++;
	}
	sigcom_init_handlers();
}
