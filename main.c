/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:37:43 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/27 17:02:30 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo *philo(void)
{
    static t_philo philo;

    return(&philo); 
}


void check_args(int argc, char **argv)
{
    if (argc != 5 && argc != 6)
    {
        printf("Error\n");
        exit(EXIT_FAILURE);
    }
}

void init(char **argv)
{
    philo()->number_philo = ft_atoi(argv[1]);
    philo()->time_die = ft_atoi(argv[2]);
    philo()->time_eat = ft_atoi(argv[3]);
    philo()->time_sleep = ft_atoi(argv[4]);
    if (argv[5] != NULL)
        philo()->number_philo_must_eat = ft_atoi(argv[5]);
    else
        philo()->number_philo_must_eat = -1;
}

void NAOSEI(void *arg)
{
	
}

void philosophers(void)
{
	pthread_t thread[philo()->number_philo];
	int thread_id[philo()->number_philo];
	int i;
	i = 0;
	while (i < philo()->number_philo)
	{
		thread_id[i] = i;
		pthread_create(&thread[i], NULL, NAOSEI, &thread_id[i]);
		i++;
	}	
}

int main(int argc, char **argv)
{
    check_args(argc, argv);
    init(argv);
	philosophers();
    return EXIT_SUCCESS;
}

