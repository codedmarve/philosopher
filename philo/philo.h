/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moduwole <moduwole@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 08:32:36 by moduwole          #+#    #+#             */
/*   Updated: 2023/01/20 08:32:36 by moduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define G_BLUE "\e[0;38;5;24m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define RED "\033[0;31m"
# define PINK "\e[0;38;5;199m"
# define RESET "\033[0m"

# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define FORK "has taken a fork"
# define DIED "died"

typedef struct s_data
{
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	int				philo_died;
	long long		time;
	pthread_t		monitor;
	pthread_mutex_t	*mymutex;
	pthread_mutex_t	print;
}		t_data;

typedef struct s_philo
{
	int			id;
	long long	t_die;
	int			n_eaten;
	int			lfork;
	int			rfork;
	pthread_t	th;
	t_data		*data;
}		t_philo;

int			ft_isdigit(int d);
void		*routine(void *arg);
int			philo_eat(t_philo *phi);
int			simulation(t_philo *phi);
int			th_create(t_philo *phi);
int			ft_atoi(const char *str);
int			ft_iscorrect(char **str);
int			checks(int argc, char **argv);
int			init_data(t_data *data, char **argv, int argc);
void		init_philo(t_philo *phi, t_data *data);
int			state_print(t_philo *phi, int id, char *color, char *status);
long long	time_diff(long long time);
void		time_sim(long long time);
int			drop_forks(t_philo *phi);
int			philo_sleep(t_philo *phi);
int			philo_think(t_philo *phi);
void		*routine2(void *args);
int			is_dead(t_philo *phi, int *i);
long long	get_time(void);
void		one_philo(t_data *data, t_philo *phi);
void		free_all(t_data *data, t_philo *phi);

#endif