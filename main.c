#include <pebble.h>
  
static Window *s_main_window;
static TextLayer *s_time_layer;
static TextLayer *s_time_layer2;
static TextLayer *s_time_layer3;

//int str_cut(char *str, int begin, int len){
    //int l = strlen(str);

    //if (len < 0) len = l - begin;
    //if (begin + len > l) len = l - begin;
    //memmove(str + begin, str + begin + len, l - len + 1);

    //return len;
//}

char* itoa(int i, char b[]){
    char const digit[] = "0123456789";
    char* p = b;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    int shifter = i;
    do{ //Move to where rep ends
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{ //Move back, inserting digits soos jy gaan
        *--p = digit[i%10];
        i = i/10;
    }while(i);
    return b;
}

static void update_time() {
  // Get a tm structure
  time_t temp = time(NULL); 
  const struct tm *tick_time = localtime(&temp);

  // Create a long-lived buffer
  //static char buffer[] = "00:00";

  // Write the current hours and minutes into the buffer
  //if(clock_is_24h_style() == true) {
    //Use 24h hour format
    //strftime(buffer, sizeof("00:00"), "%H:%M", tick_time);
  //} else {
    //Use 12 hour format
    //strftime(buffer, sizeof("00:00"), "%I:%M", tick_time);
  //}
	
	char s_min[] = "";
	strftime(s_min, sizeof("00"), "%M", tick_time);
	char *s_h = "";
	strftime(s_h, sizeof("00"), "%I", tick_time);
	
	int i_min = atoi(s_min);
	int i_h = atoi(s_h);
	
	int i_min1 = 60 - i_min;
	
	char *s_min1 = "";
	s_min1 = itoa(i_min1, s_min1);
		
	char *s_h1 = "ERROR";
	
	if(i_h == 1){ //conversion to words
		s_h = "een\0";
		s_h1 = "twee\0";
	}else if(i_h == 2){
		s_h = "twee\0";
		s_h1 = "drie\0";
	}else if(i_h == 3){
		s_h = "drie\0";
		s_h1 = "vier\0";
	}else if(i_h == 4){
		s_h = "vier\0";
		s_h1 = "vyf\0";
	}else if(i_h == 5){
		s_h = "vyf\0";
		s_h1 = "ses\0";
	}else if(i_h == 6){
		s_h = "ses\0";
		s_h1 = "sewe\0";
	}else if(i_h == 7){
		s_h = "sewe\0";
		s_h1 = "agt\0";
	}else if(i_h == 8){
		s_h = "agt\0";
		s_h1 = "nege\0";
	}else if(i_h == 9){
		s_h = "nege\0";
		s_h1 = "tien\0";
	}else if (i_h == 10){
		s_h = "tien\0";
		s_h1 = "elf\0";
	}else if (i_h == 11){
		s_h = "elf\0";
		s_h1 = "twaalf\0";
	}else if(i_h == 12){
		s_h = "twaalf\0";
		s_h1 = "een\0"; //om half 13 te vermy
	}
	
	//char* s_h1 = "";
	//s_h1 = itoa(i_h1, s_h1); // convert int to string.
	
	if((i_min >= 1) && (i_min <= 59)){
		text_layer_set_background_color(s_time_layer, GColorClear);
  	text_layer_set_text_color(s_time_layer, GColorBlack);
		text_layer_set_background_color(s_time_layer3, GColorBlack);
  	text_layer_set_text_color(s_time_layer3, GColorWhite);
	}else if(i_min == 0){
		text_layer_set_background_color(s_time_layer, GColorBlack);
  	text_layer_set_text_color(s_time_layer, GColorWhite);
		text_layer_set_background_color(s_time_layer3, GColorClear);
  	text_layer_set_text_color(s_time_layer3, GColorBlack);
	}
	
	if(i_min == 0){
		text_layer_set_text(s_time_layer, s_h);					// 0
		text_layer_set_text(s_time_layer2, "uur");
		text_layer_set_text(s_time_layer3, NULL);
	}else if(i_min == 1){
		text_layer_set_text(s_time_layer, "een");				// 1
		text_layer_set_text(s_time_layer2, "oor");
		text_layer_set_text(s_time_layer3, s_h);
	}else if(i_min == 2){
		text_layer_set_text(s_time_layer, "twee\0");		// 2
		text_layer_set_text(s_time_layer2, "oor");
		text_layer_set_text(s_time_layer3, s_h);
	}else if(i_min == 3){
		text_layer_set_text(s_time_layer, "drie");			// 3
		text_layer_set_text(s_time_layer2, "oor");
		text_layer_set_text(s_time_layer3, s_h);
	}else if(i_min == 4){
		text_layer_set_text(s_time_layer, "vier");			// 4
		text_layer_set_text(s_time_layer2, "oor");
		text_layer_set_text(s_time_layer3, s_h);
	}else if(i_min == 5){
		text_layer_set_text(s_time_layer, "vyf");				// 5
		text_layer_set_text(s_time_layer2, "oor");
		text_layer_set_text(s_time_layer3, s_h);
	}else if(i_min == 6){
		text_layer_set_text(s_time_layer, "ses");				// 6
		text_layer_set_text(s_time_layer2, "oor");
		text_layer_set_text(s_time_layer3, s_h);
	}else if(i_min == 7){
		text_layer_set_text(s_time_layer, "sewe");			// 7
		text_layer_set_text(s_time_layer2, "oor");
		text_layer_set_text(s_time_layer3, s_h);
	}else if(i_min == 8){
		text_layer_set_text(s_time_layer, "agt");				// 8
		text_layer_set_text(s_time_layer2, "oor");
		text_layer_set_text(s_time_layer3, s_h);
	}else if(i_min == 9){
		text_layer_set_text(s_time_layer, "nege");			// 9
		text_layer_set_text(s_time_layer2, "oor");
		text_layer_set_text(s_time_layer3, s_h);
	}else if(i_min == 10){
		text_layer_set_text(s_time_layer, "tien");			// 10
		text_layer_set_text(s_time_layer2, "oor");
		text_layer_set_text(s_time_layer3, s_h);
	}else if(i_min == 11){
		text_layer_set_text(s_time_layer, "elf");				// 11
		text_layer_set_text(s_time_layer2, "oor");
		text_layer_set_text(s_time_layer3, s_h);
	}else if(i_min == 12){
		text_layer_set_text(s_time_layer, "twaalf");		// 12
		text_layer_set_text(s_time_layer2, "oor");
		text_layer_set_text(s_time_layer3, s_h);
	}else if((i_min >= 13) && (i_min <= 29) && (i_min != 15)){
		char *temp = "";
		strcpy(temp, s_min);
		strcat(temp, "\0");
		text_layer_set_text(s_time_layer, temp);				// 13 - 29, excl 15
		text_layer_set_text(s_time_layer2, "oor");
		text_layer_set_text(s_time_layer3, s_h);
	}else if(i_min == 15){
		text_layer_set_text(s_time_layer, "kwart");			// 15
		text_layer_set_text(s_time_layer2, "oor");
		text_layer_set_text(s_time_layer3, s_h);
	}else if(i_min == 30){
		text_layer_set_text(s_time_layer, NULL);				// 30
		text_layer_set_text(s_time_layer2, "half");
		text_layer_set_text(s_time_layer3, s_h1);
	}else if((i_min >= 31) && (i_min <= 47) && (i_min != 45)){
		char *temp = "";
		strcpy(temp, s_min1);
		strcat(temp, "\0");
		text_layer_set_text(s_time_layer, temp);			// 31 - 47, excl 45
		text_layer_set_text(s_time_layer2, "voor");
		text_layer_set_text(s_time_layer3, s_h1);
	}else if(i_min == 45){
		text_layer_set_text(s_time_layer, "kwart");			// 45
		text_layer_set_text(s_time_layer2, "voor");
		text_layer_set_text(s_time_layer3, s_h1);
	}else if(i_min == 48){
		text_layer_set_text(s_time_layer, "twaalf");		// 48
		text_layer_set_text(s_time_layer2, "voor");
		text_layer_set_text(s_time_layer3, s_h1);
	}else if(i_min == 49){
		text_layer_set_text(s_time_layer, "elf");				// 49
		text_layer_set_text(s_time_layer2, "voor");
		text_layer_set_text(s_time_layer3, s_h1);
	}else if(i_min == 50){
		text_layer_set_text(s_time_layer, "tien");			// 50
		text_layer_set_text(s_time_layer2, "voor");
		text_layer_set_text(s_time_layer3, s_h1);
	}else if(i_min == 51){
		text_layer_set_text(s_time_layer, "nege");			// 51
		text_layer_set_text(s_time_layer2, "voor");
		text_layer_set_text(s_time_layer3, s_h1);
	}else if(i_min == 52){
		text_layer_set_text(s_time_layer, "agt");				// 52
		text_layer_set_text(s_time_layer2, "voor");
		text_layer_set_text(s_time_layer3, s_h1);
	}else if(i_min == 53){
		text_layer_set_text(s_time_layer, "sewe");			// 53
		text_layer_set_text(s_time_layer2, "voor");
		text_layer_set_text(s_time_layer3, s_h1);
	}else if(i_min == 54){
		text_layer_set_text(s_time_layer, "ses");				// 54
		text_layer_set_text(s_time_layer2, "voor");
		text_layer_set_text(s_time_layer3, s_h1);
	}else if(i_min == 55){
		text_layer_set_text(s_time_layer, "vyf");				// 55
		text_layer_set_text(s_time_layer2, "voor");
		text_layer_set_text(s_time_layer3, s_h1);
	}else if(i_min == 56){
		text_layer_set_text(s_time_layer, "vier");			// 56
		text_layer_set_text(s_time_layer2, "voor");
		text_layer_set_text(s_time_layer3, s_h1);
	}else if(i_min == 57){
		text_layer_set_text(s_time_layer, "drie");			// 57
		text_layer_set_text(s_time_layer2, "voor");
		text_layer_set_text(s_time_layer3, s_h1);
	}else if(i_min == 58){
		text_layer_set_text(s_time_layer, "twee\0");		// 58
		text_layer_set_text(s_time_layer2, "voor");
		text_layer_set_text(s_time_layer3, s_h1);
	}else if(i_min == 59){
		text_layer_set_text(s_time_layer, "een");				// 59
		text_layer_set_text(s_time_layer2, "voor");
		text_layer_set_text(s_time_layer3, s_h1);
	}else{
		text_layer_set_text(s_time_layer, "ERROR");			// Else
		text_layer_set_text(s_time_layer2, "ERROR");
		text_layer_set_text(s_time_layer3, "ERROR");
	}
}

static void main_window_load(Window *window) {
  // Create time TextLayer
  s_time_layer = text_layer_create(GRect(0, 0, 144, 65));
  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_text_color(s_time_layer, GColorBlack);
  text_layer_set_text(s_time_layer, "ERROR\0");
  
  s_time_layer2 = text_layer_create(GRect(0, 47, 144, 65));
  text_layer_set_background_color(s_time_layer2, GColorClear);
  text_layer_set_text_color(s_time_layer2, GColorBlack);
  text_layer_set_text(s_time_layer2, "ERROR\0");
	
	s_time_layer3 = text_layer_create(GRect(0, 105, 144, 65));
  text_layer_set_background_color(s_time_layer3, GColorBlack);
  text_layer_set_text_color(s_time_layer3, GColorClear);
  text_layer_set_text(s_time_layer3, "ERROR\0");
	 
  // Improve the layout to be more like a watchface
  text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);
  
  text_layer_set_font(s_time_layer2, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_text_alignment(s_time_layer2, GTextAlignmentCenter);
	
	text_layer_set_font(s_time_layer3, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_text_alignment(s_time_layer3, GTextAlignmentCenter);
	
  // Add it as a child layer to the Window's root layer
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer2));
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer3));
  
  // Make sure the time is displayed from the start
  update_time();
}

static void main_window_unload(Window *window) {
  // Destroy TextLayer
  text_layer_destroy(s_time_layer);
  text_layer_destroy(s_time_layer2);
	text_layer_destroy(s_time_layer3);

}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
}
  
static void init() {
  // Create main Window element and assign to pointer
  s_main_window = window_create();
	
  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  // Show the Window on the watch, with animated=true
  window_stack_push(s_main_window, true);
  
  // Register with TickTimerService
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
}

static void deinit() {
  // Destroy Window
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
	return 0;
}
