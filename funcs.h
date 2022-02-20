void draw_tanks(unsigned const int height, unsigned const int width, int* green_position, int* blue_position);

void controls(unsigned const int map_height, unsigned const int map_width, int* green_position, int* blue_position, bool* green_shot, bool* blue_shot, int* green_x, int* blue_x, int* green_bullets, int* blue_bullets);

void draw(unsigned const int map_height, unsigned const int map_width, int green_position, int blue_position, bool* green_shot, bool* blue_shot, int* green_x, int* blue_x, int bar_lvl, char bar[], int green_score[], int blue_score[], int* green_bullets, int* blue_bullets);

void draw_menu();

int get_map();

void clear_menu();