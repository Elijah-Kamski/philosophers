#include "../../philosophers.h"

// handles actions for a philosopher
void	*action_handler(void *_philo)
{
	t_philo	*philo;

	philo = (t_philo *)_philo;
	if (philo->args->philo_count == 1)
	{
		routine(philo, START_MEAL);
		return (NULL);
	}
	while (true)
	{
		pthread_mutex_lock(&philo->args->routine_mutex);
		if (philo->args->termination)
		{
			pthread_mutex_unlock(&philo->args->routine_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->args->routine_mutex);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
