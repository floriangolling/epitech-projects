/*
** EPITECH PROJECT, 2020
** CPE_corewar_bonus_2019
** File description:
** enum
*/

#ifndef ENUM_H_
#define ENUM_H_

enum state {
    FETCH,
    WAIT,
    EXECUTE
};

enum parameter_type {
    NO_PARAM,
    REGISTER,
    DIRECT,
    INDIRECT
};

enum mnenonic {
    LIVE = 1,
    LD = 2,
    ST = 3,
    ADD = 4,
    SUB = 5,
    AND = 6,
    OR = 7,
    XOR = 8,
    ZJMP = 9,
    LDI = 10,
    STI = 11,
    FORK = 12,
    LLD = 13,
    LLDI = 14,
    LFORK = 15,
    AFF = 16
};

#endif /* !ENUM_H_ */