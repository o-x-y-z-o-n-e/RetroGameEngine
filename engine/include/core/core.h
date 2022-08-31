#ifndef CORE_H
#define CORE_H

int init_core();
void start_core();
void close_core();
void set_on_core_update(void (*func)(float delta));
void crash_core(int error);

#endif