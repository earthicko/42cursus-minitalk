#include <unistd.h>
#include "sigcom.h"
#include <string.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
		return (0);
	sigcom_init();
	pid = atoi(argv[1]);	// 추후 ft_atoi_if_valid로 에러 처리
	for (size_t i=0;i<strlen(argv[2]);i++)
	{
		sigcom_send(argv[2][i], pid);
	}
	return (0);
}
