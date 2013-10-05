#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"
#include "http.h"

#define MY_UUID { 0x91, 0x41, 0xB6, 0x28, 0xBC, 0x89, 0x49, 0x8E, 0xB1, 0x47, 0x04, 0x9F, 0x49, 0xC0, 0x99, 0xAC }
PBL_APP_INFO(MY_UUID, "Watch", "Jorge Izquierdo", 1, 0, DEFAULT_MENU_ICON, APP_INFO_STANDARD_APP);
#define APP_COOKIE 1949327672


Window window;

char text[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer nec odio. Praesent libero. Sed cursus ante dapibus diam. Sed nisi. Nulla quis sem at nibh elementum imperdiet. Duis sagittis ipsum. Praesent mauris. Fusce nec tellus sed augue semper porta. Mauris massa. Vestibulum lacinia arcu eget nulla. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Curabitur sodales ligula in libero. Sed dignissim lacinia nunc. Curabitur tortor. Pellentesque nibh. Aenean quam. In scelerisque sem at dolor. Maecenas mattis. Sed convallis tristique sem. Proin ut ligula vel nunc egestas porttitor. Morbi lectus risus, iaculis vel, suscipit quis, luctus non, massa. Fusce ac turpis quis ligula lacinia aliquet. Mauris ipsum. Nulla metus metus, ullamcorper vel, tincidunt sed, euismod in, nibh. Quisque volutpat condimentum velit. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Nam nec ante. Sed lacinia, urna non tincidunt mattis, tortor neque adipiscing diam, a cursus ipsum ante quis turpis. Nulla facilisi. Ut fringilla. Suspendisse potenti. Nunc feugiat mi a tellus consequat imperdiet. Vestibulum sapien. Proin quam. Etiam ultrices. Suspendisse in justo eu magna luctus suscipit. Sed lectus. Integer euismod lacus luctus magna. Quisque cursus, metus vitae pharetra auctor, sem massa mattis sem, at interdum magna augue eget diam. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Morbi lacinia molestie dui. Praesent blandit dolor. Sed non quam. In vel mi sit amet augue congue elementum. Morbi in ipsum sit amet pede facilisis laoreet. Donec lacus nunc, viverra nec, blandit vel, egestas et, augue. Vestibulum tincidunt malesuada tellus. Ut ultrices ultrices enim. Curabitur sit amet mauris. Morbi in dui quis est pulvinar ullamcorper. Nulla facilisi. Integer lacinia sollicitudin massa. Cras metus. Sed aliquet risus a tortor. Integer id quam. Morbi mi. Quisque nisl felis, venenatis tristique, dignissim in, ultrices sit amet, augue. Proin sodales libero eget ante. Nulla quam. Aenean laoreet. Vestibulum nisi lectus, commodo ac, facilisis ac, ultricies eu, pede. Ut orci risus, accumsan porttitor, cursus quis, aliquet eget, justo. Sed pretium blandit orci. Ut eu diam at pede suscipit sodales. Aenean lectus elit, fermentum non, convallis id, sagittis at, neque. Nullam mauris orci, aliquet et, iaculis et, viverra vitae, ligula. Nulla ut felis in purus aliquam imperdiet. Maecenas aliquet mollis lectus. Vivamus consectetuer risus et tortor. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer nec odio. Praesent libero. Sed cursus ante dapibus diam. Sed nisi. Nulla quis sem at nibh elementum imperdiet. Duis sagittis ipsum. Praesent mauris. Fusce nec tellus sed augue semper porta. Mauris massa. Vestibulum lacinia arcu eget nulla. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Curabitur sodales ligula in libero. Sed dignissim lacinia nunc. Curabitur tortor. Pellentesque nibh. Aenean quam. In scelerisque sem at dolor. Maecenas mattis. Sed convallis tristique sem. Proin ut ligula vel nunc egestas porttitor. Morbi lectus risus, iaculis vel, suscipit quis, luctus non, massa. Fusce ac turpis quis ligula lacinia aliquet. Mauris ipsum. Nulla metus metus, ullamcorper vel, tincidunt sed, euismod in, nibh. Quisque volutpat condimentum velit. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Nam nec ante. Sed lacinia, urna non tincidunt mattis, tortor neque adipiscing diam, a cursus ipsum ante quis turpis. Nulla facilisi. Ut fringilla. Suspendisse potenti. Nunc feugiat mi a tellus consequat imperdiet. Vestibulum sapien. Proin quam. Etiam ultrices. Suspendisse in justo eu magna luctus suscipit. Sed lectus. Integer euismod lacus luctus magna. Quisque cursus, metus vitae pharetra auctor, sem massa mattis sem, at interdum magna augue eget diam. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Morbi lacinia molestie dui. Praesent blandit dolor. Sed non quam. In vel mi sit amet augue congue elementum. Morbi in ipsum sit amet pede facilisis laoreet. Donec lacus nunc, viverra nec, blandit vel, egestas et, augue. Vestibulum tincidunt malesuada tellus. Ut ultrices ultrices enim. Curabitur sit amet mauris. Morbi in dui quis est pulvinar ullamcorper. Nulla facilisi. Integer lacinia sollicitudin massa. Cras metus. Sed aliquet risus a tortor. Integer id quam. Morbi mi. Quisque nisl felis, venenatis tristique, dignissim in, ultrices sit amet, augue. Proin sodales libero eget ante. Nulla quam. Aenean laoreet. Vestibulum nisi lectus, commodo ac, facilisis ac, ultricies eu, pede. Ut orci risus, accumsan porttitor, cursus quis, aliquet eget, justo. Sed pretium blandit orci. Ut eu diam at pede suscipit sodales. Aenean lectus elit, fermentum non, convallis id, sagittis at, neque. Null";
const int res = 9;
const int up = 2;
const int down = -1;

int progress = 0;

Window w2;
TextLayer t2;

ScrollLayer scroll_layer;
InverterLayer inverter_layer;
const int vert_scroll_text_padding = 4;


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
/*void do_request_text(){
	DictionaryIterator *body;
	HTTPResult result = http_out_get("http://mipebbleapp.appspot.com/geta", APP_COOKIE, &body);
	if(result != HTTP_OK) {
		text = "Req failed";
		return;
	}
	if(http_out_send() != HTTP_OK) {
		text = "Req failed";
		return;
	}
}*/
void show_text_window(){
	
	
	window_init(&w2, "Text");
  	window_stack_push(&w2, true /* Animated */);
	
	 const GRect max_text_bounds = GRect(0, 0, 144, 2000);

  // Initialize the scroll layer
  scroll_layer_init(&scroll_layer, w2.layer.bounds);

  // This binds the scroll layer to the window so that up and down map to scrolling
  // You may use scroll_layer_set_callbacks to add or override interactivity
  scroll_layer_set_click_config_onto_window(&scroll_layer, &w2);

  // Set the initial max size
  scroll_layer_set_content_size(&scroll_layer, max_text_bounds.size);

  // Initialize the text layer
  text_layer_init(&t2, max_text_bounds);
  text_layer_set_text(&t2, text);

  // Change the font to a nice readable one
  // This is system font; you can inspect pebble_fonts.h for all system fonts
  // or you can take a look at feature_custom_font to add your own font
  text_layer_set_font(&t2, fonts_get_system_font(FONT_KEY_GOTHIC_14));

  // Trim text layer and scroll content to fit text box
  GSize max_size = text_layer_get_max_used_size(app_get_current_graphics_context(), &t2);
  text_layer_set_size(&t2, max_size);
  scroll_layer_set_content_size(&scroll_layer, GSize(144, max_size.h + vert_scroll_text_padding));

  // Add the layers for display
  scroll_layer_add_child(&scroll_layer, &t2.layer);

  

  layer_add_child(&w2.layer, &scroll_layer.layer);
}
void failed(int32_t cookie, int http_status, void* context) {
	//text = "Couldn't load alright";
}
void success(int32_t cookie, int http_status, DictionaryIterator* received, void* context) {
	
	Tuple* textx = dict_read_first(received);
	if (textx){
		//text = textx->value->cstring;
		
	}
	
}
void reconnect(void* context) {
	
//do_request_text();
}
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
	progress += up;
}


void down_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
  (void)recognizer;
  (void)window;
	
	progress += down;
}


void select_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
  (void)recognizer;
  (void)window;
	
	if (res == progress){
		show_text_window();
	}
	else {
		
		progress = 50000;
	}
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
	//text = "ola k ase";
	
  // Attach our desired button functionality
  window_set_click_config_provider(&window, (ClickConfigProvider) click_config_provider);
		http_register_callbacks((HTTPCallbacks){.failure=failed,.success=success,.reconnect=reconnect}, (void*)ctx);
	//do_request_text();
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
        },
	  .messaging_info = {
			.buffer_sizes = {
				.inbound = 1024,
				.outbound = 256,
			}
		}

  };
  app_event_loop(params, &handlers);
}

