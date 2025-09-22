/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 12:14:08 by abita             #+#    #+#             */
/*   Updated: 2025/09/11 12:14:11 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _DEFAULT_SOURCE
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include "ft_printf.h"

#define BUFFER_SIZE 1024

static void printing(unsigned char bits)
{
    static char buffer[BUFFER_SIZE];
    static int i = 0;

    if (bits != '\0')
    {
        buffer[i++] = bits;
        if (i >= BUFFER_SIZE)
        {
            write(1, &buffer, i);
            i = 0;                  
        }
    }
    else
    {
        buffer[i++] = '\0';
        write(1, &buffer, i);
        write(1, "\n", 1);
        i = 0;
    }
}

static void handler(int sig, siginfo_t *info, void *ucontext)
{
    (void)info;
    (void)ucontext;
    static unsigned char bits = 0;
    static int bit_position = 0;

    if (sig == SIGUSR1)
        bits = (bits << 1) | 0;
    else
        bits = (bits << 1) | 1;
    bit_position++;
    if (bit_position == 8)
    {
        printing(bits);
        bits = 0;
        bit_position = 0;     
    }
}

int main()
{
    struct sigaction sa;

    ft_printf("%d\n", (int)getpid());
	sa.sa_sigaction = &handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		return (write(2, "error: sigaction\n", 17), -1);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		return (write(2, "error: sigaction\n", 17), -1);
    while (1)
        pause();
    return (0);
}
