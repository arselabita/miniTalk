/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:52:56 by abita             #+#    #+#             */
/*   Updated: 2025/04/29 10:53:03 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count && size && count > SIZE_MAX / size)
		return (NULL);
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}
/*
int main()
{
    int n;
    int i;
    int *ptr;

    n = 5;
    ptr = (int  *)ft_calloc(n, sizeof(int));
    if (ptr)
        printf("Memory successfully allocated!\n");
    i = 0;
    while (i < n)
    {
        printf("%d ", ptr[i]);
        i++;
    }
    free(ptr);
    return (0);
}*/
