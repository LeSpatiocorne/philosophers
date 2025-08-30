/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidruon <nidruon@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:12:20 by nidruon           #+#    #+#             */
/*   Updated: 2025/07/03 23:46:19 by nidruon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_strlen(char *str)
{
	if (!str)
		return (0);
	return (1 + ft_strlen(++str));
}

void	ft_putstr_fd(int fd, char *str)
{
	write(fd, str, ft_strlen(str));
}

static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

long	ft_atol(char *str)
{
	long	result;
	int		i;

	if (!is_valid_number(str))
		return (-1);
	result = 0;
	i = 0;
	while (str[i])
	{
		result = result * 10 + (str[i] - '0');
		if (result > 2147483647)
			return (-1);
		i++;
	}
	return (result);
}

void	print_status(t_philo *philo, char *message, char *color)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->all_alive)
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%s%ld %d %s%s\n",
			color, timestamp(philo->data->start_time),
			philo->id, message, RESET);
		pthread_mutex_unlock(&philo->data->print_mutex);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
}
