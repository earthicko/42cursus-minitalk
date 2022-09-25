#include "libft.h"
#include "sigcom_bonus.h"

void	print_sigcom_state()
{
	char	mask;

	mask = 1;
	ft_printf("|| SIGCOM STATE\n");
	ft_printf("|| buff: [");
	while (mask)
	{
		ft_printf("%d ", mask & g_sigcom.buffer);
		mask = (mask << 1);
	}
	ft_printf("] [%c] (%#x) (%d)\n", g_sigcom.buffer, g_sigcom.buffer, g_sigcom.buffer);
	ft_printf("|| mask: [");
	mask = 1;
	while (mask)
	{
		ft_printf("%d ", mask & g_sigcom.mask);
		mask = (mask << 1);
	}
	ft_printf("] (%#x)\n", g_sigcom.mask);
	ft_printf("|| expecting [%c] (%d)\n", g_sigcom.expecting, g_sigcom.expecting);
	ft_printf("|| peer PID: %d\n", g_sigcom.peer_pid);
	ft_printf("|| state: %d\n", g_sigcom.state);
}
