#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <sys/time.h>
# include <pthread.h>
# include <memory.h>

# define MICROSEC 1000
# define MUTEX_INIT_ERROR "Failed to initialize mutex"

typedef struct s_args {
	int					philo_count;
	int					t_to_die;
	int					t_to_eat;
	int					t_to_sleep;
	int					must_eat_times;
	pthread_mutex_t		routine_mutex;
	bool				termination;
}				t_args;

typedef struct s_philo {
	int					philo_idx;
	int					meals_count;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	suseconds_t			t_since_last_meal;
	pthread_t			t_id;
	suseconds_t			start_t;
	t_args				*args;
	bool				is_satisfied;
	bool				has_started;
}				t_philo;

typedef enum e_event_id {
	DEAD,
	EAT,
	THINK,
	SLEEP,
	START_MEAL,
	END_MEAL,
}				t_event_id;

pthread_mutex_t		*init_forks(t_args *args);
t_philo				*init_philos(t_args *args, pthread_mutex_t *forks_array);
bool				thread_handler(t_args *args, t_philo *philos,
						pthread_mutex_t *forks);
void				*action_handler(void *_philo);
void				routine(t_philo *philo, t_event_id event_id);
void				philo_eat(t_philo *philo);
void				philo_sleep(t_philo *philo);
void				philo_think(t_philo *philo);
void				everyone_ate_print(t_args *args);
bool				has_starved(t_philo *philo);
bool				is_philo_dead_or_fed(t_args *args,
						t_philo *philo, int *satisfied_philos);
bool				is_digit(char c);
bool				ft_are_digits(char **argv);
bool				validate_args(int argc, char **argv);
bool				init_args(t_args *args, char **argv);
suseconds_t			get_time(void);
int					error_handler(t_args *args, pthread_mutex_t *forks,
						t_philo *philos, char *error_msg);
void				cleanup(t_args *args, pthread_mutex_t *forks,
						t_philo *philos);
int					ft_atoi(char *str);

#endif
