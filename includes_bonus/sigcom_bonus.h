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
# include <signal.h>
# define SIGCOM_BONUS_H

# define TIMEOUT_RX_USEC 2000000
# define TIMEOUT_TX_USEC 1000000
# define DELAY_USEC 100
# define MAX_RETRY 5

# define EOT 0x04

# define MSG_TIMEOUT_EXCEEDED "%s >>> Timeout (%dus) exceeded\n"
# define MSG_MAX_RETRY_EXCEEDED "%s >>> Max retry (%d) exceeded\n"
# define MSG_CONNECTION_ESTABLISHED "%s >>> Connection established with pid %d\n"

enum	e_state
{
	STATE_READY = 0,
	STATE_RX,
	STATE_TX
};

typedef struct s_sigcom
{
	char	buffer;
	char	mask;
	pid_t	peer_pid;
	int		state;
	int		sig;
	pid_t	si_pid;
}	t_sigcom;

extern t_sigcom	g_sigcom;

void	sigcom_init(void);
void	sigcom_sigaction(int sig, siginfo_t *info, void *uap);

void	sigcom_setstate_ready(void);
void	sigcom_setstate_rx(pid_t peer_pid);
void	sigcom_setstate_tx(pid_t peer_pid, char *str);

int		sigcom_action_ready(void);
int		sigcom_action_rx(void);

int		sigcom_send_string(char *str);
int		sigcom_send_byte(char byte, pid_t pid);
void	print_sigcom_state(void);
#endif
