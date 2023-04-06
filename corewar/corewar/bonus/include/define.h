/*
** EPITECH PROJECT, 2020
** CPE_corewar_bonus_2019
** File description:
** define
*/

#ifndef DEFINE_H_
#define DEFINE_H_

#include "op.h"
#include "struct.h"

typedef unsigned char int_4b[4];
typedef unsigned char short_2b[2];

extern ref_t ref[];
extern sfColor warrior_color[];

#define BIT(x) x = ((x >> 24)&0xff) | ((x << 8)&0xff0000) | ((x >> 8)&0xff00) \
    | ((x << 24)&0xff000000)

#define INC_PC(pc) pc = (pc + 1) % (MEM_SIZE)
#define NEG_PC(pc) (pc < 0) ? (MEM_SIZE) + pc : pc
#define GO_PC(pc, add) pc = NEG_PC(pc + (add % IDX_MOD)) % (MEM_SIZE)
#define GO_LPC(pc, add) pc = (pc + add) % (MEM_SIZE)

#define WRONG_IT(it) (it > 0 && it < 17) ? 0 : 1
#define WRONG_REG(reg) (reg >= 0 && reg < 16) ? 0 : 1
#define CARRY(r) (!(r)) ? 1 : 0

#define HEIGHT 1080
#define WIDTH 1920

#define HEX "0123456789abcdef"
#define HEX_LEN 16

#define ORANGE (sfColor){250, 140, 0, 255}

#endif /* !DEFINE_H_ */