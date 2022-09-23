#include <unistd.h>
#include <signal.h>
#include "sigcom.h"
#include <stdio.h>

void	sigcom_send(char byte, pid_t pid)
{
	int		i;
	char	mask;

	printf("Sending %c\n", byte);
	mask = 1;
	i = 0;
	while (i < NBIT_PER_BYTE)
	{
		if (byte & mask)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(DELAY_USECONDS);
		mask = mask << 1;
		i++;
	}
}
