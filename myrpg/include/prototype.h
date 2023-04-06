/*
** EPITECH PROJECT, 2020
** MUL_my_rpg_2019
** File description:
** prototype
*/

#ifndef PROTOTYPE_H_
#define PROTOTYPE_H_

#include "struct.h"

/*************\
*   GENERAL   *
\*************/

double CONVERSION;
double PI;
int (*select_game_state[6])(game_t *game);
window_t *create_window(window_t *window, char *title);
elem_t create_element(elem_t element, char *element_name,
float pos_x, float pos_y);
button_t create_button(button_t button, char *button_name,
float pos_x, float pos_y);
void usage(void);
int main_menu(game_t *game);
int settings_menu(game_t *game);
int in_game(game_t *game);
int pause_menu(game_t *game);
int end_game(game_t *game);
int change_state_cause_of_error(game_t *game);
int create_music(game_t *game);

/***************\
*   MAIN MENU   *
\***************/

int init_main_menu(game_t *game);
int init_ui_main_menu(game_t *game);
int init_button_main_menu(game_t *game);
void draw_main_menu(game_t *game);
int events_main_menu(game_t *game);
void destroy_main_menu_elements(game_t *game);

/***************\
* SETTINGS MENU *
\***************/

int init_settings_menu(game_t *game);
int init_ui_settings_menu(game_t *game);
int init_button_settings_menu(game_t *game);
int draw_settings_menu(game_t *game);
int events_settings_menu(game_t *game);
int is_on_quit_button_settings(game_t *game);
int is_on_confirm_button_settings(game_t *game);
int is_on_off_music(game_t *game);
void destroy_settings_menu(game_t *game);

/*************\
*   PREGAME   *
\*************/

int pregame(game_t *game);
int init_ui_pregame(game_t *game);
int init_button_pregame(game_t *game);
int events_pregame(game_t *game);
void draw_pregame(game_t *game);
void destroy_pregame(game_t *game);

/************\
*   LOADING  *
\************/

void loading(game_t *game);
int init_text_loading(game_t *game);
void destroy_loading(game_t *game);
void draw_loading(game_t *game);
int set_loading_text(game_t *game);

/****************\
*   PAUSE MENU   *
\****************/

bool intro(game_t *game);
bool init_intro(intro_t *intro);
void init_sprite(intro_t *intro);

/****************\
*   PAUSE MENU   *
\****************/

int pause_menu(game_t *game);
int init_ui_pause_menu(game_t *game);
int init_button_pause_menu(game_t *game);
int events_pause_menu(game_t *game);
void draw_pause_menu(game_t *game);
void destroy_pause_menu(game_t *game);

/**********\
*   GAME   *
\**********/

void *init_in_game(game_t *game);
int init_in_game_scene(game_t *game);
int create_character(game_t *game);
int create_utils_in_game(game_t *game);
int in_game(game_t *game);
void draw_in_game(game_t *game);
void destroy_in_game(game_t *game);
void select_skin(game_t *game);
void select_transparent_skin(game_t *game);
void init_character_pos(game_t *game);
int init_in_game_text(game_t *game);
int battle_scene(game_t *game);

/****************\
*   DRAW SCENE   *
\****************/

void (*select_draw_in_game[6])(game_t *game);
void draw_outside(game_t *game);
void draw_tavern(game_t *game);
void draw_seller(game_t *game);
void draw_cave(game_t *game);
void draw_dungeon(game_t *game);
void draw_arena(game_t *game);
void draw_inventory(game_t *game);
void draw_shield_chara(game_t *game);

/**********\
*   INIT   *
\**********/

int init_day_night(game_t *game);
int init_common_to_scenes(game_t *game);
int init_ui_outside(game_t *game);
int init_ui_tavern(game_t *game);
int init_ui_seller(game_t *game);
int init_ui_cave(game_t *game);
int init_ui_dungeon(game_t *game);
int init_ui_arena(game_t *game);
int init_outside_pnj(game_t *game);
int init_tavern_pnj(game_t *game);
int init_seller_pnj(game_t *game);
int init_cave_pnj(game_t *game);
int init_dungeon_pnj(game_t *game);
int init_arena_pnj(game_t *game);
int init_inventory(game_t *game);
int init_inventory_text(game_t *game);
int rectangle_set_position(sfRectangleShape *rect, int x, int y);

