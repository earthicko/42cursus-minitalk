#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void	action_1(int sig, siginfo_t *info, void *uap)
{
	(void) uap;

	printf("Action for SIGUSR1\n");
	printf("sig=%d\n", sig);
	printf("info:\n");
	printf("info.si_signo=%d\n", info->si_signo);
	printf("info.si_pid=%d\n", info->si_pid);
}

void	action_2(int sig, siginfo_t *info, void *uap)
{
	(void) uap;

	printf("Action for SIGUSR2\n");
	printf("sig=%d\n", sig);
	printf("info:\n");
	printf("info.si_signo=%d\n", info->si_signo);
	printf("info.si_pid=%d\n", info->si_pid);
}

int main(){
	struct sigaction usract1;
	struct sigaction usract2;

	usract1.sa_sigaction = action_1;
	usract2.sa_sigaction = action_2;
	sigemptyset(&usract1.sa_mask);
	sigemptyset(&usract2.sa_mask);
	usract1.sa_flags = SA_SIGINFO;
	usract2.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &usract1, NULL);
	sigaction(SIGUSR2, &usract2, NULL);
	printf("pid: %d\n", getpid());
	int i = 0;
	while (1)
	{
		printf("%d\n", i);
		sleep(1);
		i++;
	}
	return (0);
}