#include "../../philosophers.h"

// simulates the philosopher's sleeping period
void	philo_sleep(t_philo *philo)
{
	routine(philo, SLEEP);
	usleep(philo->args->t_to_sleep * MICROSEC);
}
