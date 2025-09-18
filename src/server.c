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

#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include "printf/ft_printf.h"

static void handler(int sig)
{
    static unsigned char bits = 0;
    static int bit_position = 0;

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
    pid_t pid;

    pid = getpid();
    ft_printf("%d\n", (int)pid);
    signal(SIGUSR1, handler);
    signal(SIGUSR2, handler);
    while (1)
        pause();
    return (0);
}
