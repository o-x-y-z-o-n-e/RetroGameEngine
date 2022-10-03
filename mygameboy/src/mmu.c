#include "rge.h"
#include "gb/core.h"

#include <stdio.h>

const uint8_t BIOS[0x100] = {
	0x31, 0xFE, 0xFF, 0xAF, 0x21, 0xFF, 0x9F, 0x32, 0xCB, 0x7C, 0x20, 0xFB, 0x21, 0x26, 0xFF, 0x0E,
	0x11, 0x3E, 0x80, 0x32, 0xE2, 0x0C, 0x3E, 0xF3, 0xE2, 0x32, 0x3E, 0x77, 0x77, 0x3E, 0xFC, 0xE0,
	0x47, 0x11, 0x04, 0x01, 0x21, 0x10, 0x80, 0x1A, 0xCD, 0x95, 0x00, 0xCD, 0x96, 0x00, 0x13, 0x7B,
	0xFE, 0x34, 0x20, 0xF3, 0x11, 0xD8, 0x00, 0x06, 0x08, 0x1A, 0x13, 0x22, 0x23, 0x05, 0x20, 0xF9,
	0x3E, 0x19, 0xEA, 0x10, 0x99, 0x21, 0x2F, 0x99, 0x0E, 0x0C, 0x3D, 0x28, 0x08, 0x32, 0x0D, 0x20,
	0xF9, 0x2E, 0x0F, 0x18, 0xF3, 0x67, 0x3E, 0x64, 0x57, 0xE0, 0x42, 0x3E, 0x91, 0xE0, 0x40, 0x04,
	0x1E, 0x02, 0x0E, 0x0C, 0xF0, 0x44, 0xFE, 0x90, 0x20, 0xFA, 0x0D, 0x20, 0xF7, 0x1D, 0x20, 0xF2,
	0x0E, 0x13, 0x24, 0x7C, 0x1E, 0x83, 0xFE, 0x62, 0x28, 0x06, 0x1E, 0xC1, 0xFE, 0x64, 0x20, 0x06,
	0x7B, 0xE2, 0x0C, 0x3E, 0x87, 0xE2, 0xF0, 0x42, 0x90, 0xE0, 0x42, 0x15, 0x20, 0xD2, 0x05, 0x20,
	0x4F, 0x16, 0x20, 0x18, 0xCB, 0x4F, 0x06, 0x04, 0xC5, 0xCB, 0x11, 0x17, 0xC1, 0xCB, 0x11, 0x17,
	0x05, 0x20, 0xF5, 0x22, 0x23, 0x22, 0x23, 0xC9, 0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B,
	0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D, 0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E,
	0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99, 0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC,
	0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E, 0x3C, 0x42, 0xB9, 0xA5, 0xB9, 0xA5, 0x42, 0x3C,
	0x21, 0x04, 0x01, 0x11, 0xA8, 0x00, 0x1A, 0x13, 0xBE, 0x20, 0xFE, 0x23, 0x7D, 0xFE, 0x34, 0x20,
	0xF5, 0x06, 0x19, 0x78, 0x86, 0x23, 0x05, 0x20, 0xFB, 0x86, 0x20, 0xFE, 0x3E, 0x01, 0xE0, 0x50
};

extern uint8_t DEBUG_MODE;

static uint8_t ROM[0x4000];  /* 0x0000 (16kB) Cartridge ROM Bank #0 */
static uint8_t SROM[0x4000];  /* 0x4000 (16kB) Cartridge ROM Bank #1 to n */
static uint8_t VRAM[0x2000];  /* 0x8000 (8kB)  Video RAM */
static uint8_t SRAM[0x2000];  /* 0xA000 (8kB)  Cartridge RAM Bank */
static uint8_t RAM[0x2000];  /* 0xC000 (8kB)  Internal RAM */
static uint8_t OAM[0x00A0];  /* 0xFE00 (160B) Object Attribute Memory */
static uint8_t HIO[0x0080];  /* 0xFF00 (128B) Hardware I/O Registers */
static uint8_t HRAM[0x007F];  /* 0xFF80 (127B) Zero Page (High RAM) */

static FILE* rom_file;
static bool use_bios = false;


//---------------------------------------------------------------------------------------------------


static void transfer_DMA(uint16_t source) {
	for(int i = 0; i < 160; i++)
		OAM[i] = gb_mmu_read(source + i);
}


//---------------------------------------------------------------------------------------------------


static int get_cart_size(int header_code) {
	if(header_code < 0x08) {
		return 32768 << header_code;
	}

	if(header_code == 0x52) return 16384 * 72;
	else if(header_code == 0x53) return 16384 * 80;
	else if(header_code == 0x54) return 16384 * 96;

	return -1;
}


//---------------------------------------------------------------------------------------------------


