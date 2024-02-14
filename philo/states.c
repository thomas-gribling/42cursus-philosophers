/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 10:06:21 by tgriblin          #+#    #+#             */
/*   Updated: 2024/02/14 08:50:30 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *phi)
{
	pthread_mutex_lock(&phi->lf);
	put_message(MSG_FORK, phi);
	pthread_mutex_lock(phi->rf);
	put_message(MSG_FORK, phi);
	put_message(MSG_EAT, phi);
	phi->eating = 1;
	if (phi->meals_left > 0)
		phi->meals_left--;
	ft_usleep(phi->all->t_eat);
	phi->last_eat = get_time();
	pthread_mutex_unlock(phi->rf);
	pthread_mutex_unlock(&phi->lf);
	phi->eating = 0;
}
