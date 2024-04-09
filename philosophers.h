/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:56:22 by okrahl            #+#    #+#             */
/*   Updated: 2024/03/22 16:55:02 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_data	t_data;

typedef struct s_philosopher
{
	pthread_t				tid;
	int						index;
	int						meals_eaten;
	long					start_time;
	long					last_meal;
	int						time_to_eat;
	int						time_to_sleep;
	int						time_to_die;
	int						max_meals;
	int						fork_r;
	int						fork_l;
	int						all_here;
	int						num_philosophers;
	pthread_mutex_t			all_here_mutex_p;
	pthread_mutex_t			start_time_mutex_p;
	pthread_mutex_t			last_meal_mutex_p;
	pthread_mutex_t			meals_eaten_mutex_p;
	struct s_philosopher	*next;
	struct s_data			*data;
}				t_philosopher;

struct	s_data
{
	int				all_created;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				max_meals;
	long			start_time;
	int				all_here;
	int				num_philosophers;
	pthread_mutex_t	all_here_mutex;
	pthread_mutex_t	all_created_mutex;
	pthread_mutex_t	max_meals_mutex;
	pthread_mutex_t	start_time_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*fork_mutex;
	t_philosopher	*philosopher;
};

//Activities
int				eat(t_philosopher *philosopher, long start_time);
int				ft_sleep(t_philosopher *philosopher, long start_time);
int				think(t_philosopher *philosopher, long start_time);

//Clean_up
void			clean_up(t_data *data);
void			clean_philosohers(t_philosopher *current_philosopher);

//Handle_Forks
int				take_forks(t_philosopher *philosopher, long start_time);
int				take_first_fork(t_philosopher *philos, \
				long start_time, int first_fork);
int				take_second_fork(t_philosopher *philos, \
				long start_time, int first_fork, int second_fork);
int				give_forks_back(t_philosopher *philosopher);

//Helper
int				assign_first_fork(t_philosopher *philosopher);
int				assign_second_fork(t_philosopher *philosopher);
int				one_finished(t_data *data);
int				ft_atoi(char *str);
void			change_all_here(t_data *data);

//Init_data
t_philosopher	*init_philo(int index, t_data *data);
t_philosopher	*create_philos(int num_philos, t_data *data);
pthread_mutex_t	*init_forks(int count);
void			assign_forks(t_data *data, int num_philosophers);
t_data			*fill_data(int argc, char	**argv);

//Main
int				input_check(int argc, char **argv);
int				main(int argc, char **argv);

//Philosopher
int				no_one_dead(t_data	*data);
int				create_philosopher_threads(t_data *data);
int				join_philosopher_threads(t_data *data);
void			monitor_philosophers(t_data *data);
int				start_philosophers(t_data *data);

//Routine
int				check_all_here(t_philosopher *philosopher);
int				check_all_created(t_data *data);
void			activities_loop(t_philosopher	*philosopher, long start_time);
void			*routine(void *arg);

//Update_time
long			get_timestamp_ms(long start_time);
void			update_starttimes(t_data *data);

//Handle_one
int				handle_solo(t_philosopher *philosopher);

#endif