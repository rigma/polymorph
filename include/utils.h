#ifndef UTILS_H
#define UTILS_H

/**
 * @fn     split(const char *str, char delemiter)
 * @author Romain Failla
 * @brief  Sépare une chaîne de caractères selon un délimiteur
 * @param  const char *str : la chaîne à séparer
 * @param  char delemiter : le caractère de séparation
 * @param  size_t *size : la taille du tableau de résultat
 * @return char**
 */
char **split(const char *str, char delemiter, size_t *size);

#endif
