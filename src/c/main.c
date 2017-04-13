#include <pebble.h>

static Window *s_main_window;
static TextLayer *s_time_layer; // Will display the time in the main Window

// Handler for loading the Window and its elements
static void main_window_load(Window *window) {
	// Get information about the window
	Layer *window_layer = window_get_root_layer(window);
	GRect bounds = layer_get_bounds(window_layer);
	
	// Create the TextLayer with specific bounds
	s_time_layer = text_layer_create(
		GRect(0, PBL_IF_ROUND_ELSE(58, 52), bounds.size.w, 50));	// Changes display based on round or rectanguler display
	
	// Enhance the look of the layout
	text_layer_set_background_color(s_time_layer, GColorClear);
	text_layer_set_text_color(s_time_layer, GColorBlack);
	text_layer_set_text(s_time_layer, "00:00");
	text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
	text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);
	
	// Add TextLayer as child layer to Window's root layer
	layer_add_child(window_layer, text_layer_get_layer(s_time_layer));
}

// Handler for unloading the Window
static void main_window_unload(Window *window) {
	// Destroy TextLayer to free up memory
	text_layer_destroy(s_time_layer);
}

static void init() {
	// Instantiate main Window element
	s_main_window = window_create();
	
	// Instantiate handlers to manage elements in Window object
	window_set_window_handlers(s_main_window, (WindowHandlers) {
		.load = main_window_load,
		.unload = main_window_unload
	});
}

static void deinit() {
	// Destroy Window to free memory
	window_destroy(s_main_window);
}

int main(void) {
	init();
	app_event_loop();	// wait for system until exit
	deinit();
}
