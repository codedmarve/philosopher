/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moduwole <moduwole@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:22:31 by moduwole          #+#    #+#             */
/*   Updated: 2023/02/08 20:22:31 by moduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_eat(t_philo *phi)
{
	pthread_mutex_lock(&phi->data->mymutex[phi->lfork]);
	if (!state_print(phi, phi->id + 1, GREEN, FORK))
		return (drop_forks(phi, 1), 0);
	pthread_mutex_lock(&phi->data->mymutex[phi->rfork]);
	if (!state_print(phi, phi->id + 1, GREEN, FORK))
		return (drop_forks(phi, 2), 0);
	if (!state_print(phi, phi->id + 1, PURPLE, EAT))
		return (drop_forks(phi, 2), 0);
	pthread_mutex_lock(&phi->data->tm);
	phi->t_die = get_time();
	pthread_mutex_unlock(&phi->data->tm);
	time_sim(phi->data->t_eat);
	drop_forks(phi, 2);
	pthread_mutex_lock(&phi->data->shared);
	phi->n_eaten++;
	pthread_mutex_unlock(&phi->data->shared);
	return (1);
}

int	philo_sleep(t_philo *phi)
{
	if (!state_print(phi, phi->id + 1, BLUE, SLEEP))
		return (0);
	time_sim(phi->data->t_sleep);
	return (1);
}

int	philo_think(t_philo *phi)
{
	if (!state_print(phi, phi->id + 1, G_BLUE, THINK))
		return (0);
	return (1);
}

int	is_dead(t_philo *phi, int *i)
{
	int	time;

	if (*i == phi[*i].data->n_philo)
		*i = 0;
	pthread_mutex_lock(&phi->data->tm);
	time = time_diff(phi[*i].t_die);
	if (time > phi[*i].data->t_die)
	{
		pthread_mutex_unlock(&phi->data->tm);
		state_print(&phi[*i], phi[*i].id + 1, RED, DIED);
		pthread_mutex_lock(&phi->data->shared);
		phi[*i].data->philo_died = 1;
		pthread_mutex_unlock(&phi->data->shared);
		return (1);
	}
	pthread_mutex_unlock(&phi->data->tm);
	*i = *i + 1;
	usleep(200);
	return (0);
}
