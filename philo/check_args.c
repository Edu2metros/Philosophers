/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:09:12 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/04/05 14:09:13 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	ft_atol(const char *str)
{
	int		sign;
	long	result;

	sign = 1;
	result = 0;
	while (*str && ((*str == ' ') || (*str >= 9 && *str <= 13)))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str && *str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

static int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

static int	is_all_digit(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	limit_numbers(char **argv)
{
	int	i;

	i = 1;
	while (argv[i] != NULL)
	{
		if (ft_atol(argv[i]) <= 0 || ft_atol(argv[i]) > __INT_MAX__)
			return (0);
		i++;
	}
	return (1);
}

int	check_args(int argc, char **argv)
{
	int	flag_error;

	flag_error = 1;
	if (argc != 5 && argc != 6)
		flag_error = 0;
	else if (is_all_digit(argv) == 0)
		flag_error = 0;
	else if (limit_numbers(argv) == 0)
		flag_error = 0;
	if (flag_error == 0)
		write(2, "Error: Invalid arguments\n", 25);
	return (flag_error);
}