static void set_post_boot_value() {
	if(DEBUG_MODE) {
		rge_log_info("Disabling BIOS");
	}

	use_bios = false;

	registers.AF = 0x01B0;
	registers.BC = 0x0013;
	registers.DE = 0x00D8;
	registers.HL = 0x014D;
	registers.SP = 0xFFFE;

	gb_mmu_write(0xFF05, 0x00); // TIMA
	gb_mmu_write(0xFF06, 0x00); // TMA
	gb_mmu_write(0xFF07, 0x00); // TAC
	gb_mmu_write(0xFF10, 0x80); // NR10
	gb_mmu_write(0xFF11, 0xBF); // NR11
	gb_mmu_write(0xFF12, 0xF3); // NR12
	gb_mmu_write(0xFF14, 0xBF); // NR14
	gb_mmu_write(0xFF16, 0x3F); // NR21
	gb_mmu_write(0xFF17, 0x00); // NR22
	gb_mmu_write(0xFF19, 0xBF); // NR24
	gb_mmu_write(0xFF1A, 0x7F); // NR30
	gb_mmu_write(0xFF1B, 0xFF); // NR31
	gb_mmu_write(0xFF1C, 0x9F); // NR32
	gb_mmu_write(0xFF1E, 0xBF); // NR33
	gb_mmu_write(0xFF20, 0xFF); // NR41
	gb_mmu_write(0xFF21, 0x00); // NR42
	gb_mmu_write(0xFF22, 0x00); // NR43
	gb_mmu_write(0xFF23, 0xBF); // NR30
	gb_mmu_write(0xFF24, 0x77); // NR50
	gb_mmu_write(0xFF25, 0xF3); // NR51
	gb_mmu_write(0xFF26, 0xF1); // NR52 (0xF1 - GB) or (0xF0 - SGB)
	gb_mmu_write(0xFF40, 0x91); // LCDC
	gb_mmu_write(0xFF42, 0x00); // SCY
	gb_mmu_write(0xFF43, 0x00); // SCX
	gb_mmu_write(0xFF45, 0x00); // LYC
	gb_mmu_write(0xFF47, 0xFC); // BGP
	gb_mmu_write(0xFF48, 0xFF); // OBP0
	gb_mmu_write(0xFF49, 0xFF); // OBP1
	gb_mmu_write(0xFF4A, 0x00); // WY
	gb_mmu_write(0xFF4B, 0x00); // WX
	gb_mmu_write(0xFFFF, 0x00); // IE
}


//---------------------------------------------------------------------------------------------------


void gb_mmu_init() {
	gb_mmu_write(0xFF00, 0xFF); //set joypad register to 0xFF. Low is active state for button.
}


//---------------------------------------------------------------------------------------------------


void gb_mmu_close() {
	fclose(rom_file);
}


//---------------------------------------------------------------------------------------------------


int gb_load(const char* file_path) {
	if((rom_file = fopen(file_path, "rb")) == NULL) {
		rge_log_error("Cannot load file: '%s'", file_path);
		return 1;
	}

	gb_mmu_load_bank(0);
	gb_mmu_load_bank(1);

	//check rom header
	{
		uint8_t cart_type = gb_mmu_read(0x0147);
		uint8_t cart_size = gb_mmu_read(0x0148);
		uint8_t eram_size = gb_mmu_read(0x0149);
		uint8_t header_check_sum = gb_mmu_read(0x014D);
		uint16_t global_check_sum = ((uint16_t)gb_mmu_read(0x014E) << 8) | gb_mmu_read(0x014F);

		/*
		==(Cartridge Types)==
		00h  ROM ONLY                 13h  MBC3+RAM+BATTERY
		01h  MBC1                     15h  MBC4
		02h  MBC1+RAM                 16h  MBC4+RAM
		03h  MBC1+RAM+BATTERY         17h  MBC4+RAM+BATTERY
		05h  MBC2                     19h  MBC5
		06h  MBC2+BATTERY             1Ah  MBC5+RAM
		08h  ROM+RAM                  1Bh  MBC5+RAM+BATTERY
		09h  ROM+RAM+BATTERY          1Ch  MBC5+RUMBLE
		0Bh  MMM01                    1Dh  MBC5+RUMBLE+RAM
		0Ch  MMM01+RAM                1Eh  MBC5+RUMBLE+RAM+BATTERY
		0Dh  MMM01+RAM+BATTERY        FCh  POCKET CAMERA
		0Fh  MBC3+TIMER+BATTERY       FDh  BANDAI TAMA5
		10h  MBC3+TIMER+RAM+BATTERY   FEh  HuC3
		11h  MBC3                     FFh  HuC1+RAM+BATTERY
		12h  MBC3+RAM
		*/

		if (cart_type != 0) {
			rge_log_error("Unsupported cartridge type: 0x%x", cart_type);
			return 1;
		}

		if (cart_size != 0) {
			rge_log_error("Unsupported cartridge size: 0x%x", cart_size);
			return 1;
		}

		if (eram_size == 0 && (cart_type == 0x05 || cart_type == 0x06)) {
			rge_log_error("Invalid cartridge. MBC2 does not supprt an external ram size of 0.");
			return 1;
		}

		uint16_t x = 0;
		for (int i = 0x0134; i <= 0x014C; i++) {
			x -= (gb_mmu_read(i) + 1);
		}
		if (header_check_sum != (x & 0xFF)) {
			rge_log_error("Invalid cartridge. Failed header checksum.");
			rge_log_error("Calculated checksum: %d", x);
			rge_log_error("Expected checksum:   %d", header_check_sum);
			return 1;
		}

		x = 0;
		for (int i = 0; i < 0x014E; i++)     x += gb_mmu_read(i);
		for (int i = 0x150; i < get_cart_size(cart_size); i++) x += gb_mmu_read(i);

		if (global_check_sum != x) {
			rge_log_error("Invalid cartridge. Failed global checksum.");
			rge_log_error("Calculated checksum: %d", x);
			rge_log_error("Expected checksum:   %d", global_check_sum);
			return 1;
		}
	}

	use_bios = true;

	return 0;
}


