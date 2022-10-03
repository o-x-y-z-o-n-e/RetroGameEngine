#include "gb/core.h"
#include "rge.h"

#define BIT_VALUE(A, b) ((A) & (0x01 << (b)))

#define V_BLANK_PERIOD 1.0800F
#define H_BLANK_PERIOD 0.0486F
#define MODE_2_PERIOD  0.0190F
#define MODE_3_PERIOD  0.0410F


pixel_t palette[] = {
	{ 0xFF, 0xFF, 0xFF, 0xFF },
	{ 0xC0, 0xC0, 0xC0, 0xFF },
	{ 0x60, 0x60, 0x60, 0xFF },
	{ 0x00, 0x00, 0x00, 0xFF }
};

static uint8_t* LCDC;
static uint8_t* STAT;
static uint8_t* SCY;
static uint8_t* SCX;
static uint8_t* LY;
static uint8_t* LYC;
static uint8_t* WY;
static uint8_t* WX;

static float update_counter;


//---------------------------------------------------------------------------------------------------


static pixel_t get_tile_pixel(uint8_t* tile, int px, int py) {
	uint8_t c = ((tile[(py * 2)] & (0x80 >> px)) >> (7 - px))
		| ((tile[(py * 2) + 1] & (0x80 >> px)) >> (7 - px + 1));

	return palette[c];
}


//---------------------------------------------------------------------------------------------------


static void set_line(int i) {
	*LY = i;

	if(BIT_VALUE(*STAT, 6)) {
		if(*LY == *LYC) {
			gb_cpu_int_flag_set(INTERRUPT_LCD, 1);
		}
	}
}


//---------------------------------------------------------------------------------------------------


static void set_mode(int i) {
	*STAT &= ~0x03;      //clear STAT mode flags
	*STAT |= (i & 0x03); //set STAT mode flags

	//call STAT interrupt for modes 0, 1 & 2 if the respective interrupt enable is set.
	if(i < 3) {
		if(BIT_VALUE(*STAT, i + 3)) {
			gb_cpu_int_flag_set(INTERRUPT_LCD, 1);
		}
	}
}


//---------------------------------------------------------------------------------------------------


static void draw_line() {
	uint8_t* tilemap = gb_mmu_location(BIT_VALUE(*LCDC, 3) ? 0x9C00 : 0x9800);
	uint8_t* tiledata = gb_mmu_location(BIT_VALUE(*LCDC, 4) ? 0x8000 : 0x8800);

	int map_pixel_y = (*SCY + *LY) % 256;
	int tile_coord_y = map_pixel_y / 8;
	int tile_pixel_y = map_pixel_y % 8;

	for(int x = 0; x < SCREEN_WIDTH; x++) {
		int map_pixel_x = (*SCX + x) % 256;
		int tile_coord_x = map_pixel_x / 8;
		int tile_pixel_x = map_pixel_x % 8;

		uint8_t tile_index = tilemap[tile_coord_x + (tile_coord_y * 32)];
		uint8_t* tile_pointer = &tiledata[(BIT_VALUE(*LCDC, 4) ? tile_index : (int8_t)tile_index) * 16];

		pixel_t tile_pixel = get_tile_pixel(tile_pointer, tile_pixel_x, tile_pixel_y);

		rge_renderer_set_pixel(x, *LY, tile_pixel);
		//display_pixel(x, *LY, tile_pixel.r, tile_pixel.g, tile_pixel.b);
	}
}


//---------------------------------------------------------------------------------------------------


static void debug_tilemap() {
	uint8_t* tilemap = gb_mmu_location(BIT_VALUE(*LCDC, 3) ? 0x9C00 : 0x9800);
	uint8_t* tiledata = gb_mmu_location(BIT_VALUE(*LCDC, 4) ? 0x8000 : 0x8800);

	for(int x = 0; x < 32; x++) {
		for(int y = 0; y < 32; y++) {
			for(int px = 0; px < 8; px++) {
				for(int py = 0; py < 8; py++) {
					uint8_t i_tile = tilemap[x + (y * 32)];
					uint8_t* tile = &tiledata[i_tile * 16];

					pixel_t c = get_tile_pixel(tile, px, py);

					rge_renderer_set_pixel(
						(x * 8) + px,
						(y * 8) + py,
						c
					);

					// display_pixel((x * 8) + px, (y * 8) + py, c.r, c.g, c.b);
				}
			}
		}
	}

}


//---------------------------------------------------------------------------------------------------


void gb_ppu_init() {
	LCDC = gb_mmu_location(0xFF40);
	STAT = gb_mmu_location(0xFF41);
	SCY  = gb_mmu_location(0xFF42);
	SCX  = gb_mmu_location(0xFF43);
	LY   = gb_mmu_location(0xFF44);
	LYC  = gb_mmu_location(0xFF45);

	WY   = gb_mmu_location(0xFF4A);
	WX   = gb_mmu_location(0xFF4B);

	//turn on display
	*LCDC |= 0x80;
}


//---------------------------------------------------------------------------------------------------


void gb_ppu_close() {

}


//---------------------------------------------------------------------------------------------------


void gb_ppu_step(int ms_tick_delta) {
	if (!BIT_VALUE(*LCDC, 7)) {
		return;
	}

	update_counter += (ms_tick_delta);

	int lcd_mode = *STAT & 0x03;

	if (lcd_mode == 2) {
		if (update_counter > MODE_2_PERIOD) {
			update_counter -= MODE_2_PERIOD;
			set_mode(3);
		}
	} else if (lcd_mode == 3) {
		if (update_counter > MODE_3_PERIOD) {
			update_counter -= MODE_3_PERIOD;
			set_mode(0);

			draw_line();
		}
	} else if (lcd_mode == 0) {
		if (update_counter > H_BLANK_PERIOD) {
			update_counter -= H_BLANK_PERIOD;

			set_line(*LY + 1);

			if (*LY < SCREEN_HEIGHT) {
				set_mode(2);
			} else {
				set_mode(1);

				rge_window_refresh();
			}
		}
	} else if (lcd_mode == 1) {
		if (update_counter > V_BLANK_PERIOD) {
			update_counter -= V_BLANK_PERIOD;

			set_line(0);
			set_mode(2);
		}
	}
}