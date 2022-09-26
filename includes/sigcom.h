/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigcom.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 12:03:35 by donghyle          #+#    #+#             */
/*   Updated: 2022/09/25 12:03:37 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGCOM_H
# define SIGCOM_H
# include "libft.h"
# include <signal.h>
# include <unistd.h>
# define TIMEOUT_USEC 1000000
# define DELAY_USEC 100

typedef struct s_sigcom
{
	char	buffer;
	char	mask;
	int		state;
}	t_sigcom;

enum	e_state
{
	STATE_READY = 0,
	STATE_RX,
	STATE_TX
};

extern t_sigcom	g_sigcom;

void	sigcom_init(void);
void	sigcom_setstate_receive(void);
void	sigcom_init_sender(void);
void	sigcom_send_byte(char byte, pid_t pid);
#endif
