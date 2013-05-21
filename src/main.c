
#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"
#include "http.h"

#define MY_UUID { 0x91, 0x41, 0xB6, 0x28, 0xBC, 0x89, 0x49, 0x8E, 0xB1, 0x47, 0x04, 0x9F, 0x49, 0xC0, 0x99, 0xAD }
PBL_APP_INFO(MY_UUID, "Reloj ;)", "Jorge Izquierdo", 1, 0, DEFAULT_MENU_ICON, APP_INFO_STANDARD_APP);


Window window;



BmpContainer background;

BmpContainer numbers[4];
int states[4] = {-1, -1, -1, -1};
int resources[10] = {
    RESOURCE_ID_IMAGE_ZERO,
    RESOURCE_ID_IMAGE_ONE, 
    RESOURCE_ID_IMAGE_TWO,
    RESOURCE_ID_IMAGE_THREE,
    RESOURCE_ID_IMAGE_FOUR,
    RESOURCE_ID_IMAGE_FIVE,
    RESOURCE_ID_IMAGE_SIX,
    RESOURCE_ID_IMAGE_SEVEN,
    RESOURCE_ID_IMAGE_EIGHT,
    RESOURCE_ID_IMAGE_NINE
};

void unload_number(int row, int pos) {
    int idx = 2 * row + pos;

    if(states[idx] != -1) {
        layer_remove_from_parent(&numbers[idx].layer.layer);
        bmp_deinit_container(&numbers[idx]);
        states[idx] = -1;
    }
} 
    
void load_number(int row, int pos, int resid) {
    int idx = 2 * row + pos;

    unload_number(row, pos);
    
    states[idx] = resid;
    bmp_init_container(resid, &numbers[idx]);
    numbers[idx].layer.layer.frame.origin.x = (pos == 0) ? 25 : 77;
    numbers[idx].layer.layer.frame.origin.y = (row == 0) ? 11 : 89;
    layer_add_child(&window.layer, &numbers[idx].layer.layer);
}

void show_time(PblTm* t) {
    unsigned short hour = (clock_is_24h_style() ? t->tm_hour : (t->tm_hour > 12 ? t->tm_hour - 12 : t->tm_hour));
    
    load_number(0, 0, resources[hour / 10]);
    load_number(0, 1, resources[hour % 10]);
    load_number(1, 0, resources[t->tm_min / 10]);
    load_number(1, 1, resources[t->tm_min % 10]);
}

// Modify these common button handlers

void up_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
  (void)recognizer;
  (void)window;

}


void down_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
  (void)recognizer;
  (void)window;

}


void select_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
  (void)recognizer;
  (void)window;

  //text_layer_set_text(&textLayer, "Select!");
}


void select_long_click_handler(ClickRecognizerRef recognizer, Window *window) {
  (void)recognizer;
  (void)window;

}


// This usually won't need to be modified

void click_config_provider(ClickConfig **config, Window *window) {
  (void)window;

  config[BUTTON_ID_SELECT]->click.handler = (ClickHandler) select_single_click_handler;

  config[BUTTON_ID_SELECT]->long_click.handler = (ClickHandler) select_long_click_handler;

  config[BUTTON_ID_UP]->click.handler = (ClickHandler) up_single_click_handler;
  config[BUTTON_ID_UP]->click.repeat_interval_ms = 100;

  config[BUTTON_ID_DOWN]->click.handler = (ClickHandler) down_single_click_handler;
  config[BUTTON_ID_DOWN]->click.repeat_interval_ms = 100;
}


// Standard app initialisation

void handle_init(AppContextRef ctx) {
  (void)ctx;

  window_init(&window, "Hola mama");
  window_stack_push(&window, true /* Animated */);
	window_set_fullscreen(&window, true);	
  resource_init_current_app(&APP_RESOURCES);
    
    bmp_init_container(RESOURCE_ID_IMAGE_BACKGROUND, &background);
    layer_add_child(&window.layer, &background.layer.layer);
    
    PblTm t;
    get_time(&t);
    show_time(&t);


  // Attach our desired button functionality
  window_set_click_config_provider(&window, (ClickConfigProvider) click_config_provider);
}

void handle_deinit(AppContextRef ctx) {
    (void) ctx;
    
    for(int i = 0; i < 4; i++)
        unload_number(i >> 1, i & 1);
    
    bmp_deinit_container(&background);
}

void handle_minute_tick(AppContextRef ctx, PebbleTickEvent* t) {
    (void) ctx;
    
    show_time(t->tick_time);
}
void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,
	.deinit_handler = &handle_deinit,
        
    .tick_info = {
            .tick_handler = &handle_minute_tick,
            .tick_units = MINUTE_UNIT
        }

  };
  app_event_loop(params, &handlers);
}
