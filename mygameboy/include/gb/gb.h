#ifndef GB_H
#define GB_H

int  gb_init();
int  gb_load(const char* file_path);
void gb_step(int ms_tick_delta);
void gb_close();

#endif