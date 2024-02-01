#include "../../philosophers.h"

// prints a message when all philosophers have eaten
void	everyone_ate_print(t_args *args)
{
	args->termination = true;
	printf("Every Philosopher ate %d times!\n", args->must_eat_times);
	pthread_mutex_unlock(&args->routine_mutex);
}

// checks if a philosopher has starved
bool	has_starved(t_philo *philo)
{
	return (((get_time() - philo->t_since_last_meal)
			>= philo->args->t_to_die));
}

// checks if a philosopher is dead or satisfied
bool	is_philo_dead_or_fed(t_args *args,
				t_philo *philo, int *satisfied_philos)
{
	if (args->must_eat_times > 0 && philo->meals_count >= args->must_eat_times)
	{
		if (!philo->is_satisfied)
		{
			*satisfied_philos += 1;
			philo->is_satisfied = true;
		}
	}
	if (has_starved(philo))
	{
		pthread_mutex_unlock(&args->routine_mutex);
		routine(philo, DEAD);
		pthread_mutex_lock(&args->routine_mutex);
		args->termination = true;
		pthread_mutex_unlock(&args->routine_mutex);
		return (true);
	}
	return (false);
}
