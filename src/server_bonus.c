/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 20:59:10 by abita             #+#    #+#             */
/*   Updated: 2025/09/19 20:59:38 by abita            ###   ########.fr       */
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
			write (1, buffer, i);    // write (STDOUT_FILENO, ....)
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
#include <stdio.h>
static size_t i = 0;
printf("i: %zu\n", i);
i++;



	static unsigned char	bits = 0;
	static int				bit_position = 0;
	static pid_t			client_pid = 0;

	(void) ucontext;
	if (!client_pid)
		client_pid = info->si_pid;
	if (client_pid != info->si_pid)     //  Q? Could this get a second client hung when it sends while the first client is busy?
		return ;
	if (sig == SIGUSR1)
		bits = (bits << 1) | 0;
	else
		bits = (bits << 1) | 1;
	bit_position++;

pid_t tmp_client_pid = client_pid;
	if (bit_position == 8)
	{
		printing(bits);
		if (bits == '\0')
			kill(client_pid, SIGUSR1);
		bits = 0;                            // Probably not needed?
		bit_position = 0;
		client_pid = 0;
	}
kill (tmp_client_pid, SIGUSR2);
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
	{
		sleep (100);
		// pause();
	}
	return (0);
}
