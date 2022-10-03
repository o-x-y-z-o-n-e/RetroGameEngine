#include "rge.h"
#include "gb/gb.h"
#include "gb/core.h"

#include <stdio.h>
#include <stdbool.h>

#define BIT_VALUE(A, b) ((A) & (0x01 << (b)))

#define TIMER_PERIOD_1 0.003814697265625F
#define TIMER_PERIOD_2 0.0152587890625F
#define TIMER_PERIOD_3 0.06103515625F
#define TIMER_PERIOD_0 0.244140625F

extern uint8_t DEBUG_MODE;

struct registers_t registers;

static float timer_ticks;
static float divider_ticks;
static float allocated_cycles;
static bool enable_interrupts;


//---------------------------------------------------------------------------------------------------


static void print_cpu_state() {
	rge_log_info("==Registers==");
	rge_log_info("A: %d", registers.A);
	rge_log_info("F: %d", registers.F);
	rge_log_info("B: %d", registers.B);
	rge_log_info("C: %d", registers.C);
	rge_log_info("D: %d", registers.D);
	rge_log_info("E: %d", registers.E);
	rge_log_info("H: %d", registers.H);
	rge_log_info("L: %d", registers.L);
	rge_log_info("AF: %d", registers.AF);
	rge_log_info("BC: %d", registers.BC);
	rge_log_info("DE: %d", registers.DE);
	rge_log_info("HL: %d", registers.HL);
	rge_log_info("PC: 0x%x", registers.PC);
	rge_log_info("SP: 0x%x", registers.SP);
	
	rge_log_info("==Flags==");
	rge_log_info("ZERO: %u", gb_cpu_flag_get(FLAGS_ZERO) ? 1 : 0);
	rge_log_info("SUBTRACT: %u", gb_cpu_flag_get(FLAGS_SUBTRACT) ? 1 : 0);
	rge_log_info("HALF_CARRY: %u", gb_cpu_flag_get(FLAGS_HALF_CARRY) ? 1 : 0);
	rge_log_info("CARRY: %u", gb_cpu_flag_get(FLAGS_CARRY) ? 1 : 0);
}


//---------------------------------------------------------------------------------------------------


static void handle_interrupts() {
	if (registers.IME) {
		//get active flags
		uint8_t flags = *registers.IF & registers.IE;

		//only called an interrupt handler if at least 1 flag is active
		if (flags) {
			gb_cpu_delay(2);
			gb_mmu_push(registers.PC);

			//set interrupt handler to address
			if (flags & INTERRUPT_V_BLANK) {
				registers.PC = 0x0040;
				*registers.IF &= ~INTERRUPT_V_BLANK;
			}
			else if (flags & INTERRUPT_LCD) {
				registers.PC = 0x0048;
				*registers.IF &= ~INTERRUPT_LCD;
			}
			else if (flags & INTERRUPT_TIMER) {
				registers.PC = 0x0050;
				*registers.IF &= ~INTERRUPT_TIMER;
			}
			else if (flags & INTERRUPT_SERIAL) {
				registers.PC = 0x0058;
				*registers.IF &= ~INTERRUPT_SERIAL;
			}
			else if (flags & INTERRUPT_JOYPAD) {
				registers.PC = 0x0060;
				*registers.IF &= ~INTERRUPT_JOYPAD;
			}
		}

		//turn off all interrupts until the current interrupt handler ends by calling RETI (which re-enables interrupts)
		registers.IME = 0;
		enable_interrupts = false;
	}

	//delay enabling master interrupts
	if (enable_interrupts) {
		//this is here because the opcode 'EI' (enable interrupts), is delayed by 1 m-cycle. eg, if EI and then DI is called, then nothing happens.
		registers.IME = 1;
		enable_interrupts = false;
	}
}


//---------------------------------------------------------------------------------------------------


static void handle_timers(int ms_tick_delta) {
	//Divider
	{
		if (divider_ticks > 0.06103515625F) {
			divider_ticks -= 0.06103515625;

			(*gb_mmu_location(0xFF04))++;
		}
	}

	//Timer
	{
		uint8_t control = gb_mmu_read(0xFF07);

		if(!BIT_VALUE(control, 2))
			return;

		uint8_t counter = gb_mmu_read(0xFF05);

		int speed = control & 0x03;
		float period = 0;

		if(speed == 0)      period = TIMER_PERIOD_0;
		else if(speed == 1) period = TIMER_PERIOD_1;
		else if(speed == 2) period = TIMER_PERIOD_2;
		else if(speed == 3) period = TIMER_PERIOD_3;

		timer_ticks += ms_tick_delta;

		if(timer_ticks > period) {
			timer_ticks -= period;

			if(counter + 1 > 0xFF) {
				counter = gb_mmu_read(0xFF06);
				gb_cpu_int_flag_set(INTERRUPT_TIMER, 1);
			} else {
				counter++;
			}
		}
	}
}


//---------------------------------------------------------------------------------------------------


static void step(int ms_tick_delta) {
	handle_interrupts();
	handle_timers(ms_tick_delta);

	/*
	GB runs instructions at 1048576hz (~1MHz)->(~1µs)->(~0.001ms). aka. ~953.67431640625 instructions will run per millisecond.
	*/

	allocated_cycles += (float)ms_tick_delta * 953.67431640625F;

	if(allocated_cycles <= 0)
		return;

	//fetch
	uint8_t opcode = gb_mmu_fetch();

	//decode
	op_func func = gb_cpu_decode(opcode);

	//execute
	func();

	//keep count of opcode timings to simulate the clock speed of the LR35902
	allocated_cycles -= (float)gb_cpu_delay_get(opcode);
}


//---------------------------------------------------------------------------------------------------


void gb_cpu_delay(int cycles) {
	allocated_cycles -= cycles;
}


//---------------------------------------------------------------------------------------------------


//Set the value of a specified register flag. Note: 'int flag' is a bitmask, not an index of the bit.
void gb_cpu_flag_set(int flag, bool state) {
	if(state) registers.F |= flag;
	else registers.F &= ~flag;
}


//---------------------------------------------------------------------------------------------------


bool gb_cpu_flag_get(int flag) {
	return registers.F & flag;
}


//---------------------------------------------------------------------------------------------------


//Set the value of a specified interrupt flag. Note: 'int interrupt' is a bitmask, not an index of the bit.
void gb_cpu_int_flag_set(int interrupt, bool state) {
	if(state) *registers.IF |= interrupt;
	else *registers.IF &= ~interrupt;
}


//---------------------------------------------------------------------------------------------------


bool gb_cpu_int_flag_get(int interrupt) {
	return *registers.IF & interrupt;
}


//---------------------------------------------------------------------------------------------------


//Set the Interrupt Master Enable flag.
void gb_cpu_ime_set(bool enabled) {
	if(enabled) {
		enable_interrupts = true;
	} else {
		registers.IME = enabled;
	}
}


//---------------------------------------------------------------------------------------------------


int gb_init() {
	registers.IF = gb_mmu_location(0xFF0F);
	registers.PC = 0x0000;
	registers.SP = 0xFFFE;
	registers.IME = 1;

	gb_mmu_init();
	gb_ppu_init();

	return 0;
}


//---------------------------------------------------------------------------------------------------


void gb_close() {
	gb_ppu_close();
	gb_mmu_close();
}


//---------------------------------------------------------------------------------------------------


void gb_step(int ms_tick_delta) {
	step(ms_tick_delta);
	gb_ppu_step(ms_tick_delta);
}