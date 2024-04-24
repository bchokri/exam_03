#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

int ft_strlen(char *str)
{
    int i;

    i = 0;
    if(!str)
        return(0);
    while(str[i])
        i++;
    return(i);
}

char *ft_strjoin(char *s1,char *s2)
{
    int i;
    int j;
    char *result;

    i = 0;
    j = 0;
    if(!s2)
        return(NULL);
    if(!s1)
    {
        s1 = malloc(sizeof(char) * 1);
        s1[0] = '\0';
    }
    result = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
    if(!result)
        return(NULL);
    while (s1[j])
    {
        result[i] = s1[j];
        i++;
        j++;
    }
    j = 0;
    while(s2[j])
    {
        result[i] = s2[j];
        i++;
        j++;
    }
    result[i] = '\0';
    free(s1);
    return(result);
}

static int	ft_searsh(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}



static char	*get_line(char *s)
{
	int		i;
	char	*line;
	int		c;

	i = 0;
	c = 0;
	if (!s[0])
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	while (s[c] && s[c] != '\n')
	{
		line[c] = s[c];
		c++;
	}
	if (s[c] == '\n')
		line[c++] = '\n';
	line[c] = '\0';
	return (line);
}

static char	*update_static(char *s)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\0')
	{
		free(s);
		return (NULL);
	}
	line = malloc(sizeof(char) * (ft_strlen(s) - i));
	if (!line)
		return (NULL);
	i++;
	while (s[i])
		line[j++] = s[i++];
	line[j] = '\0';
	free(s);
	return (line);
}


static char	*get_static(int fd, char *static_str)
{
	ssize_t	readbytes;
	char	*buff;

	readbytes = 1;
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	while (readbytes != 0 && ft_searsh(static_str) == 0)
	{
		readbytes = read(fd, buff, BUFFER_SIZE);
		if (readbytes == -1)
		{
			free(buff);
			free(static_str);
			return (NULL);
		}
		buff[readbytes] = '\0';
		static_str = ft_strjoin(static_str, buff);
	}
	free(buff);
	return (static_str);
}
// 





char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*static_str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	static_str = get_static(fd, static_str);
	if (!static_str)
		return (NULL);
	buffer = get_line(static_str);
	static_str = update_static(static_str);
	return (buffer);
}

// 

// char *update_static(char *str)
// {
//     int i;
//     int j;
//     char *update;

//     i = 0;
//     j = 0;
//     while(str[i] && str[i] != '\n')
//         i++;
// 	if (str[i] == '\0')
// 	{
// 		free(str);
// 		return (NULL);
// 	}
//     update = malloc(sizeof(char) * (ft_strlen(str) - i));
//     if(!update)
//         return(NULL);
//     i++;
//     while (str[i])
//     {
//        update[j] = str[i];
//        i++;
//        j++;
//     }
//     update[j] = '\0';
//     free(str); 
//     return(update);
// }

// int ft_check(char *str)
// {
//     int i;

//     if(!str)
//         return(0);
//     i = 0;
//     while(str[i])
//     {
//         if(str[i] == '\n')
//             return(1);
//         i++;
//     }
//     return(0);
// }




// char *get_line(char *str)
// {
//     int i;
//     int c;
//     char *line;

//     i = 0;
//     c = 0;
// 	if (!str[0])
// 		return (NULL);
//     while(str[i] && str[i] != '\n')
//         i++;
//     if(str[i] == '\n')
//         i++;
//     line = malloc(sizeof(char) * (i + 1));
//     if(!line)
//         return(NULL);
//     while(str[c] && str[c] != '\n')
//     {
//         line[c] = str[c];
//         c++;
//     }
//     if(str[c] == '\n')
//     {
//         line[c] = str[c];
//         c++;
//     }
//     line[c] = '\0';
//     return(line);
// }

// char *get_static(int fd,char *str)
// {
//     ssize_t bytes;
//     char *buffer;

//     buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
//     if(!buffer)
//         return(NULL);
//     bytes = 1;
//     while(bytes != 0 && ft_check(str) == 0)
//     {
//         bytes = read(fd,buffer,BUFFER_SIZE);
//         if(bytes == -1)
//         {
//             free(buffer);
//             free(str);
//             return(NULL);
//         }
//         buffer[BUFFER_SIZE] = '\0';
//         str = ft_strjoin(str,buffer);
//     }
//     free(buffer);
//     return(str);
// }
// char *get_next_line(int fd)
// {
//     static char *str;
//     char *line;

