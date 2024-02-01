#include "../../philosophers.h"

#define EAT_STR "is eating\n"
#define THINK_STR "is thinking\n"
#define SLEEP_STR "is sleeping\n"
#define DEAD_STR "died\n"

// prints the timestamp, philosopher's ID, and the corresponding
// event (such as eating, thinking, sleeping, or a termination event).
void	routine(t_philo *philo, t_event_id event_id)
{
	suseconds_t	timestamp;
	const char	*events[4] = {DEAD_STR, EAT_STR, THINK_STR, SLEEP_STR};

	pthread_mutex_lock(&philo->args->routine_mutex);
	if (philo->args->termination)
	{
		pthread_mutex_unlock(&philo->args->routine_mutex);
		return ;
	}
	timestamp = get_time() - philo->start_t;
	if (event_id == 0 || event_id == 1 || event_id == 2 || event_id == 3)
		printf("%ld %d %s", timestamp, philo->philo_idx, events[event_id]);
	pthread_mutex_unlock(&philo->args->routine_mutex);
}
