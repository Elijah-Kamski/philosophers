#include "../../philosophers.h"
#define MALLOC_ERROR "malloc() failed to allocate memory"

// frees mutex forks up to the specified index
static void	free_forks_until(pthread_mutex_t *forks, int until)
{
	int	i;

	i = 0;
	while (i <= until)
	{
		pthread_mutex_destroy(&forks[i]);
		i += 1;
	}
	free(forks);
}

// initializes an array of mutex forks
pthread_mutex_t	*init_forks(t_args *args)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(args->philo_count * sizeof(pthread_mutex_t));
	if (!forks)
		error_handler(args, NULL, NULL, MALLOC_ERROR);
	i = 0;
	while (i < args->philo_count)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			free_forks_until(forks, i);
			error_handler(args, NULL, NULL, MUTEX_INIT_ERROR);
		}
		i += 1;
	}
	return (forks);
}

// initializes an array of philosophers
t_philo	*init_philos(t_args *args, pthread_mutex_t *forks_array)
{
	t_philo	*philos;
	int		i;

	philos = malloc(args->philo_count * sizeof(t_philo));
	if (!philos)
		error_handler(args, forks_array, NULL, MALLOC_ERROR);
	i = 0;
	while (i < args->philo_count)
	{
		philos[i].philo_idx = i + 1;
		philos[i].meals_count = 0;
		philos[i].is_satisfied = 0;
		philos[i].left_fork = &forks_array[i];
		philos[i].right_fork = &forks_array[(i + 1) % args->philo_count];
		philos[i].t_since_last_meal = get_time();
		philos[i].args = args;
		i += 1;
	}
	return (philos);
}
