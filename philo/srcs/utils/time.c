/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidruon <nidruon@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:47:58 by nidruon           #+#    #+#             */
/*   Updated: 2025/07/03 22:42:17 by nidruon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time_in_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long	timestamp(long start)
{
	return (get_time_in_ms() - start);
}

void	ft_usleep(size_t ms)
{
	size_t	start;
	size_t	elapsed;

	start = get_time_in_ms();
	while ((get_time_in_ms() - start) < ms)
	{
		elapsed = get_time_in_ms() - start;
		if (ms - elapsed > 10)
			usleep(5000);
		else if (ms - elapsed > 5)
			usleep(2000);
		else if (ms - elapsed > 2)
			usleep(1000);
		else if (ms - elapsed > 1)
			usleep(500);
		else if (ms - elapsed > 0)
			usleep(200);
	}
}
