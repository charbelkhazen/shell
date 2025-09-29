#include "minishell.h"

char	isquote(char *str)
{
	char	*s;

	s = str;
	while (*s && *(s + 1))
	{
		if (*s == '"')
		{
			while (*s && *(s + 1))
				s++;
			if (*s == '"')
				return (1);
		}
		s++;
	}
	s = str;
	while (*s && *(s + 1))
	{
		if (*s == '\'')
		{
			while (*s && *(s + 1))
				s++;
			if (*s == '\'')
				return (1);
		}
		s++;
	}
	return (0);
}

// char	*removequotes(char *str)
// {
// 	int i = 0;
// 	char *str_1;
// 	char *str_2;
// 	//char *final_str;
// 	while (str[i])
// 	{
// 		if (str[i] == '"')
// 		{
// 			str_1 = ft_substr(str, 0, i);
// 			i++;
// 			while (str[i] && str[i] != '"')
// 				i++;
// 			str_2 = ft_substr(str, str[ft_strlen(str_1)], i);
// 			printf("%s\n", str_2);
// 		}
// 		i++;
// 	}	
// 	return (str_1);
// }

char	*removequotes(char *str)
{
	int		i;
	int		j;
	char	*new;

	new = malloc(ft_strlen(str) + 1);
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
			new[j++] = str[i];
		i++;
	}
	new[j] = '\0';
	return (new);
}

int main()
{
	char *str = "ji\"had\"";
	printf("%d\n", isquote(str));
	char *new_str = removequotes(str);
	printf("%s\n", new_str);
	if (removequotes(str))
		free(new_str);
}