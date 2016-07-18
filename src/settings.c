#include <pebble.h>

Window *window;

//This is called from the data_framework_inbox function
void process_tuple(Tuple *t){
    //It gets the key and the value
    uint32_t key = t->key;
    int value = t->value->int32;

    //It checks if the key is equal to the boolean box message key
    if(key == MESSAGE_KEY_boolean_box){
        //If it is, it does this magic
        APP_LOG(APP_LOG_LEVEL_DEBUG, "Got value %d for boolean", value);
    }
    //Same with this one
    else if(key == MESSAGE_KEY_color_picker){
        APP_LOG(APP_LOG_LEVEL_INFO, "Got a value %s for colour picker", t->value->cstring);
    }
}

/*
Note:
Message keys in the package.json/settings (in CloudPebble) can be used in C by appending
MESSAGE_KEY_ before your message key name.
*/

//This inbox gets the messages directly from the phone with its DictionaryIterator
void message_inbox(DictionaryIterator *iter, void *context){
    //It reads the first item in the dictionary
    Tuple *t = dict_read_first(iter);
    //Makes sure it's legit
    if(t){
        //If it is, it processes it
        process_tuple(t);
    }
    //While the keys keep coming (are not null)
    while(t != NULL){
        //Read them
        t = dict_read_next(iter);
        if(t){
            //Process them if they exist
            process_tuple(t);
        }
    }
}

//This is called when the message is dropped and doesn't go through
void message_inbox_dropped(AppMessageResult reason, void *context){
    //It prints the reason
    APP_LOG(APP_LOG_LEVEL_INFO, "Message dropped, reason %d.", reason);
}

//Called when the window loads
void window_load(Window *window){
    app_message_register_inbox_received(message_inbox);
    app_message_register_inbox_dropped(message_inbox_dropped);
    app_message_open(512, 512);
}

//Called when the window unloads
void window_unload(Window *window){

}

//Initializes the app
void init(){
    window = window_create();
    window_set_window_handlers(window, (WindowHandlers) {
        .load = window_load,
        .unload = window_unload
    });
    window_stack_push(window, true);
}

//Deinitializes the app
void deinit(){
    window_destroy(window);
}

//The main function, seen in every C program
int main(){
    init();
    app_event_loop();
    deinit();
}
