/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 12:14:41 by abita             #+#    #+#             */
/*   Updated: 2025/09/11 12:14:43 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <stdlib.h> // malloc, free
# include <unistd.h> // write and standard unix functions, like getpid()
#include <sys/types.h> // various type definitions, like pid_t
# include <signal.h> // signal name macros, and the kill() prototype
# include "libft.h"

struct sigaction {
               void     (*handler)(int);
               void     (*sigaction)(int, siginfo_t *, void *);
               sigset_t   sa_mask;
               int        sa_flags;
               void     (*sa_restorer)(void);
};

// client:
int client(int pid, char **str);



#endif