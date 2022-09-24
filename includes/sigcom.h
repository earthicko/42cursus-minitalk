#ifndef SIGCOM_H
# define SIGCOM_H
# define NBIT_PER_BYTE 8
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
