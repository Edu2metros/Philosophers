/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 18:24:26 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/04/06 18:32:25 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void child_process(t_data *data)
{
	int i;
	i = 0;
	while (i < data->number_philos)
	{
		if (data->philo[i].pid == 0)
			rotine_philo(&data->philo[i], data);
		i++;
	}

}

static void father_process(t_data *data)
{
    int status;
    int i;
    
    i = 0;
    status = EXIT_SUCCESS;
    while(i < data->number_philos)
    {
        waitpid(0, &status, 0);
        if(WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
        {
            i = 0;
            while(i < data->number_philos)
            {
                kill(data->philo[i].pid, SIGKILL);
                i++;
            }
            break;
        }
    }
}

void philosophers(char **argv)
{
	t_data	*data;

	data = init(argv);
	init_fork_philo(data);
	child_process(data);
	father_process(data);
	//finish
}