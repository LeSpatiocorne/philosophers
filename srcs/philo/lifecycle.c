/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidruon <nidruon@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:25:20 by nidruon           #+#    #+#             */
/*   Updated: 2025/07/04 00:03:53 by nidruon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping", BLUE);
	ft_usleep(philo->data->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	long	think_time;

	print_status(philo, "is thinking", MAGENTA);
	if (philo->data->time_to_eat > philo->data->time_to_sleep)
	{
		think_time = (philo->data->time_to_eat - philo->data->time_to_sleep);
		if (think_time > 0)
			ft_usleep(think_time);
	}
	else if (philo->data->nb_philo % 2 == 1)
		ft_usleep(1);
}

static int	take_forks(t_philo *philo, pthread_mutex_t *first_fork,
	pthread_mutex_t *second_fork)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	if (!philo->data->all_alive)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	pthread_mutex_lock(first_fork);
	print_status(philo, "has taken a fork", YELLOW);
	pthread_mutex_lock(second_fork);
	print_status(philo, "has taken a fork", YELLOW);
	pthread_mutex_lock(&philo->data->death_mutex);
	if (!philo->data->all_alive)
	{
		pthread_mutex_unlock(first_fork);
		pthread_mutex_unlock(second_fork);
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (1);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	first_fork = ft_ternary(philo->id % 2 == 0,
			philo->left_fork, philo->right_fork);
	second_fork = ft_ternary(philo->id % 2 == 0,
			philo->right_fork, philo->left_fork);
	if (!take_forks(philo, first_fork, second_fork))
		return ;
	print_status(philo, "is eating", GREEN);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time_in_ms();
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
}
