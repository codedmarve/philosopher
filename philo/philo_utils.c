/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moduwole <moduwole@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:21:18 by moduwole          #+#    #+#             */
/*   Updated: 2023/02/08 20:21:18 by moduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	state_print(t_philo *phi, int id, char *color, char *status)
{
	long long	now;

	now = time_diff(phi->data->time);
	pthread_mutex_lock(&phi->data->print);
	pthread_mutex_lock(&phi->data->shared);
	if (phi->data->philo_died)
	{
		pthread_mutex_unlock(&phi->data->shared);
		pthread_mutex_unlock(&phi->data->print);
		return (0);
	}
	else
		printf("%s%-10lld %-3d %-30s%s\n", color, now, id, status, RESET);
	pthread_mutex_unlock(&phi->data->shared);
	pthread_mutex_unlock(&phi->data->print);
	return (1);
}

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec * 0.001));
}

long long	time_diff(long long time)
{
	if (time > 0)
		return (get_time() - time);
	return (0);
}

void	time_sim(long long time)
{
	usleep(time * 1000);
}

void	free_all(t_data *data, t_philo *phi)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
		pthread_mutex_destroy(data->mymutex + i);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->shared);
	pthread_mutex_destroy(&data->tm);
	free(data->mymutex);
	free(data);
	free(phi);
}
