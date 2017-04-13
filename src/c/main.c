#include <pebble.h>

static Window *s_main_window; // Root window
static TextLayer *s_time_layer; // Will display the time in the main Window
static GFont s_time_font; // Custom font

static void update_time() {
	// Get the tm structure
	time_t temp = time(NULL);
	struct tm *tick_time = localtime(&temp);
	
	// Write current hours and minutes into a buffer
	static char s_buffer[8];
	strftime(s_buffer, sizeof(s_buffer), clock_is_24h_style() ? "%H:%M" : "%I:%M", tick_time);
	
	// Display new time on TextLayer
	text_layer_set_text(s_time_layer, s_buffer);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
	update_time();
}

// Handler for loading the Window and its elements
static void main_window_load(Window *window) {
	// Get information about the window
	Layer *window_layer = window_get_root_layer(window);
	GRect bounds = layer_get_bounds(window_layer);
	
	// Create GFont
	s_time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_KEY_FOOTFIGHT_BOLD_42));
	
	// Create the TextLayer with specific bounds
	s_time_layer = text_layer_create(
		GRect(0, PBL_IF_ROUND_ELSE(58, 100), bounds.size.w, 50));	// Changes display based on round or rectanguler display
	
	// Enhance the look of the layout
	text_layer_set_background_color(s_time_layer, GColorClear);
	text_layer_set_text_color(s_time_layer, GColorBlack);
	text_layer_set_text(s_time_layer, "00:00");
	text_layer_set_font(s_time_layer, s_time_font);		// Apply custom f
	text_layer_set_text_alignment(s_time_layer, GTextAlignmentRight);
	
	// Add TextLayer as child layer to Window's root layer
	layer_add_child(window_layer, text_layer_get_layer(s_time_layer));
}

// Handler for unloading the Window
static void main_window_unload(Window *window) {
	// Destroy TextLayer to free up memory
	text_layer_destroy(s_time_layer);
	
	// Unload custom font
	fonts_unload_custom_font(s_time_font);
}

static void init() {
	// Instantiate main Window element
	s_main_window = window_create();
	
	// Instantiate handlers to manage elements in Window object
	window_set_window_handlers(s_main_window, (WindowHandlers) {
		.load = main_window_load,
		.unload = main_window_unload
	});
	
	// Instantiate TimeTickerService
	tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
	
	// Show the Window on watch, with animated=true
	window_stack_push(s_main_window, true);
	
	// Make sure time is displayed from start
	update_time();
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
