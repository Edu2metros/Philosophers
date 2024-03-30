/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:56:12 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/30 13:40:26 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;

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

t_philo	*philo(void)
{
	static t_philo	philo;

	return (&philo);
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	print_stderror(void)
{
	char	*str;

	str = "Error:	Invalid arguments\n"
		"Usage: ./philo number_of_philosophers time_to_die"
		"time_to_eat time_to_sleep"
		"[number_of_times_each_philosopher_must_eat]\n"
		"All arguments must be positive integers\n"
		"Example: ./philo 5 800 200 200\n";
	write(STDERR_FILENO, str, 215);
}

int	is_all_digit(char **argv)
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
