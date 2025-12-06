#include "missing_compass_window.h"
#include "bitmap.h"

typedef struct {
    TextLayer *info_text_layer;
} MissingCompassWindowData;

Window *missing_compass_window_get_window(MissingCompassWindow *window) {
    return (Window *)window;
}

static void missing_compass_window_load(Window *window) {
    MissingCompassWindowData *data = window_get_user_data(window);
    Layer *window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(window_layer);

    const GFont text_font = fonts_get_system_font(PBL_IF_ROUND_ELSE(FONT_KEY_GOTHIC_18_BOLD, FONT_KEY_GOTHIC_24_BOLD));

    data->info_text_layer = text_layer_create(bounds);
    text_layer_set_text(data->info_text_layer, "This watch does not have compass hardware.");
    text_layer_set_text_alignment(data->info_text_layer, GTextAlignmentCenter);
    text_layer_set_font(data->info_text_layer, text_font);
    text_layer_set_text_color(data->info_text_layer, PBL_IF_COLOR_ELSE(GColorLightGray, GColorWhite));
    text_layer_set_background_color(data->info_text_layer, GColorClear);
    GSize text_size = text_layer_get_content_size(data->info_text_layer);
    text_layer_set_size(data->info_text_layer, text_size);
    GRect text_bounds = GRect(0, 0, text_size.w, text_size.h + 10);
    grect_align(&text_bounds, &bounds, GAlignCenter, false);
    layer_set_frame(text_layer_get_layer(data->info_text_layer), text_bounds);
    layer_add_child(window_layer, text_layer_get_layer(data->info_text_layer));
}

static void missing_compass_window_unload(Window *window) {
    MissingCompassWindowData *data = window_get_user_data(window);
    text_layer_destroy(data->info_text_layer);
}

MissingCompassWindow *missing_compass_window_create() {
    Window *window = window_create();
    MissingCompassWindowData *data = malloc(sizeof(MissingCompassWindowData));

    window_set_user_data(window, data);

    window_set_window_handlers(window, (WindowHandlers) {
            .load = missing_compass_window_load,
            .unload = missing_compass_window_unload,
    });
    window_set_background_color(window, GColorBlack);

    return (MissingCompassWindow *) window;
}

void missing_compass_window_destroy(MissingCompassWindow *window) {
    if(!window)return;

    MissingCompassWindowData *data = window_get_user_data((Window *)window);
    free(data);

    window_destroy((Window *)window);
}
