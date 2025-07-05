/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidruon <nidruon@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:30:01 by nidruon           #+#    #+#             */
/*   Updated: 2025/07/03 23:47:17 by nidruon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	print_welcome(t_data *data)
{
	printf(MAGENTA"=== Dressing Table ===\n"RESET);
	printf("🧠 Philosphers amount: %d\n", data->nb_philo);
	printf("⏰ Time to die: %ld ms\n", data->time_to_die);
	printf("🍽️  Time to eat: %ld ms\n", data->time_to_eat);
	printf("💤 Time to sleep: %ld ms\n", data->time_to_sleep);
	if (data->must_eat_count > 0)
		printf("🔢 Amount of dinners: %d\n", data->must_eat_count);
	else
		printf("🔢 Infinite simulation (no dinners limitation)\n");
	printf(MAGENTA"===================================\n"RESET);
	printf(GREEN"Beginning of the simulation\n\n"RESET);
}

static int	handle_single_philosopher(t_data *data)
{
	printf(YELLOW"0 1 has taken a fork\n"RESET);
	ft_usleep(data->time_to_die);
	printf(RED"%ld 1 died\n"RESET, data->time_to_die);
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (!parse_arguments(ac, av, &data))
		return (1);
	if (data.nb_philo == 1)
		return (handle_single_philosopher(&data));
	if (!init_data(&data))
	{
		ft_putstr_fd(2, RED"Error: Couldn't initialize.\n"RESET);
		return (1);
	}
	print_welcome(&data);
	if (!start_simulation(&data))
	{
		ft_putstr_fd(2, RED"Error: Simulation didn't started\n"RESET);
		cleanup_data(&data);
		return (1);
	}
	cleanup_data(&data);
	printf(BLUE"\nEnd of simulation.\n"RESET);
	return (0);
}