//---------------------------------------------------------------------------------------------------


void gb_mmu_load_bank(int i) {
	fseek(rom_file, i * 0x4000, SEEK_SET);
	fread(i > 0 ? SROM : ROM, 1, 0x4000, rom_file);
}


//---------------------------------------------------------------------------------------------------


uint8_t gb_mmu_fetch() {
	uint8_t u8 = gb_mmu_read(registers.PC);
	registers.PC++;

	return u8;
}


//---------------------------------------------------------------------------------------------------


uint16_t gb_mmu_fetch_u16() {
	//read the next two bytes at PC and assemble them as an unsigned short (little-endian)
	uint16_t u16 = ((uint16_t)gb_mmu_read(registers.PC + 1) << 8) | gb_mmu_read(registers.PC);

	registers.PC += 2;

	return u16;
}


//---------------------------------------------------------------------------------------------------


//Writes a byte to specified system memory address.
void gb_mmu_write(uint16_t address, uint8_t value) {
	uint8_t* mem = gb_mmu_location(address);
	if(mem != NULL)
		*mem = value;

	switch (address) {
		case 0xFF46: {
			//DMA transfer
			transfer_DMA(value << 8);
			return;
		}

		case 0xFF50:
		{
			//Disable BIOS by mapping the first 255 bytes of memory back to ROM#0
			if (value == 1 && use_bios) {
				set_post_boot_value();
			}
			return;
		}
	}
}


//---------------------------------------------------------------------------------------------------


//Reads & returns the byte value from specified system memory address.
uint8_t gb_mmu_read(uint16_t address) {
	return (*gb_mmu_location(address));
}


//---------------------------------------------------------------------------------------------------


//Returns a pointer to the value at the specified system memory address.
uint8_t* gb_mmu_location(uint16_t address) {
	/* 0x0000 (16kB) Cartridge ROM Bank #0 */
	/* 0x4000 (16kB) Cartridge ROM Bank #1 to n */
	/* 0x8000 (8kB)  Video RAM */
	/* 0xA000 (8kB)  Cartridge RAM Bank */
	/* 0xC000 (8kB)  Internal RAM */
	/* 0xFE00 (160B) Object Attribute Memory */
	/* 0xFF00 (128B) Hardware I/O Registers */
	/* 0xFF80 (128B) Zero Page (High RAM) */
	if (address < 0x0100) {
		if (use_bios) {
			return &BIOS[address];
		} else {
			return &ROM[address];
		}
	} else if (address < 0x4000) {
		return &ROM[address];
	} else if (address < 0x8000) {
		return &SROM[address - 0x4000];
	} else if (address < 0xA000) {
		return &VRAM[address - 0x8000];
	} else if (address < 0xC000) {
		return &SRAM[address - 0xA000];
	} else if (address < 0xE000) {
		return &RAM[address - 0xC000];
	} else if (address < 0xFE00) {
		return &RAM[address - 0xE000]; // Echo of RAM at (0xC000 - 0xDDFF)
	} else if (address < 0xFEA0) {
		return &OAM[address - 0xFE00];
	} else if (address < 0xFF00) {
		return NULL;  // Not used
	} else if (address < 0xFF80) {
		return &HIO[address - 0xFF00];
	} else if (address < 0xFFFF) {
		return &HIO[address - 0xFF80];
	}

	//last possible option as 0xFFFF
	return &registers.IE;
}


//---------------------------------------------------------------------------------------------------


// ==(Control)==
void gb_mmu_call(uint16_t address) {
	gb_mmu_push(registers.PC);

	registers.PC = address;
}

void gb_mmu_return() {
	gb_mmu_pop(&registers.PC);
}

void gb_mmu_push(uint16_t value) {
	uint8_t high = (uint8_t)((value & 0xFF00) >> 8);
	uint8_t low = (uint8_t)(value & 0x00FF);
	gb_mmu_write(registers.SP - 1, high);
	gb_mmu_write(registers.SP - 2, low);

	registers.SP -= 2;
}

void gb_mmu_pop(uint16_t* reg) {
	(*reg) = (gb_mmu_read(registers.SP+1) << 8) | gb_mmu_read(registers.SP);

	registers.SP += 2;
}

void gb_mmu_restart(uint8_t value) {
	gb_mmu_push(registers.PC);

	registers.PC = (uint16_t)(value & 0x00FF);
}
// ==(Control)==