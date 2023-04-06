/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** struct
*/

#ifndef STRUCT_H_
#define STRUCT_H_

#include <SFML/Graphics.h>

/************\
*   WINDOW   *
\************/

typedef struct s_window
{
    sfVector2f scale;
    sfEvent event;
    sfRenderWindow *window;
    sfVideoMode video_mode;
    sfTexture *texture;
    sfSprite *sprite;
    int pos;
} window_t;


/*************\
*   ELEMENT   *
\*************/

typedef struct elem_s
{
    sfTexture *texture;
    sfSprite *sprite;
    sfVector2f set_position;
    sfVector2f get_position;
    sfIntRect rect;
    bool is_display;
    bool gen_action;
    int state;
} elem_t;

/************\
*     UI     *
\************/

typedef struct button_s
{
    sfTexture *texture;
    sfSprite *sprite;
    sfVector2f position;
    bool is_hover;
} button_t;

typedef struct string_s
{
    sfText *string;
    sfFont *font;
    sfColor color;
    sfVector2f place_string;
} string_t;


typedef struct rectangle_s
{
    sfRectangleShape *rect;
    sfVector2f rect_size;
    sfVector2f rect_position;
    sfColor color;
    bool is_hover;
} rectangle_t;

typedef struct menu_s
{
    elem_t *ui_scene;
    button_t *buttons;
    string_t *texts;
    rectangle_t *rectangle;
} menu_t;

/***********\
*   SCENE   *
\***********/

typedef struct scene_s
{
    elem_t *ui_scene;
    string_t texts;
    elem_t *pnj;
    char *dialog;
    int pos_in_dial;
    int dialog_state;
    bool dial_activated;
    elem_t ennemy;
    sfSoundBuffer **sbuffer;
    sfSound **sounds;
}scene_t;

/************\
*  SETTINGS  *
\************/

typedef struct settings_s
{
    bool is_music_on;
    int music_volume;
} settings_t;

/************\
*   PLAYER   *
\************/

typedef struct inventory_s
{
    bool inventory_is_open;
    bool has_drop_shield;
    bool has_drop_sword;
    bool is_equip_shield;
    bool is_equip_sword;
} inventory_t;

typedef struct player_s
{
    int level;
    elem_t character;
    elem_t pl_not_op;
    inventory_t inventory;
    int is_walking;
    int type;
    int is_on_scene;
    bool is_in_fight;
    bool has_shield;
    int power;
}player_t;

/************\
*   HITBOX   *
\************/

typedef struct box_s
{
    sfImage *m;
    sfVector2f pos;
    sfVector2u dim;
    unsigned char **box;
}box_t;

typedef struct hitbox_s
{
    box_t map;
    box_t player;
    bool transparent;
    bool pnj;
    int ic_c;
    sfColor *color;
}hitbox_t;

/************\
*   SHAPES   *
\************/

typedef struct square_s
{
    sfVector2i pos;
    sfVector2i dim;
    sfColor color;
}square_t;

typedef struct v_halo_s
{
    int x_circle;
    int y_circle;
    int reverse;
    int save;
    float i;
    float c1;
    float c2;
    sfColor c;
    sfColor safe;
}v_halo_t;

/**********\
*   RAIN   *
\**********/

typedef struct drop_s
{
    sfVector2i pos;
    sfVector2i dim;
    u_int16_t start;
    bool animation;
    sfColor color;
    short impact;
    float speed;
}drop_t;

typedef struct rain_s
{
    u_int16_t begining;
    u_int16_t ic_loop;
    u_int16_t nb_drop;
    drop_t *drop;
    short mvt;
    char add;
}rain_t;

/**********\
*   DARK   *
\**********/

typedef struct halo_s
{
    bool light_on;
    sfColor extremity;
    sfColor center;
    sfVector2i pos;
    short alpha;
    float radius;
}halo_t;

