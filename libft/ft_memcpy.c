#include "libft.h"

void	*memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!src || !dest)
		return (NULL);
	i = 0;
	if (dest != src)
	{
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];	
			i++;
		}
		dest[i] = '\0';
	}
}
