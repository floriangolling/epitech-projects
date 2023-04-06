/*
** EPITECH PROJECT, 2020
** defender project
** File description:
** create element
*/

#include "rpg.h"

elem_t create_element(elem_t element, char *element_name,
    float pos_x, float pos_y)
{
    element.texture = sfTexture_createFromFile(element_name, NULL);
    element.sprite = sfSprite_create();
    sfSprite_setTexture(element.sprite, element.texture, sfTrue);
    element.set_position.x = pos_x;
    element.set_position.y = pos_y;
    sfSprite_setPosition(element.sprite, element.set_position);
    element.is_display = false;
    element.gen_action = false;
    element.state = 0;
    return (element);
}