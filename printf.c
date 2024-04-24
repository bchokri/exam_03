# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
#include<stdio.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

size_t	ft_size(long n)
{
	int	i;

	i = 0;
	if (n == 0)
	{
		i++;
	}
	if (n < 0)
	{
		i++;
		n = n * -1;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

size_t	ft_putchar_fd(int c, int fd)
{
	if (fd < 0)
		return (0);
	write(fd, &c, 1);
	return (1);
}

size_t	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	if (!fd)
		return (0);
	if (s == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	return (i);
}

void	ft_work_printadd(int i, int j, int *nbr_final, char *base)
{
	if (i == 3)
	{
		ft_putstr_fd("0", 1);
	}
	if (i == 0)
	{
		while (--j >= 0)
			ft_putchar_fd(base[nbr_final[j]], 1);
	}
}

int	ft_size_hexa_me(size_t n)
{
	int	i;

	i = 0;
	if (n == 0)
	{
		i++;
	}
	while (n > 0)
	{
		n = n / 16;
		i++;
	}
	return (i);
}

int	*workon_alloc(char *base, size_t nbr)
{
	int	j;
	int	*nbr_final;
	int	len;

	j = 0;
	len = ft_size_hexa_me(nbr);
	nbr_final = malloc(sizeof(int) * len);
	if (!nbr_final)
		return (NULL);
	while (nbr)
	{
		nbr_final[j] = nbr % ft_strlen(base);
		nbr = nbr / ft_strlen(base);
		j++;
	}
	return (nbr_final);
}

size_t	ft_printadd(size_t nbr, int i)
{
	int		j;
	int		*nbr_final;
	char	*base;

	j = ft_size_hexa_me(nbr);
	base = "0123456789abcdef";
	if (nbr == 0)
		i = 3;
	nbr_final = workon_alloc(base, nbr);
	ft_work_printadd(i, j, nbr_final, base);
	free(nbr_final);
	return (j);
}

size_t	ft_putnbr_fd(int n, int fd)
{
	char	digit;
	size_t	i;

	i = ft_size((long)n);
	if (fd < 0)
		return (0);
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else if (n < 0)
	{
		write(fd, "-", 1);
		n = n * -1;
		ft_putnbr_fd(n, fd);
	}
	else
	{
		digit = n + '0';
		write(fd, &digit, 1);
	}
	return (i);
}



int	ft_check(int c)
{
	char	*str;
	int		i;

	i = 0;
	str = "sdx";
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_workonform(int i, va_list list, int count)
{

	if (i == 0)
		count = count + ft_putstr_fd(va_arg(list, char *), 1);
	else if (i == 1)
		count = count + ft_putnbr_fd(va_arg(list, int), 1);
	else if (i == 2)
		count = count + ft_printadd(va_arg(list, unsigned int), 0);
	return (count);
}

int	ft_short_printf(va_list list, const char *forma, int i, int count)
{
	while (forma[i] != '\0')
	{
		if (forma[i] == '%' && (ft_check(forma[i + 1]) >= 0))
		{
			count = ft_workonform(ft_check(forma[i + 1]), list, count);
			i++;
		}
		else if (forma[i] == '%' && forma[i + 1] != '\0')
		{
			ft_putchar_fd(forma[++i], 1);
			count++;
		}
		else if (forma[i] == '%')
			i++;
		else
		{
			ft_putchar_fd(forma[i], 1);
			count++;
		}
		i++;
	}
	return (count);
}

int	ft_printf(const char *forma, ...)
{
	va_list	list;
	int		i;
	int		count;

	va_start(list, forma);
	count = 0;
	i = 0;
	count = ft_short_printf(list, forma, i, count);
	va_end(list);
	return (count);
}
int main()
{
	printf("--%d\n",ft_printf("%d %s %x\n",5,"aaa",255));
	printf("---%d\n",printf("%d %s %x",5,"aaa",255));
}