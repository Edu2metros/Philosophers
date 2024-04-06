/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:20:12 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/04/06 18:35:48 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long get_time(void)
{
	struct timeval	time;
	long			result;

	gettimeofday(&time, NULL);
	result = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (result);
}

void print_instance(t_data *data, int id, char *str)
{
	long	time;

	time = get_time() - data->time_init;
	printf("%ld %d %s\n", time, id, str);
}

int	current_status_philo(t_data *data)
{
	int	result;

	result = data->flag_die;
	return (result);
}

int	ft_atoi(const char *str)
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