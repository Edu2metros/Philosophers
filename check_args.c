/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddos-sa <eddos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 13:30:30 by eddos-sa          #+#    #+#             */
/*   Updated: 2024/03/30 13:42:02 by eddos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int argc, char **argv)
{
	int	error;

	error = 1;
	if (argc != 5 && argc != 6)
		error = 0;
	else if (ft_atoi(argv[1]) < 1)
		error = 0;
	else if (ft_atoi(argv[2]) < 1)
		error = 0;
	else if (ft_atoi(argv[3]) < 1)
		error = 0;
	else if (ft_atoi(argv[4]) < 1)
		error = 0;
	else if (argc == 6 && ft_atoi(argv[5]) < 1)
		error = 0;
	else if (!is_all_digit(argv))
		error = 0;
	if (!error)
		print_stderror();
	return (error);
}
