/*
** EPITECH PROJECT, 2020
** CPE_corewar_2019
** File description:
** core_warrior
*/

#include "corewar.h"

static int argument(core_t *core, warrior_t *warrior, char **argv, int *e)
{
    if (my_cmp(argv[*e], "-dump", 0) && my_isin(argv[*e + 1], '0', '9', 0)) {
        core->nb_cycle = my_atoi(argv[++*e]);
        ++*e;
        return (1);
    }
    if (my_cmp(argv[*e], "-n", 0) && my_isin(argv[*e + 1], '0', '9', 0)) {
        warrior->warrior_n = my_atoi(argv[++*e]);
        ++*e;
        return (1);
    }
    if (my_cmp(argv[*e], "-a", 0) && my_isin(argv[*e + 1], '0', '9', 0)) {
        warrior->ld_adress = my_atoi(argv[++*e]);
        ++*e;
        return (1);
    }
    return (0);
}

static int flags(core_t *core, int argc, char **argv, int *e)
{
    for (int i = 0; i < 3; i++)
        if (*e + 1 < argc && argument(core, &core->warrior[core->nb_w], argv, e)
        && *e >= argc)
            return (error("INIT: arg aren't relate to any warrior\n"));
    return (0);
}

static void n_not_taken(core_t *core, int *n)
{
    for (int e = 0; e < core->nb_w; ++e)
        if (core->warrior[e].warrior_n == *n) {
            ++*n;
            n_not_taken(core, n);
        }
}

int init_warrior(core_t *core, int argc, char **argv, int *e)
{
    if (core->nb_w > 3) return (error("INIT: Too much arg\n"));
    core->warrior[core->nb_w].warrior_n = core->nb_w + 1;
    core->warrior[core->nb_w].n = core->nb_w + 1;
    core->warrior[core->nb_w].alive = 1;
    core->warrior[core->nb_w].process = NULL;
    if (flags(core, argc, argv, e)) return (1);
    n_not_taken(core, &core->warrior[core->nb_w].warrior_n);
    if (init_menory(core, &core->warrior[core->nb_w], argv, e))
        return (1);
    ++core->nb_w;
    return (0);
}

void destroy_warrior(warrior_t *warrior)
{
    free(warrior->program);
    destroy_process(warrior->process);
}