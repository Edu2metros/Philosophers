/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:36:21 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/04/04 15:39:03 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*init(char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	fill_info_data(data, argv);
	init_philo_struct(data);
	forks_init(data);
	*control_struct() = data;
	return (data);
}

void	init_philo_struct(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->number_philos);
	while (i < data->number_philos)
	{
		data->philo[i].philo_id = 0;
		data->philo[i].last_time_eat = 0;
		i++;
	}
}
void	ft_bzero(void *s, size_t n)
{
	unsigned char	*c;
	size_t			mem;

	c = (unsigned char *)s;
	mem = 0;
	while (mem < n)
	{
		c[mem] = 0;
		mem++;
	}
}

void	*ft_calloc(size_t nitems, size_t size)
{
	int		*p;
	size_t	overflow;

	overflow = nitems * size;
	if (nitems != 0 && (overflow / nitems) != size)
		return (NULL);
	p = malloc(nitems * size);
	if (p == NULL)
		return (p);
	ft_bzero(p, size * nitems);
	return (p);
}

void forks_init(t_data *data)
{
    int i;

    i = 0;
    data->forks = malloc(sizeof(int) * data->number_philos);
    while (i < data->number_philos)
        data->forks[i++] = 0;
    i = 0;
    data->fork_m = malloc(sizeof(pthread_mutex_t) * data->number_philos);
    while (i < data->number_philos)
    {
        pthread_mutex_init(&data->fork_m[i], NULL);
        i++;
    }
}

