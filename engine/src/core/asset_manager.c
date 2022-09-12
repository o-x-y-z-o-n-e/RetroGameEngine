#include "core/asset_manager.h"



//------------------------------------------------------------------------------


size_t rge_get_str_hash(const char* str) {
	size_t hash = 5381;
	char c;
	while((c = *str++) != 0)
		hash = ((hash << 5) + hash) + c;

	return hash;
}


//------------------------------------------------------------------------------


int rge_assets_init() {

	return 1;
}