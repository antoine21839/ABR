#include "ABR.h"

void detruire_ABR(ABR *a){
    assert(NULL != a);

    if(NULL == *a)
        return;
    detruire_ABR(&(*a)->fg);
    detruire_ABR(&(*a)->fd);
    free(*a);
    *a = NULL;
}

Noeud * allouer_noeud(const void *val, void *(*allouer_elem)(const void *)){
    Noeud *tmp;

    assert(NULL != val);
    assert(NULL != allouer_elem);

    tmp = (Noeud *)malloc(sizeof(Noeud));
    if(NULL == tmp){
        fprintf(stderr, "Erreur lors de l'allocation de la mémoire !\n");
        return NULL;
    }
    tmp->val = allouer_elem(val);
    if(NULL == tmp->val){
        fprintf(stderr, "Erreur lors de l'allocation de la mémoire !\n");
        free(tmp);
        return NULL;
    }
    tmp->fg = NULL;
    tmp->fd = NULL;
    return tmp;
}

int ajouter_dans_ABR(ABR *a, const void *val, int (*compar)(const void *, const void *), void (*action_si_egal)(Noeud *), void *(*allouer_elem)(const void *)){
    int res_compar;

    assert(NULL != a);
    assert(NULL != val);
    assert(NULL != compar);
    assert(NULL != action_si_egal);

    if(NULL == *a){
        *a = allouer_noeud(val, allouer_elem);
        if(NULL == *a){
            fprintf(stderr, "Erreur lors de l'ajout d'un élément dans l'ABR !\n");
            detruire_ABR(a);
            return 0;
        }
        return 1;
    }
    res_compar = compar((*a)->val, val);
    if(res_compar < 0) /* Si la valeur du noeud sur lequel on est inférieure à la valeur à ajouter */
        return ajouter_dans_ABR(&(*a)->fd, val, compar, action_si_egal, allouer_elem);
    if(res_compar > 0) /* Si la valeur du noeud sur lequel on est supérieure à la valeur à ajouter */
        return ajouter_dans_ABR(&(*a)->fg, val, compar, action_si_egal, allouer_elem);
    action_si_egal(*a); /* Si la valeur du noeud sur lequel on est égale à la valeur à ajouter */
    return 1;
}

static void parcours_infixe_ABR_aux(const ABR a, void (*appliquer)(const void *, int nb_arguments, va_list liste_arguments), int nb_arguments, va_list liste_arguments){
    assert(NULL != appliquer);

    if(NULL == a)
        return;
    parcours_infixe_ABR_aux(a->fg, appliquer, nb_arguments, liste_arguments);
    appliquer(a->val, nb_arguments, liste_arguments);
    parcours_infixe_ABR_aux(a->fd, appliquer, nb_arguments, liste_arguments);
}

void parcours_infixe_ABR(const ABR a, void (*appliquer)(const void *, int nb_arguments, va_list liste_arguments), int nb_arguments, ...){
    va_list liste_arguments;

    assert(NULL != appliquer);

    va_start(liste_arguments, nb_arguments);
    parcours_infixe_ABR_aux(a, appliquer, nb_arguments, liste_arguments);
    va_end(liste_arguments);
}
