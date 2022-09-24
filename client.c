#include <unistd.h>
#include "sigcom.h"
#include <string.h>
#include <stdlib.h>
#include "ft_printf.h"

int	main(int argc, char **argv)
{
	int		pid;
	// char	*cursor;

	if (argc != 3)
		return (0);
	sigcom_init();
	pid = atoi(argv[1]);	// 추후 ft_atoi_if_valid로 에러 처리
	// cursor = argv[2];
	// while (*cursor)
	// {
	// 	sigcom_send(*cursor, pid);
	// 	cursor++;
	// }
	int i = 0;
	char c = 'a' - 1;
	while (1)
	{
		c++;
		ft_printf("%d\n", i++);
		sigcom_send(c, pid);
		if (c == 'z')
			c = 'a' - 1;
	}
	return (0);
}
