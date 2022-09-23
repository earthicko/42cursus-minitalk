#ifndef SIGCOM_H
# define SIGCOM_H
# define NBIT_PER_BYTE 8
typedef struct s_sigcom
{
	char	buffer;
	int		cursor;
}	t_sigcom;

extern t_sigcom	g_sigcom;

void	sigcom_init(void);
#endif