/***********\
*   EVENT   *
\***********/

int (*select_events_in_game[6])(game_t *game);
int events_in_game(game_t *game);
int event_keyboard(game_t *game);
int inventory_events(game_t *game);
int pnj_event(game_t *game);
int outside_events(game_t *game);
int tavern_events(game_t *game);
int seller_events(game_t *game);
int cave_events(game_t *game);
int dungeon_events(game_t *game);
int arena_events(game_t *game);
int equipment(game_t *game);
void day_clock(game_t *game);
void night_clock(game_t *game);
void night(game_t *game);
void real_morning(game_t *game);
int choose_pnj_dialog(game_t *game);
void set_power(game_t *game);

/******************\
*   BATTLE SCENE   *
\******************/

void draw_battle_scene(game_t *game);
int events_battle_scene(game_t *game);
void destroy_battle_scene(game_t *game);


/**************\
*   MOVEMENT   *
\**************/

void move_character(game_t *game, float x, float y);
void move_left(game_t *ga, double time);
void move_right(game_t *ga, double time);
void move_up(game_t *ga, double time);
void move_down(game_t *ga, double time);
void move_rect_player(game_t *ga);
void is_player_walking(game_t *game);
void move_up_cave(game_t *ga, float time);
void move_down_cave(game_t *ga, float time);
void move_up_dungeon(game_t *ga, float time);
void move_down_dungeon(game_t *ga, float time);
void change_rect_up(game_t *game);
void move_pnj(game_t *game, sfVector2f move);
int shield_animation(game_t *game, int move);
void shield_movement(game_t *game, int ic);
void shield_activation(game_t *game, int ic);
void movement_activations(game_t *game, double time);

/****************\
*   FRAMBUFFER   *
\****************/

int init_framebuffer(game_t *ga, fbf_t *fbf, int height, int width);
int framebuffer_calculate(game_t *ga);
void framebuffer_display(game_t *ga);
void framebuffer_destroy(fbf_t *fbf);
void framebuffer_update(game_t *ga, fbf_t *fbf, u_int8_t alpha);
int framebuffer_thread(game_t *ga);
int framebuffer_run(game_t *ga);
void framebuffer_end(fbf_t *fbf);

/************\
*   BUFFER   *
\************/

int init_buffer(fbf_t *fbf, int height, int width);
void buffer_display(bf_t *buffer, sfRenderWindow *w);
void destroy_buffer(bf_t *buffer);
void put_pixel(bf_t *buffer, int x, int y, sfColor color);
void put_pixel_light(bf_t *buffer, int x, int y, sfColor color);
void buffer_restore(bf_t *buffer);
void buffer_gloomy_restore(bf_t *buffer, sfUint8 alpha);

/************\
*   SHAPES   *
\************/

void put_square(bf_t *buffer, square_t sqr);
void put_drop(bf_t *buffer, drop_t drop);
void put_halo(bf_t *buffer, halo_t *halo);
void put_halo_map(bf_t *buffer, halo_t *halo, sfVector2f m);

/**********\
*   RAIN   *
\**********/

int init_rain(game_t *ga, fbf_t *fbf, rain_t *rain);
int framebuffer_rain(game_t *ga, fbf_t *fbf);
void destroy_rain(rain_t *rain);
drop_t drop_born(fbf_t *fbf, int x, int y);
void drop_reborn(fbf_t *fbf, drop_t *drop, int x, int y);
void drop_transition(game_t *ga, fbf_t *fbf, drop_t *drop);
void rain_splash(fbf_t *fbf, drop_t *drop);
void rain_restart(fbf_t *fbf, rain_t *rain);

/**********\
*   DARK   *
\**********/

int init_dark(game_t *ga, dark_t *dark);
int framebuffer_dark(game_t *ga, fbf_t *fbf, dark_t *dark);
void destroy_dark(dark_t *dark);
halo_t halo_born(fbf_t *fbf);
void halo_position(halo_t *halo, sfVector2f p);
void dark_detected(game_t *ga, sfUint8 large, int x, int y);
void dark_random(fbf_t *fbf, dark_t *dark);

