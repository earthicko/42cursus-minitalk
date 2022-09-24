#include <unistd.h>
#include "sigcom.h"
#include "ft_printf.h"

int	main(void)
{
	ft_printf("PID: %d\n", getpid());
	sigcom_init();
	while (1)
		pause();
	return (0);
}
