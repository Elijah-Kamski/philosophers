#include "../../philosophers.h"
#define ARG_ERROR "philo_counts and must_eat_times must be bigger than 0"
#define ARGS_ERROR "Invalid arguments"

// validates command-line arguments
bool	validate_args(int argc, char **argv)
{
	if ((argc != 5 && argc != 6) || !ft_are_digits(argv))
	{
		error_handler(NULL, NULL, NULL, ARGS_ERROR);
		printf("Argument must use following format:\n"
			"n_philos t_to_die t_to_eat t_to_sleep [times_philo_must_eat] \n");
		printf("Recommended t_to_die >= (t_to_eat + t_to_sleep + 10)\n");
		return (false);
	}
	return (true);
}

// initializes the arguments structure
bool	init_args(t_args *args, char **argv)
{
	args->philo_count = ft_atoi(argv[1]);
	args->t_to_die = ft_atoi(argv[2]);
	args->t_to_eat = ft_atoi(argv[3]);
	args->t_to_sleep = ft_atoi(argv[4]);
	args->must_eat_times = -1;
	if (argv[5])
		args->must_eat_times = ft_atoi(argv[5]);
	if (args->philo_count == 0 || args->must_eat_times == 0)
	{
		error_handler(NULL, NULL, NULL, ARG_ERROR);
		return (false);
	}
	if (pthread_mutex_init(&args->routine_mutex, NULL) != 0)
	{
		error_handler(NULL, NULL, NULL, MUTEX_INIT_ERROR);
		return (false);
	}
	args->termination = false;
	return (true);
}
