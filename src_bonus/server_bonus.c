/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 12:03:59 by donghyle          #+#    #+#             */
/*   Updated: 2022/09/25 12:04:00 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "sigcom_bonus.h"
#include "libft.h"

int	main(void)
{
	ft_printf("PID: %d\n", getpid());
	sigcom_ready_default();
	while (1)
	{
		print_sigcom_state();
		ft_printf("main >>> while loop start\n");
		pause();
	}
	return (0);
}
