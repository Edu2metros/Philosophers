/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:58:51 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/04/04 19:32:52 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long get_time()
{
    struct timeval current_time;
    long milliseconds;

    gettimeofday(&current_time, NULL);
    milliseconds = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
    return milliseconds;
}

t_data **control_struct(void)
{
    static t_data *result;
    return (&result);
}


void print_instance(t_data *data, int id, char *msg)
{
    long time;
	pthread_mutex_lock(&data->died);
    if (data->flag_die == 1)
	{
		pthread_mutex_unlock(&data->died);
        return;
	}
    time = get_time() - data->time_init;
    printf("%ld %d %s\n", time, id + 1, msg);
	pthread_mutex_unlock(&data->died);
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
