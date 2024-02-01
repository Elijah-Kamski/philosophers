#include "../../philosophers.h"

// cleans up allocated resources, including mutexes and arrays
void	cleanup(t_args *args, pthread_mutex_t *forks, t_philo *philos)
{
	int	i;

	if (args)
		pthread_mutex_destroy(&args->routine_mutex);
	if (forks)
	{
		i = 0;
		while (i < args->philo_count)
		{
			pthread_mutex_destroy(&forks[i]);
			philos[i].left_fork = NULL;
			philos[i].right_fork = NULL;
			i += 1;
		}
		free(forks);
		forks = NULL;
	}
	if (philos)
	{
		free(philos);
		philos = NULL;
	}
}

// calculates and returns the length of the given string
static size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i += 1;
	return (i);
}

// handles errors by printing an error message and cleaning up
int	error_handler(t_args *args, pthread_mutex_t *forks,
		t_philo *philos, char *error_msg)
{
	cleanup(args, forks, philos);
	write(STDERR_FILENO, "Error: ", 7);
	write(STDERR_FILENO, error_msg, ft_strlen(error_msg));
	write(STDERR_FILENO, "\n", 1);
	return (-1);
}
