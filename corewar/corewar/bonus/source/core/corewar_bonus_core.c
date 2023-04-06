/*
** EPITECH PROJECT, 2020
** CPE_corewar_bonus_2019
** File description:
** corewar_bonus_core
*/

#include "corewar_bonus.h"

static int file_type_control(char *filename, int fd)
{
    int magic = 0;

    if (!(my_str_isin(filename, ".cor", 0))) {
        close(fd);
        return (error("INIT: not a .cor file\n"));
    }
    if (read(fd, &magic, sizeof(magic)) == -1) {
        close(fd);
        return (error("INIT: empty file\n"));
    }
    BIT(magic);
    if (magic != corewar_bonus_EXEC_MAGIC) {
        close(fd);
        return (error("INIT: magic isn't right\n"));
    }
    close(fd);
    return (0);
}

static int nb_warrior(core_t *core, int argc, char **argv)
{
    u_int8_t nb_w = 0;
    int fd;

    for (int e = 1; e < argc; ++e) {
        if (argv[e][0] == '-')
            continue;
        fd = open(argv[e], O_RDONLY);
        if (fd > 0 && !(file_type_control(argv[e], fd)))
            ++nb_w;
    }
    return (nb_w);
}

static int load_adress(core_t *core, int argc, char **argv)
{
    u_int8_t nb_w = nb_warrior(core, argc, argv);
    u_int16_t gap;

    if (nb_w > 4) return (error("INIT: Too many warrior\n"));
    else if (nb_w < 2) return (error("INIT: Too few warrior\n"));
    gap = MEM_SIZE / nb_w;
    for (int e = 0; e < nb_w; ++e)
        core->warrior[e].ld_adress = e * gap;
    return (0);
}

int init_core(core_t *core, int argc, char **argv)
{
    core->run = 1;
    core->nb_w = 0;
    core->nb_cycle = 0;
    if (load_adress(core, argc, argv)) return (1);
    for (int e = 0; e < MEM_SIZE; ++e) {
        core->men[e] = 0;
        core->belong[e] = 0;
    }
    for (int e = 1; e < argc; ++e)
        if (init_warrior(core, argc, argv, &e))
            return (1);
    if (init_cycle(core, &core->cycle)) return (1);
    return (0);
}

void destroy_core(core_t *core)
{
    for (int e = 0; e < core->nb_w; ++e)
        destroy_warrior(&core->warrior[e]);
}