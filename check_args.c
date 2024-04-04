#include "philo.h"

long	ft_atol(const char *str)
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

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	is_all_digit(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	limit_numbers(char **argv)
{
	int	i;

	i = 1;
	while (argv[i] != NULL)
	{
		if (ft_atol(argv[i]) <= 0 || ft_atol(argv[i]) > __INT_MAX__)
			return (0);
		i++;
	}
	return (1);
}

void	print_stderror(void)
{
	char	*str;

	str = "Error:	Invalid arguments\n"
			"Usage: ./philo number_of_philosophers time_to_die"
			"time_to_eat time_to_sleep"
			"[number_of_times_each_philosopher_must_eat]\n"
			"All arguments must be positive integers\n"
			"Example: ./philo 5 800 200 200\n";
	write(STDERR_FILENO, str, 215);
}

int	check_args(int argc, char **argv)
{
	int flag_error;

	flag_error = 1;
	if (argc != 5 && argc != 6)
		flag_error = 0;
	else if (is_all_digit(argv) == 0)
		flag_error = 0;
	else if (limit_numbers(argv) == 0)
		flag_error = 0;
	if (flag_error == 0)
		print_stderror();
	return (flag_error);
}