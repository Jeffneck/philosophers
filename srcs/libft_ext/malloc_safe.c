# include "../../includes/philosophers.h"

void	*malloc_safe(size_t bytes, void *tofree, char *strerr, void (*f_cleanclose)(void *, char *))
{
	void	*ret;

	ret = malloc(bytes);
	if (NULL == ret)
		f_cleanclose(tofree, strerr);
	return (ret);
}