typedef struct dark_s
{
    u_int8_t gradually;
    sfColor detected;
    u_int8_t nb_halo;
    halo_t *halo;
}dark_t;

/*********\
*   CUT   *
\*********/

typedef struct shift_s
{
    u_int8_t active;
    sfVector2f pos;
    sfVector2f dim;
    sfColor color;
}shift_t;

typedef struct cut_s
{
    bool transition;
    u_int8_t ic_scene;
    u_int8_t wait;
    sfMutex *l_wait;
    u_int8_t idx;
    sfMutex *l_idx;
    shift_t shift;
    bool is_transition;
    bool past_transition;
}cut_t;

/************\
*   BUFFER   *
\************/

typedef struct bf_s
{
    sfVector2u size;
    sfSprite *sprite;
    sfMutex *l_sprite;
    sfTexture *texture;
    sfUint8 *pixels;
}bf_t;

/**********\
*  THREAD  *
\**********/

typedef struct thread_s
{
    sfThread *thread;
    sfMutex *l_run;
    sfMutex *l_activate;
    sfTime sleep;
    bool run;
}thread_t;

/***************\
*  FRAMEBUFFER  *
\***************/

typedef struct fbf_s
{
    u_int8_t nb_active;
    u_int8_t *active;
    thread_t _s;
    sfVector2i w;
    sfVector2f m;
    sfVector2f p;
    bool move;
    cut_t cut;
    bf_t buffer;
    rain_t rain;
    dark_t dark;
}fbf_t;

/************\
*   BATTLE   *
\************/

typedef struct arrow_s
{
    bool send;
    sfSprite *sprite;
    sfTexture *texture;
    sfVector2f pos;
    sfVector2f tip;
    sfVector2f offset;
    float speed;
}arrow_t;

typedef struct enemy_s
{
    bool alive;
    bool animate;
    sfSprite *sprite;
    sfTexture *texture;
    sfIntRect rect;
    sfVector2f pos;
    sfVector2i move;
    arrow_t arrow;
    u_int16_t saveleft;
}enemy_t;

typedef struct life_s
{
    u_int8_t nb_life;
    sfColor color;
    sfVector2f size;
    sfRectangleShape *health;
    sfRectangleShape *back;
}life_t;

typedef struct battle_s
{
    bool end;
    u_int8_t battle;
    u_int8_t nb_arrow;
    arrow_t *arrows;
    u_int8_t nb_enemy;
    enemy_t *enemy;
    sfFloatRect hit_enemy;
    sfFloatRect hit_player;
    life_t life;
}battle_t;

/************\
*    GAME    *
\************/

typedef struct common_s
{
    elem_t *common_ui;
    button_t close_inv_butt;
    rectangle_t *inv_rectangle;
    elem_t *inventory_ui;
    string_t *inventory_text;
} common_t;

typedef struct transparent_s
{
    sfSprite *sprite;
    sfTexture *texture;
    sfColor color;
    sfVector2f pos;
    int state;
} transparent_t;

/************\
*    INTRO   *
\************/

typedef struct intro_s
{
    sfSprite *tilesheet;
    sfTexture **texture;
    sfTime time;
    double seconds;
    sfIntRect rect;
    sfVector2i inc;
} intro_t;

typedef struct loading_s
{
    string_t text;
    char **loading_tab;
    sfClock *clock_load;
    int load_time;
}loading_t;

typedef struct game_s
{
    window_t *window;
    fbf_t fbf;
    intro_t intro;
    loading_t loading;
    menu_t *menu;
    scene_t *game_scenes;
    common_t common;
    player_t player;
    settings_t settings;
    sfClock *clock;
    sfTime time;
    sfMusic *music;
    sfVector2i mouse_position;
    bool game_is_up;
    int *game_state;
    hitbox_t hit;
    battle_t battle;
    transparent_t *trans;
}game_t;

#endif /* !STRUCT_H_ */