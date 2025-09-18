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

typedef struct s_bits
{
    unsigned char bits;
    int bit_position;
} t_bits;




#endif