#include "../philosophers.h"

int	main(int argc, char **argv)
{
	t_args			args;
	pthread_mutex_t	*forks;
	t_philo			*philos;

	if (!validate_args(argc, argv) || !init_args(&args, argv))
		return (-1);
	forks = init_forks(&args);
	philos = init_philos(&args, forks);
	if (!thread_handler(&args, philos, forks))
		return (-1);
	cleanup(&args, forks, philos);
	return (-1);
}
