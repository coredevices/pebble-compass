#include "pebble.h"

typedef struct MissingCompassWindow MissingCompassWindow;

Window *missing_compass_window_get_window(MissingCompassWindow *window);

MissingCompassWindow *missing_compass_window_create();
void missing_compass_window_destroy(MissingCompassWindow *window);

