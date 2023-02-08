/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moduwole <moduwole@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 09:00:13 by moduwole          #+#    #+#             */
/*   Updated: 2023/01/20 09:00:13 by moduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int d)
{
	if (d >= '0' && d <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	long	i;
	long	nbr;

	i = 0;
	nbr = 0;
	if (!str)
		return (nbr);
	while (str[i] != '\0' && (str[i] == ' '
			|| str[i] == '\t' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f'))
			i++;
	if (str[i] == '+')
		i++;
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		nbr = (nbr * 10) + (str[i] - '0');
		i++;
	}
	if (nbr > 2147483647)
		return (0);
	return (nbr);
}

int	ft_iscorrect(char **str)
{
	int		i;
	int		j;
	char	c;

	i = 1;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			c = str[i][j];
			if ((c >= '0' && c <= '9') || c == '+')
			{
				if (c == '+' && (!ft_isdigit(str[i][j + 1]) \
					|| ft_isdigit(str[i][j - 1])))
					return (0);
				j++;
			}
			else
				return (0);
		}
		i++;
	}
	return (1);
}

int	checks(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (printf("Error: arguments must be five or six\n"), 0);
	if (!ft_iscorrect(argv))
		return (printf("Error: some arguments are not unsigned integers\n"), 0);
	return (1);
}
