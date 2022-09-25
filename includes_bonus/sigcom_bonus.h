/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigcom_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 12:03:35 by donghyle          #+#    #+#             */
/*   Updated: 2022/09/25 12:03:37 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGCOM_BONUS_H
# define SIGCOM_BONUS_H
# define TIMEOUT_RX_USECONDS 1000000000
# define TIMEOUT_TX_USECONDS 10000000
# define DELAY_USECONDS 1000000
# define ENQ 0x05
# define STATE_DEFAULT 0
# define STATE_RECEIVE_EXPECTED 1
# define STATE_RECEIVE_UNEXPECTED 2

typedef struct s_sigcom
{
	char	buffer;
	char	mask;
	char	expecting;
	pid_t	peer_pid;
	int		state;
}	t_sigcom;

extern t_sigcom	g_sigcom;

void	sigcom_ready_default(void);
void	sigcom_ready(int last_bit, int sender_pid, char expecting);

void	sigcom_send_byte(char byte, pid_t pid);
void	print_sigcom_state();
#endif
