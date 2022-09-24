#include <unistd.h>
#include "sigcom.h"
#include <string.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	int		pid;
	char	*cursor;
	int		i;

	if (argc < 3)
		return (0);
	sigcom_init();
	pid = atoi(argv[1]);	// 추후 ft_atoi_if_valid로 에러 처리
	i = 2;
	while (i < argc)
	{
		cursor = argv[i];
		while (*cursor)
		{
			sigcom_send(*cursor, pid);
			cursor++;
		}
		i++;
	}
	return (0);
}
