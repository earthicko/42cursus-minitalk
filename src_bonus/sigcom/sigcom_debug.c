/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigcom_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 00:49:10 by donghyle          #+#    #+#             */
/*   Updated: 2022/09/26 00:49:11 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sigcom_bonus.h"

static void	print_byte_binary(char c)
{
	char	mask;

	mask = 1;
	while (mask)
	{
		if (mask & c)
			ft_printf("1 ");
		else
			ft_printf("0 ");
		mask = (mask << 1);
	}
}

void	print_sigcom_state(void)
{
	char	buffer;

	buffer = g_sigcom.buffer;
	ft_printf("    || SIGCOM STATE\n");
	ft_printf("    || buff: [");
	print_byte_binary(buffer);
	ft_printf("] [%c] (%#x) (%d)\n", buffer, buffer, buffer);
	ft_printf("    || mask: [");
	print_byte_binary(g_sigcom.mask);
	ft_printf("] (%#x)\n", g_sigcom.mask);
	ft_printf("    || peer PID: %d\n", g_sigcom.peer_pid);
	ft_printf("    || state: %d\n", g_sigcom.state);
}
