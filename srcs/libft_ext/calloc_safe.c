# include "../../includes/philosophers.h"

void	*calloc_safe(size_t bytes, void *tofree, char *strerr, void (*f_cleanclose)(void *, char *))
{
	void	*ret;

	ret = malloc(bytes);
	if (NULL == ret)
		f_cleanclose(tofree, strerr);
	memset(&ret, 1, bytes);
	return (ret);
}