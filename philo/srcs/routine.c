/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 09:06:36 by tgriblin          #+#    #+#             */
/*   Updated: 2024/03/04 15:43:07 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	ft_usleep_stop(unsigned int ms, t_philo *phi)
{
	unsigned int	start;

	start = get_time();
	pthread_mutex_lock(&phi->eat_mutex);
	while (get_time() - start < ms && !phi->stop)
	{
		pthread_mutex_unlock(&phi->eat_mutex);
		usleep(ms / 10);
		pthread_mutex_lock(&phi->eat_mutex);
	}
	pthread_mutex_unlock(&phi->eat_mutex);
}

static void	*check_death(void *arg)
{
	t_philo	*phi;

	if (!arg)
		return (NULL);
	phi = (t_philo *)arg;
	ft_usleep_stop(phi->all->t_die + 1, phi);
	pthread_mutex_lock(&phi->eat_mutex);
	if (get_time() - phi->last_eat >= phi->all->t_die && !phi->stop)
	{
		pthread_mutex_lock(&phi->all->death_mutex);
		pthread_mutex_lock(&phi->all->kill_mutex);
		if (!phi->all->dead && !phi->stop)
		{
			pthread_mutex_unlock(&phi->all->kill_mutex);
			put_message(MSG_DIE, phi);
			pthread_mutex_lock(&phi->all->kill_mutex);
		}
		phi->all->dead = 1;
		pthread_mutex_unlock(&phi->all->kill_mutex);
		pthread_mutex_unlock(&phi->all->death_mutex);
	}
	pthread_mutex_unlock(&phi->eat_mutex);
	return (NULL);
}

static void	philo_eat(t_philo *phi)
{
	if (phi->i % 2)
	{
		pthread_mutex_lock(&phi->lf);
		put_message(MSG_FORK, phi);
		pthread_mutex_lock(phi->rf);
	}
	else
	{
		pthread_mutex_lock(phi->rf);
		put_message(MSG_FORK, phi);
		pthread_mutex_lock(&phi->lf);
	}
	put_message(MSG_FORK, phi);
	put_message(MSG_EAT, phi);
	pthread_mutex_lock(&phi->eat_mutex);
	phi->last_eat = get_time();
	pthread_mutex_unlock(&phi->eat_mutex);
	if (phi->meals_left > 0)
		phi->meals_left--;
	ft_usleep(phi->all->t_eat);
	pthread_mutex_unlock(phi->rf);
	pthread_mutex_unlock(&phi->lf);
}

void	*routine(void *arg)
{
	t_philo	*phi;

	phi = (t_philo *)arg;
	phi->last_eat = phi->start;
	if (phi->i % 2)
		ft_usleep(phi->all->t_eat);
	while (!phi->all->dead)
	{
		pthread_create(&phi->death_check, NULL, check_death, phi);
		philo_eat(phi);
		if (!phi->meals_left)
		{
			pthread_mutex_lock(&phi->eat_mutex);
			phi->stop = 1;
			pthread_mutex_unlock(&phi->eat_mutex);
			pthread_join(phi->death_check, NULL);
			return (NULL);
		}
		put_message(MSG_SLEEP, phi);
		ft_usleep(phi->all->t_sleep);
		put_message(MSG_THINK, phi);
		pthread_detach(phi->death_check);
	}
	return (NULL);
}
