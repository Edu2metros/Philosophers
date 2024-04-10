/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:59:26 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/04/08 15:24:24 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philosophers(char **argv)
{
	t_data		*data;
	pthread_t	*thread_id;
	pthread_t	thread_big_brother;
	int			*philo_id;
	int			i;

	data = init(argv);
	thread_id = (pthread_t *)malloc(data->number_philos * sizeof(pthread_t));
	philo_id = (int *)malloc(data->number_philos * sizeof(int));
	i = 0;
	pthread_create(&thread_big_brother, NULL, big_brother, data);
	if (data->number_philos == 1)
		handle_one_philo(data);
	while (i < data->number_philos)
	{
		philo_id[i] = i;
		pthread_create(&thread_id[i], NULL, routine, &philo_id[i]);
		i++;
	}
	pthread_join(thread_big_brother, NULL);
	finish(data, thread_id);
	free(thread_id);
	free(philo_id);
}

int	main(int argc, char **argv)
{
	if (!check_args(argc, argv))
		return (EXIT_FAILURE);
	philosophers(argv);
	return (EXIT_SUCCESS);
}
