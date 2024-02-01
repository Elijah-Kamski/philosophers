#include "../../philosophers.h"

// simulates the philosopher's thinking phase.
void	philo_think(t_philo *philo)
{
	routine(philo, THINK);
	usleep(((philo->args->t_to_die - (get_time() 
					- philo->t_since_last_meal)) * MICROSEC) / 2);
}
