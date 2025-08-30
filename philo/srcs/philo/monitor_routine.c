/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidruon <nidruon@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 23:42:30 by nidruon           #+#    #+#             */
/*   Updated: 2025/07/03 23:43:19 by nidruon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	check_philosophers(t_data *data, int *all_satisfied)
{
	int	i;

	i = 0;
	*all_satisfied = 1;
	while (i < data->nb_philo && check_alive(&data->philos[i]))
	{
		if (is_dead(&data->philos[i]))
			break ;
		if (data->must_eat_count > 0
			&& get_times_eaten(&data->philos[i]) < data->must_eat_count)
			*all_satisfied = 0;
		i++;
	}
}

static void	handle_all_satisfied(t_data *data)
{
	pthread_mutex_lock(&data->death_mutex);
	pthread_mutex_lock(&data->print_mutex);
	printf(GREEN"All philosophers have eaten %d times !\n"RESET,
		data->must_eat_count);
	pthread_mutex_unlock(&data->print_mutex);
	data->all_alive = 0;
	pthread_mutex_unlock(&data->death_mutex);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		all_satisfied;

	data = (t_data *)arg;
	while (check_alive(&data->philos[0]))
	{
		check_philosophers(data, &all_satisfied);
		if (data->must_eat_count > 0 && all_satisfied)
		{
			handle_all_satisfied(data);
			break ;
		}
		usleep(50);
	}
	return (NULL);
}
