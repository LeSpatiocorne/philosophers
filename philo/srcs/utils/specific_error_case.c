/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specific_error_case.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidruon <nidruon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 18:27:28 by nidruon           #+#    #+#             */
/*   Updated: 2025/08/30 18:27:29 by nidruon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_putchar_fd(int fd, char c)
{
	write(fd, &c, 1);
}

static void	ft_putnbr_fd(int fd, int n)
{
	if (n < 10)
		ft_putchar_fd(fd, n + '0');
	else
	{
		ft_putnbr_fd(fd, n / 10);
		ft_putchar_fd(fd, n % 10 + '0');
	}
}

void	spfc_err_case(char *str, int n)
{
	ft_putstr_fd(2, str);
	ft_putnbr_fd(2, n);
	ft_putstr_fd(2, "\n");
}
