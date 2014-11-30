#ifndef UTILS_H
#define UTILS_H

/**
 * @fn     split(const char *str, char delemiter)
 * @author Romain Failla
 * @brief  S�pare une cha�ne de caract�res selon un d�limiteur
 * @param  const char *str : la cha�ne � s�parer
 * @param  char delemiter : le caract�re de s�paration
 * @param  size_t *size : la taille du tableau de r�sultat
 * @return char**
 */
char **split(const char *str, char delemiter, size_t *size);

#endif
