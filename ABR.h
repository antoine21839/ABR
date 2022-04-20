#ifndef __ABR__
#define __ABR__

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdarg.h>

typedef struct _noeud{
    void *val;
    struct _noeud *fg;
    struct _noeud *fd;
}Noeud, *ABR;

void detruire_ABR(ABR *a);
Noeud * allouer_noeud(const void *val, void *(*allouer_elem)(const void *));
int ajouter_dans_ABR(ABR *a, const void *val, int (*compar)(const void *, const void *), void (*action_si_egal)(Noeud *), void *(*allouer_elem)(const void *));
void parcours_infixe_ABR(const ABR a, void (*appliquer)(const void *, int nb_arguments, va_list liste_arguments), int nb_arguments, ...);

#endif
