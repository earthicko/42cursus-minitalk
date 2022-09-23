#include <unistd.h>
#include "ft_printf.h"

int	main(void)
{
	ft_printf("PID: %d\n", getpid());
	return (0);
}
