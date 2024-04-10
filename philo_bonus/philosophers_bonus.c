/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 18:24:26 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/04/08 15:25:40 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	init_fork_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_philos)
	{
		data->philo[i].pid = fork();
		if (data->philo[i].pid < 0)
			exit(printf("Error: fork\n"));
		if (data->philo[i].pid == 0)
			rotine_philo(&data->philo[i], data);
		i++;
	}
}

static void	kill_all_childs(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_philos)
	{
		kill(data->philo[i].pid, SIGKILL);
		i++;
	}
}

static void	father_process(t_data *data)
{
	int	status;
	int	eat_enough;
	int	i;

	i = 0;
	eat_enough = 0;
	status = EXIT_SUCCESS;
	while (i < data->number_philos)
	{
		waitpid(0, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
		{
			kill_all_childs(data);
			break ;
		}
		else if (WIFEXITED(status) && WEXITSTATUS(status) == EAT_ENOUGH)
			eat_enough++;
		if (eat_enough == data->number_philos_eat)
		{
			kill_all_childs(data);
			break ;
		}
	}
}

static void	finish(t_data *data)
{
	sem_unlink("forks");
	sem_unlink("print");
	sem_close(data->print);
	sem_close(data->forks);
	free(data->philo);
	free(data);
}

void	philosophers(char **argv)
{
	t_data	*data;

	data = init(argv);
	init_fork_philo(data);
	father_process(data);
	finish(data);
}
