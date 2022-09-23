#ifndef SIGCOM_H
# define SIGCOM_H
# define NBIT_PER_BYTE 8
# define DELAY_USECONDS 3000
typedef struct s_sigcom
{
	char	buffer;
	int		cursor;
}	t_sigcom;

extern t_sigcom	g_sigcom;

void	sigcom_init(void);
void	sigcom_send(char byte, pid_t pid);
#endif
