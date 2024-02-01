#include "../../philosophers.h"
#define THREAD_CREATION_ERROR "Failed to create a thread"
#define THREAD_JOIN_ERROR "Failed to join a thread"

// continuously checks the state of each philosopher in the
// array. If a philosopher is dead or satisfied, it returns from the function.
// If all philosophers are satisfied, it prints a message and returns.
static void	state_checker(t_philo *philos, t_args *args)
{
	int	satisfied_philos;
	int	i;

	satisfied_philos = 0;
	while (true)
	{
		i = -1;
		pthread_mutex_lock(&args->routine_mutex);
		while (++i < args->philo_count)
		{
			if (is_philo_dead_or_fed(args, &philos[i], &satisfied_philos))
				return ;
		}
		if (satisfied_philos == args->philo_count)
			return (everyone_ate_print(args));
		pthread_mutex_unlock(&args->routine_mutex);
	}
}

// creates and joins threads for the philosophers
bool	thread_handler(t_args *args, t_philo *philos, pthread_mutex_t *forks)
{
	int	i;

	i = -1;
	while (++i < args->philo_count)
	{
		philos[i].start_t = get_time();
		if (pthread_create(&philos[i].t_id, NULL,
				action_handler, (void *)&philos[i]) != 0)
		{
			error_handler(args, forks, philos, THREAD_CREATION_ERROR);
			return (false);
		}
	}
	state_checker(philos, args);
	i = -1;
	while (++i < args->philo_count)
	{
		if (pthread_join(philos[i].t_id, NULL) != 0)
		{
			error_handler(args, forks, philos, THREAD_JOIN_ERROR);
			return (false);
		}
	}
	return (true);
}
