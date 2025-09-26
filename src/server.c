/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 12:14:08 by abita             #+#    #+#             */
/*   Updated: 2025/09/26 21:01:10 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _DEFAULT_SOURCE
#define ARG_MAX 1048576

#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include "ft_printf.h"

static void	printing(unsigned char bits)
{
	static char	buffer[ARG_MAX];
	static int	i = 0;

	if (bits != '\0')
	{
		if (i < ARG_MAX)
			buffer[i++] = bits;
		else
		{
			write (1, buffer, i);
			i = 0;
			buffer[i++] = bits;
		}
	}
	else
	{
		buffer[i] = '\0';
		write(1, buffer, i);
		write(1, "\n", 1);
		i = 0;
	}
}

static void	handler(int sig, siginfo_t *info, void *ucontext)
{
	static unsigned char	bits = 0;
	static int				bit_position = 0;
	static pid_t			client_pid = 0;
	int						reply_signal;
	pid_t					sic_client_pid;

	(void) ucontext;
	if (!client_pid)
		client_pid = info->si_pid;
	if (client_pid != info->si_pid)
		return ;
	bits = (bits << 1) | (sig == SIGUSR2);
	bit_position++;
	reply_signal = SIGUSR2;
	sic_client_pid = client_pid;
	if (bit_position == 8)
	{
		printing(bits);
		if (bits == '\0')
			reply_signal = SIGUSR1;
		bits = 0;
		bit_position = 0;
		client_pid = 0;
	}
	kill (sic_client_pid, reply_signal);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("PID: %d\n", (int)getpid());
	sa.sa_sigaction = &handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		return (write(2, "Error: sigaction\n", 17), -1);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		return (write(2, "Error: sigaction\n", 17), -1);
	while (1)
		;
	return (0);
}