//     if(fd < 0 || BUFFER_SIZE <= 0)
//         return(NULL);
//     str =  get_static(fd,str);
//     if(!str)
//         return(NULL);
//     line = get_line(str);
//     str = update_static(str);
//     return(line);
// }

int main()
{
	int fd  = open("test.txt",O_RDWR,0777);
	char *str = get_next_line(fd);
	printf("%s",str);
	free(str);
	str = get_next_line(fd);
	printf("%s",str);
	free(str);
}

//--------------------prf
// #include<unistd.h>
// #include<stdlib.h>
// #include<stdio.h>
// #include<stdarg.h>

// int ft_len_add(size_t nbr)
// {
//     int i;

//     i = 0;
//     while(nbr > 0)
//     {
//         nbr = nbr / 16;
//         i++;
//     }
//     return(i);
// }
// void ft_putnbr(int n)
// {
//     char c;

//     if(n == -2147483648)
//     {
//         write(1, "-2147483648",11);
//         return ;
//     }
//     if(n < 0)
//     {
//         write(1,"-",1);
//         n = n * -1;
//     }
//     if(n > 9)
//     {
//         ft_putnbr(n/10);
//         ft_putnbr(n%10);
//     }
//     if(n <= 9)
//     {
//         c  = n + 48;
//         write(1,&c,1);
//     }
// }

// int printf_int(int n)
// {
//     int i;
//     int nb;

//     i = 0;
//     nb = n;
//     if(n == -2147483648)
//         i = 11;
//     if(n != -2147483648 )
//     {
//         if(n < 0)
//         {
//             i++;
//             n = n * -1;
//         }
//         while (n > 0 )
//         {
//             n = n / 10;
//             i++;
//         }
//     }
//     ft_putnbr(nb);
//     return(i);
// }

// void ft_putchar(char c)
// {
//     write(1,&c,1);
// }

// int ft_putstr(char *str)
// {
//     int i;
//     int c;

//     i = 0;
//     c = 0;
//     if(!str)
//     {
//         write(1, "(null)",6);
//         return(6);
//     }
//     while(str[i])
//         i++;
//     while(str[c])
//     {
//         ft_putchar(str[c]);
//         c++;
//     }
//     return(i);
// }
// int ft_check(char c)
// {
//     int i;
//     char options[3] = "dsx";

//     i = 0;
//     while(i < 3)
//     {
//         if(options[i] == c)
//             return(i);
//         i++;
//     }
//     return(-1);
// }

// int ft_printadd(size_t nbr)
// {
//     int count;
//     int i;
//     int j;
//     char base[16] = "0123456789abcdef";
//     int nbr_bd[ft_len_add(nbr)];
//     char adresse[ft_len_add(nbr) + 1];

//     count = 0;
//     i = 0;
//     j = 0;
//     count = ft_len_add(nbr);
//    if(count == 0)
//    {
//         write(1,"0",1);
//         return(1);
//    }
//     while(nbr > 0)
//     {   
//         nbr_bd[i] = nbr % 16;
//         nbr = nbr / 16;
//         i++;
//     }
//     i--;
//     while(i >= 0)
//     {
//         adresse[j] = base[nbr_bd[i]];
//         j++;
//         i--;
//     }
//     adresse[j] = '\0';
//     ft_putstr(adresse);
//     return(count);

// }



// int ft_work(va_list list,int i)
// {
//     int count;
//     size_t nbr;

//     count = 0;
//     if(i == 0)
//     {
//         count = printf_int(va_arg(list,int));
//     }
//     if(i == 1)
//     {
//         count = ft_putstr(va_arg(list,char *));
//     }
//     if(i == 2)
//     {
//         nbr = (size_t)va_arg(list,void *);
//         count = ft_printadd(nbr);
//     }
//     return(count);
// }

// int ft_printf(const char *forma, ... )
// {
//     va_list list;
//     int i;
//     int count;

//     i = 0;
//     count = 0;
//     va_start(list,forma);
//     while(forma[i])
//     {
//         if(forma[i] == '%' && ft_check(forma[i + 1]) != -1)
//         {
//             count = count + ft_work(list,ft_check(forma[i + 1]));
//             i++;
//         }
//         else if(forma[i] == '%' && ft_check(forma[i + 1]) == -1)
//         {
//             i++;
//             count++;
//             ft_putchar(forma[i]);
//         }
//         else if(forma[i] == '%')
//             i++;
//         else
//         {
//             count++;
//             ft_putchar(forma[i]);
//         }
//         i++;
//     }
//     va_end(list);
//     return(count);
// }

// int main()
// {
//     // char *str = NULL;
//     int len = ft_printf("%x",1);
//     printf("|%d|\n",len);   
    
// }
