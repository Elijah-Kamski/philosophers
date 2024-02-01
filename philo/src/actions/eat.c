#include "../../philosophers.h"

// starts the meal for the philosopher
static void	start_meal(t_philo *philo)
{
	if (philo->philo_idx % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		routine(philo, START_MEAL);
		pthread_mutex_lock(philo->right_fork);
		routine(philo, START_MEAL);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		routine(philo, START_MEAL);
		pthread_mutex_lock(philo->left_fork);
		routine(philo, START_MEAL);
	}
}

// ends the meal for the philosopher
static void	end_meal(t_philo *philo)
{
	if (philo->philo_idx % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		routine(philo, END_MEAL);
		pthread_mutex_unlock(philo->right_fork);
		routine(philo, END_MEAL);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		routine(philo, END_MEAL);
		pthread_mutex_unlock(philo->left_fork);
		routine(philo, END_MEAL);
	}
}

// philosopher eats
void	philo_eat(t_philo *philo)
{
	suseconds_t	timestamp;

	timestamp = get_time() - philo->start_t;
	if (philo->has_started == 0)
	{
		printf("%ld %d is thinking\n", timestamp, philo->philo_idx);
		pthread_mutex_lock(&philo->args->routine_mutex);
		philo->has_started = 1;
		pthread_mutex_unlock(&philo->args->routine_mutex);
	}
	start_meal(philo);
	pthread_mutex_lock(&philo->args->routine_mutex);
	philo->t_since_last_meal = get_time();
	pthread_mutex_unlock(&philo->args->routine_mutex);
	routine(philo, EAT);
	usleep(philo->args->t_to_eat * MICROSEC);
	pthread_mutex_lock(&philo->args->routine_mutex);
	philo->meals_count += 1;
	pthread_mutex_unlock(&philo->args->routine_mutex);
	end_meal(philo);
}
