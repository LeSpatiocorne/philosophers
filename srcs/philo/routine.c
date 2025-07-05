/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidruon <nidruon@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:40:00 by nidruon           #+#    #+#             */
/*   Updated: 2025/07/04 00:05:53 by nidruon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_dead(t_philo *philo)
{
	long	current_time;
	long	time_since_last_meal;

	current_time = get_time_in_ms();
	pthread_mutex_lock(&philo->meal_mutex);
	time_since_last_meal = current_time - philo->last_meal;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (time_since_last_meal >= philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		if (philo->data->all_alive)
		{
			pthread_mutex_lock(&philo->data->print_mutex);
			printf(RED"%ld %d died\n"RESET,
				timestamp(philo->data->start_time), philo->id);
			pthread_mutex_unlock(&philo->data->print_mutex);
			philo->data->all_alive = 0;
		}
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (1);
	}
	return (0);
}

int	check_alive(t_philo *philo)
{
	int	alive;

	pthread_mutex_lock(&philo->data->death_mutex);
	alive = philo->data->all_alive;
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (alive);
}

int	get_times_eaten(t_philo *philo)
{
	int	times;

	pthread_mutex_lock(&philo->meal_mutex);
	times = philo->times_eaten;
	pthread_mutex_unlock(&philo->meal_mutex);
	return (times);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat / 2);
	while (check_alive(philo))
	{
		philo_eat(philo);
		if (!check_alive(philo))
			break ;
		if (philo->data->must_eat_count > 0
			&& get_times_eaten(philo) >= philo->data->must_eat_count)
			break ;
		philo_sleep(philo);
		if (!check_alive(philo))
			break ;
		philo_think(philo);
	}
	return (NULL);
}

int	start_simulation(t_data *data)
{
	int			i;
	pthread_t	monitor_thread;

	i = -1;
	while (i++, i < data->nb_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				philosopher_routine, &data->philos[i]) != 0)
		{
			printf(RED"Erreur lors de la création du thread %d\n"RESET, i);
			return (0);
		}
	}
	if (pthread_create(&monitor_thread, NULL, monitor_routine, data) != 0)
	{
		printf(RED"Erreur lors de la création du thread"
			"de surveillance\n"RESET);
		return (0);
	}
	i = -1;
	while (i++, i < data->nb_philo)
		pthread_join(data->philos[i].thread, NULL);
	pthread_join(monitor_thread, NULL);
	return (1);
}
