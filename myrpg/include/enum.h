/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** enum
*/

#ifndef ENUM_H_
#define ENUM_H_

/**********\
*   MENU   *
\**********/

enum scenes{
    MAIN_MENU,
    SETTINGS,
    PREGAME,
    GAME,
    PAUSE_MENU,
    END_GAME
};

enum ui_order{
    BACK
};

enum ui_animation{
    OPEN,
    CLOSE
};

/***************\
*   MAIN MENU   *
\***************/

enum mm_buttons{
    MM_PLAY,
    MM_SETTINGS,
    MM_QUIT
};

enum mm_buttons_hov{
    MM_PLAY_HOV,
    MM_SETTINGS_HOV,
    MM_QUIT_HOV
};

/*************\
*   PREGAME   *
\*************/

enum pregame_ui{
    PREGAME_UI = 1
};

enum pregame_hov_buttons{
    BLBOY_HOV = 4,
    BRBOY_HOV,
    BLGIRL_HOV,
    BRGIRL_HOV
};

/*******************\
*   SETTINGS MENU   *
\*******************/

enum settings_ui{
    SM_MENU = 1,
    SM_NOTCH,
    SM_SELECTOR
};

enum settings_button{
    SM_QUIT,
    SM_CONFIRM,
};

enum settings_button_hov{
    SM_QUIT_HOV,
    SM_CONFIRM_HOV
};

/****************\
*   PAUSE MENU   *
\****************/

enum pm_ui{
    PM_SURE_UI = 1,
    PM_BLACK_BG
};

enum pm_hov_buttons{
    PM_PLAY,
    PM_MM,
    PM_QUIT,
    PM_YES,
    PM_NO,
    PM_PLAY_HOV,
    PM_MM_HOV,
    PM_QUIT_HOV,
    PM_YES_HOV,
    PM_NO_HOV
};

/**********\
*   GAME   *
\**********/

enum pnj{
    PNJ_F,
    PNJ_S,
    ENNEMY
};

enum day_time{
    DAY,
    NIGHT,
    MORNING,
    BEFORE_DAY,
    REAL_NIGHT,
    REAL_MORNING
};

enum arena_pnj{
    ELF,
    WOMAN
};

enum inventory{
    INV_UI,
    INV_CLOSE_HOV,
    BIG_SHIELD,
    LITTLE_SHIELD,
    BIG_SWORD,
    LITTLE_SWORD,
    SHIELD_SHADOW,
    SWORD_SHADOW
};

enum inventory_text{
    LEVEL_NUM_TEXT,
    POWER_WORD_TEXT,
    POWER_NUM_TEXT
};

enum inv_rectangle{
    INV_RECT_CLOSE,
    INV_RECT_BSH,
    INV_RECT_BSW,
    INV_RECT_LSH,
    INV_RECT_LSW
};

enum common_to_scenes{
    TEXT_BOX
};

enum ui_in_game{
    MAP
};

enum scenes_in_game {
    OUTSIDE_MAP,
    TAVERN_MAP,
    SELLER_MAP,
    CAVE_MAP,
    DUNGEON_MAP,
    ARENA_MAP,
    END_GAME_SCENE
};

enum movements {
    NOTHING,
    LEFT,
    UP,
    RIGHT,
    DOWN,
};

enum character_sprite {
    BLOND_BOY,
    BROWN_BOY,
    BLOND_GIRL,
    BROWN_GIRL
};

/************\
*   HITBOX   *
\************/

enum hitbox_color {
    LOW_BLUE,
    OUTSIDE,
    TAVERN,
    SELLER,
    CAVE,
    DUNGEON,
    ARENA1,
    ARENA2,
    PNJ,
    GATE
};

/**********\
*   RAIN   *
\**********/

enum drop_value {
    XTHIRD,
    X_TWO_THIRD,
    XSIXTH,
    X_FIVE_SIXTH
};

/***************\
*  FRAMEBUFFER  *
\***************/

enum frambuffer {
    CUT,
    RAIN,
    DARK
};

#endif /* !ENUM_H_ */