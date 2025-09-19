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

#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include "ft_printf.h"


void handler(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	static unsigned char bits = 0;
    static int bit_position = 0;
	static int client_pid;
	
	if (!client_pid)
		client_pid = info.si_pid;
    if (sig == SIGUSR1)
        bits = (bits << 1) | 0;
    else
        bits = (bits << 1) | 1;
    bit_position++;
    if (bit_position == 8)
    {
        if (bits != '\0')
            write(1, &bits, 1);
        else
            write(1, "\n", 1);
        bits = 0;
        bit_position = 0;     
    }
}

int main()
{
	struct sigaction sa;

	sa.sa_handler = &handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		return (write(2, "error: sigaction\n", 17), -1);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		return (write(2, "error: sigaction\n", 17), -1);
	ft_printf("%d\n", (int)getpid());
    while (1)
        pause();
    return (0);
}
