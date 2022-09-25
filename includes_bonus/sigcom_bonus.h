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
# define TIMEOUT_USECONDS 1000000
# define DELAY_USECONDS 30

typedef struct s_sigcom
{
	char	buffer;
	char	mask;
}	t_sigcom;

extern t_sigcom	g_sigcom;

void	sigcom_init(void);
void	sigcom_init_receiver(void);
void	sigcom_init_sender(void);
void	sigcom_send(char byte, pid_t pid);
#endif