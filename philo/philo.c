/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:13:12 by tgriblin          #+#    #+#             */
/*   Updated: 2024/02/05 09:23:21 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// tous commencer par penser
// si temps de vie < temps penser + temps manger = DEAD

int	can_eat(t_stats *st, int n)
{
	t_philo	*phi[3];

	if (n == 0)
		phi[0] = st->philos[st->n_philos - 1];
	else
		phi[0] = st->philos[n - 1];
	phi[1] = st->philos[n];
	if (n == st->n_philos - 1)
		phi[2] = st->philos[0];
	else
		phi[2] = st->philos[n + 1];
	if (phi[1]->state == THINKING)
		if (phi[0]->state != EATING && phi[2]->state != EATING)
			return (1);
	return (0);
}

void	*output_thread(void *vargp)
{
	t_stats	*st;
	t_philo	*phi;

	st = (t_stats *)vargp;
	phi = st->philos[st->i];
	phi->state = THINKING;
	put_msg(st, MSG_BORN, st->i + 1);
	return (NULL);
}

void	create_philos(t_stats *st)
{
	st->philos = malloc((st->n_philos + 1) * sizeof(t_philo *));
	st->i = -1;
	st->time_start = get_time();
	while (++st->i < st->n_philos)
	{
		st->philos[st->i] = malloc(sizeof(t_philo));
		pthread_mutex_init(&st->philos[st->i]->fork, NULL);
		pthread_create(&st->philos[st->i]->t, NULL, output_thread, st);
		pthread_join(st->philos[st->i]->t, NULL);
	}
	st->philos[st->i] = NULL;
}