/*********\
*   CUT   *
\*********/

int init_cut(game_t *ga, cut_t *cut);
void framebuffer_cut(game_t *ga, cut_t *cut);
void destroy_cut(cut_t *cut);
void cut_wait_before(game_t *ga, cut_t *cut, u_int8_t idx);
void cut_wait_after(game_t *ga, cut_t *cut);
void cut_tavern(game_t *ga, cut_t *cut);
void cut_enter(game_t *ga, cut_t *cut);
void cut_out(game_t *ga, cut_t *cut);
void cut_out_second(game_t *ga, cut_t *cut, shift_t *shift);

/**************\
*    HITBOX    *
\**************/

int init_hitbox(game_t *ga);
int init_box(game_t *ga, box_t *obj, sfVector2f pos, char *path);
int init_color(hitbox_t *hit);
void destroy_hitbox(game_t *ga);
void hitbox_read_image(game_t *ga, box_t *obj);
int hitbox_player(game_t *ga, int direction);
int hitbox_effect(game_t *ga, double n_x, double n_y);
int hitbox_select_skin(game_t *ga);
int hitbox_pnj(game_t *ga);

/*************\
*    SCENE    *
\*************/

int scene_outside(game_t *ga);
int scene_tavern(game_t *ga);
int scene_seller(game_t *ga);
int scene_cave(game_t *ga);
int scene_dungeon(game_t *ga);
int scene_arena_one(game_t *ga);
int scene_arena_two(game_t *ga);
void scene_restore(game_t *ga);
void scene_restore_outside(game_t *ga);
void scene_handling(game_t *ga, cut_t *cut);
void exit_scene_tavern(game_t *ga);
void exit_scene_seller(game_t *ga);
void exit_scene_cave(game_t *ga);
void exit_scene_dungeon(game_t *ga);
void exit_scene_arena_elf(game_t *ga);
void exit_scene_arena_woman(game_t *ga);

/************\
*   BATTLE   *
\************/

int init_battle_one(game_t *ga, battle_t *ba);
int init_battle_two(game_t *ga, battle_t *ba);
void battle_display(game_t *ga, battle_t *ba);
void battle_destroy(battle_t *ba);
void battle_shot(game_t *ga, battle_t *ba);
void battle_hitbox(game_t *ga, battle_t *ba);
void battle_end(game_t *ga, battle_t *ba);
void shield_protect(game_t *game);

/**********\
*   LIFE   *
\**********/

int create_life(game_t *ga, life_t *life);
void life_decrease(game_t *ga, life_t *life);
void life_display(game_t *ga, life_t *life);
void life_destroy(life_t *life);

/***********\
*   ARROW   *
\***********/

int create_arrow(arrow_t *arrow, char *path, float speed);
void arrow_display(game_t *ga, arrow_t *arrow);
void arrow_destroy(arrow_t *arrow);
void arrow_send(game_t *ga, arrow_t *arrow);
void arrow_enemy_send(game_t *ga, enemy_t *enemy, arrow_t *arrow);
void arrow_hit(game_t *ga, arrow_t *arrow);

/***********\
*   ENEMY   *
\***********/

int create_enemy_elf(enemy_t *enemy, sfVector2f pos);
int create_enemy_woman(enemy_t *enemy, sfVector2f pos);
void enemy_display(game_t *ga, enemy_t *enemy);
void enemy_destroy(enemy_t *enemy);
void enemy_animate(enemy_t *enemy);
void enemy_dodge(game_t *ga, battle_t *ba, enemy_t *enemy);
void enemy_extremity(game_t *ga, battle_t *ba, enemy_t *enemy);
void enemy_move(game_t *ga, battle_t *ba, enemy_t *enemy);

/************\
*  END GAME  *
\************/

int end_game(game_t *game);
int init_end_game_dialog(game_t *game);
void destroy_end_game(game_t *game);
void draw_end_game(game_t *game);
int events_end_game(game_t *game);
int moove_text(game_t *game);

#endif /* !PROTOTYPE_H_ */