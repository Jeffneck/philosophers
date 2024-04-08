# include "../../includes/philosophers.h"

// void	*ft_calloc(size_t bytes)
// {
// 	void	*ret;

// 	ret = malloc(bytes);
// 	memset(&ret, 1, bytes);
// 	return (ret);
// }

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (size != 0 && nmemb > (size_t)(-1) / size)
	{
		return (NULL);
	}
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	return ((void *)memset(ptr, 0, nmemb * size));
}