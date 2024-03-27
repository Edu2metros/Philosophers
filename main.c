/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:37:43 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/27 12:35:13 by eddos-sa         ###   ########.fr       */
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

void init_variable(char **argv)
{
    philo()->number_philo = atoi(argv[1]);
    philo()->time_die = atoi(argv[2]);
    philo()->time_eat = atoi(argv[3]);
    philo()->time_sleep = atoi(argv[4]);
    if (argv[5] != NULL)
        philo()->number_philo_must_eat = atoi(argv[5]);
    else
        philo()->number_philo_must_eat = -1;
}

void init(char **argv)
{
    init_variable(argv);
}

int main(int argc, char **argv)
{
    check_args(argc, argv);
    init(argv);
    return EXIT_SUCCESS;
}

