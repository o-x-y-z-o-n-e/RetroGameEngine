#ifndef GAME_H
#define GAME_H

#define SHIP_COMP 107
#define WINDOW_WIDTH 512
#define WINDOW_HEIGHT 288

void game_update(float delta);

void game_load_title();
void game_load_level(int i);

#endif