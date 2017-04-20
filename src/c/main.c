#include <pebble.h>

static Window *s_main_window; // Root window
static TextLayer *s_time_layer; // Will display the time in the main Window
static TextLayer *s_its_layer; // Displays the word "It's" in the main Window
static TextLayer *s_hey_layer; // Displays the word "Hey..." in the main Window
static GFont s_time_font; // Custom font for time and IT'S TextLayers
static GFont s_hey_font; // Custom font for Hey TextLayer
static BitmapLayer *s_background_layer;	// Background layer which holds the GBitmap
static GBitmap *s_background_bitmap; //Custom bitmap background

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
	
	// Create GBitmap
	s_background_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_PAPER_CRUMPLED);
	
	// Create BitmapLayer to display the GBitmap
	s_background_layer = bitmap_layer_create(bounds);
	
	// Create GFont for time TextLayer
	s_time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_KEY_FOOTFIGHT_BOLD_42));
	
	// Create GFont for Hey TextLayer
	s_hey_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_KEY_FOOTFIGHT_BOLD_19));
	
	// Create the TextLayer with specific bounds which displays time
	s_time_layer = text_layer_create(
		GRect(0, PBL_IF_ROUND_ELSE(58, 100), bounds.size.w, 50));
	
	// Enhance the look of the time layer
	text_layer_set_background_color(s_time_layer, GColorClear);
	text_layer_set_text_color(s_time_layer, GColorBlack);
	text_layer_set_text(s_time_layer, "00:00");
	text_layer_set_font(s_time_layer, s_time_font);
	text_layer_set_text_alignment(s_time_layer, GTextAlignmentRight);
	
	// Create TextLayer to display "IT'S"
	s_its_layer = text_layer_create(
		GRect(0, PBL_IF_ROUND_ELSE(58, 38), bounds.size.w-10, 50));		// Apply a left shift by 10 units
	
	// Enhance the look of the IT'S layer
	text_layer_set_background_color(s_its_layer, GColorClear);
	text_layer_set_text_color(s_its_layer, GColorBlack);
	text_layer_set_text(s_its_layer, "IT'S");
	text_layer_set_font(s_its_layer, s_time_font);
	text_layer_set_text_alignment(s_its_layer, GTextAlignmentRight);
	
	// Set the bitmap onto the layer and add to window
	bitmap_layer_set_bitmap(s_background_layer, s_background_bitmap);
	layer_add_child(window_layer, bitmap_layer_get_layer(s_background_layer));
	
	// Add the IT'S TextLayer as child layer to Window
	layer_add_child(window_layer, text_layer_get_layer(s_its_layer));
	
	// Add time TextLayer as child layer to Window's root layer
	layer_add_child(window_layer, text_layer_get_layer(s_time_layer));
}

// Handler for unloading the Window
static void main_window_unload(Window *window) {
	// Destroy GBitmap
	gbitmap_destroy(s_background_bitmap);
	
	// Destroy the BitmapLayer
	bitmap_layer_destroy(s_background_layer);
	
	// Destroy the IT'S TextLayer
	text_layer_destroy(s_its_layer);
	
	// Destroy time TextLayer to free up memory
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
