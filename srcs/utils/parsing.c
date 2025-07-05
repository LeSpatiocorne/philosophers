/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidruon <nidruon@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:30:00 by nidruon           #+#    #+#             */
/*   Updated: 2025/07/03 23:38:58 by nidruon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	print_usage(void)
{
	printf(RED"Usage: ./philo [nb_philo] [time_to_die] [time_to_eat]"
		"[time_to_sleep] [must_eat_count(optionnel)]\n"RESET);
	printf("- nb_philo: nombre de philosophes (1-200)\n");
	printf("- time_to_die: temps avant qu'un philosophe meure (en ms)\n");
	printf("- time_to_eat: temps pour manger (en ms)\n");
	printf("- time_to_sleep: temps pour dormir (en ms)\n");
	printf("- must_eat_count: nombre de repas minimum (optionnel)\n");
}

static int	check_arguments(t_data *data, int ac)
{
	if (data->nb_philo <= 0 || data->nb_philo > 200)
	{
		printf(RED"Erreur: Le nombre de philosophes"
			"doit être entre 1 et 200\n"RESET);
		return (0);
	}
	if (data->time_to_die <= 0 || data->time_to_eat <= 0
		|| data->time_to_sleep <= 0)
	{
		printf(RED"Erreur: Tous les temps doivent être positifs\n"RESET);
		return (0);
	}
	if (ac == 6 && data->must_eat_count <= 0)
	{
		printf(RED"Erreur: Le nombre de repas doit être positif\n"RESET);
		return (0);
	}
	return (1);
}

int	parse_arguments(int ac, char **av, t_data *data)
{
	if (ac < 5 || ac > 6)
	{
		print_usage();
		return (0);
	}
	data->nb_philo = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	if (ac == 6)
		data->must_eat_count = ft_atol(av[5]);
	else
		data->must_eat_count = -1;
	return (check_arguments(data, ac));
}
