/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:58:51 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/04/04 14:05:54 by eddos-sa         ###   ########.fr       */
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
    if (data->flag_die == 1)
        return;
    time = get_time() - data->time_init;
    printf("%ld %d %s\n", time, id, msg);
}

void fill_info_data(t_data *data, char **argv)
{
    data->number_philos = ft_atoi(argv[1]) + 1;
    data->time_die = ft_atoi(argv[2]);
    data->time_eat = ft_atoi(argv[3]);
    data->time_sleep = ft_atoi(argv[4]);
    if (argv[5] != NULL)
        data->number_philos_eat = ft_atoi(argv[5]);
    else
        data->number_philos_eat = -1;
    data->flag_die = 0;
    data->time_init = get_time();
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
