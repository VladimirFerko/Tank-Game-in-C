#define _POSIX_C_SOURCE 200201L
#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "funcs.h"

// procedure for printing tanks onto the screen

void draw_tanks(unsigned const int height, unsigned const int width, int* green_position, int* blue_position){

    int random_position = (rand() % (width - 7) + 3);


    *blue_position = random_position;
    
    random_position = (rand() % (width - 7) + 3);

    *green_position = random_position;

}

// procedure for handling controls of the tanks
void controls(unsigned const int map_height, unsigned const int map_width, int* green_position, int* blue_position, bool* green_shot, bool* blue_shot, int* green_x, int* blue_x, int* green_bullets, int* blue_bullets){
    int key = getch();

    switch(key){
        case 'd' : case 'D' : {
            if(*blue_position < map_width - 5){
                if(!*green_shot && !*blue_shot){
                    *blue_position += 1;
                }
            }

            break;
        }
        case 'a' : case 'A' : {
            if (*blue_position > 0){
                if(!*green_shot && !*blue_shot){
                    *blue_position -= 1;
                }
            }
            break;
        }
        case KEY_LEFT: {
            if (*green_position > 0){
                if(!*green_shot && !*blue_shot){
                    *green_position -= 1;
                }
            }
            break;
        }
        case KEY_RIGHT: {
            if (*green_position < map_width - 5){
                if(!*green_shot && !*blue_shot){
                    *green_position += 1;
                }
            }
            break;
        }
        case KEY_UP: {
            if(*green_bullets > 0){
                if(!*blue_shot || !*green_shot){
                    *green_x = map_height - 5;
                    *green_shot = true;
                }
            }
            break;
        }
        case 's' : case 'S' : {
            if(*blue_bullets > 0){
                if (!*blue_shot || !*green_shot){
                    *blue_x = 4;
                    *blue_shot = true;
                }
            }
            break;
        }
    }
}

void draw(unsigned const int map_height, unsigned const int map_width, int green_position, int blue_position, bool* green_shot, bool* blue_shot, int* green_x, int* blue_x, int bar_lvl, char bar[], int green_score[], int blue_score[], int* green_bullets, int* blue_bullets){

    struct timespec ts = {
        .tv_sec = 0,                    // nr of secs
        .tv_nsec = 0.001 * 10000000000L  // nr of nanosecs
    };

    start_color();
    init_pair(1,COLOR_GREEN, COLOR_BLACK);
    init_pair(2,COLOR_CYAN, COLOR_BLACK);
    
    // priting map from the map arr onto the screen
    for(int index_h = 0; index_h < map_height; index_h++){
        for(int index_w = 0; index_w < map_width; index_w++){
            if(index_h == 0 || index_h == map_height - 1){
                if(index_w == 0 || index_w == map_width - 1){
                    mvprintw(index_h, index_w, "+");
                }
                else{
                    mvprintw(index_h, index_w, "-");
                }
                refresh();
            }
            else if(index_w == 0 || index_w == map_width - 1){
                mvprintw(index_h, index_w, "|");
            }
        }
    }

    // printing obstacle
    for(int i = 0; i < map_width - 2; i++){
        if(bar[i] == '|'){
            mvprintw(bar_lvl, i + 1, " ");
        }
        else{
            mvprintw(bar_lvl, i + 1, "%c", bar[i]);\
        }
    }
//    mvprintw(60,30, *bar);
   
    // printing upper blue tank 
    attron(COLOR_PAIR(2));
    if(blue_position == map_width - 5){
        mvprintw(2, blue_position, " ###");
        mvprintw(3, blue_position + 1, " | ");
    }
    else{
        mvprintw(2, blue_position, " ### ");
        mvprintw(3, blue_position + 1, " | ");
    }
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(1));
    // printing lower green tank 
    if(green_position == map_width - 5){
        mvprintw(map_height - 4, green_position + 1, " | ");
        mvprintw(map_height - 3, green_position, " ###");
        
    }
    else{
        mvprintw(map_height - 4, green_position + 1, " | ");
        mvprintw(map_height - 3, green_position, " ### ");
        
    }
    attroff(COLOR_PAIR(1));

    // printing bullets
    if(*green_shot){
        *green_bullets -= 1;
        if(bar[green_position + 1] == '-'){
            bar[green_position + 1] = '|';
            for(int i = 0; i < bar_lvl - 5; i++){
                mvprintw(*green_x, green_position + 2, " ");
                *green_x -= 1;
                mvprintw(*green_x, green_position + 2, "o");
                refresh();
                nanosleep(&ts, NULL);
            }
        }
        else{
            for(int i = 0; i < map_height - 6; i++){
                mvprintw(*green_x, green_position + 2, " ");
                *green_x -= 1;
                mvprintw(*green_x, green_position + 2, "o");
                refresh();
                nanosleep(&ts, NULL);
            }

        // adding score
        if(green_position + 2 == blue_position + 2 || green_position + 2 == blue_position + 1 ||  green_position + 2 == blue_position + 3 ){
            green_score[0] += 1;
            }
        }

            *green_shot = false;
    }

    if(*blue_shot){
        *blue_bullets -= 1;
        if(bar[blue_position + 1] == '-'){
            bar[blue_position + 1] = '|';
            for(int i = 0; i < bar_lvl - 4; i++){
                mvprintw(*blue_x, blue_position + 2, " ");
                *blue_x += 1;
                mvprintw(*blue_x, blue_position + 2, "o");
                refresh();
                nanosleep(&ts, NULL);
            }
        }
        else{
            for(int i = 0; i < map_height - 6; i++){
                mvprintw(*blue_x, blue_position + 2, " ");
                *blue_x += 1;
                mvprintw(*blue_x, blue_position + 2, "o");
                refresh();
                nanosleep(&ts, NULL);
            }
        // adding score
        if(blue_position + 2 == green_position + 2 || blue_position + 2 == green_position + 3 || blue_position + 2 == green_position + 1){
            blue_score[0] += 1;
            }
        }

        


        *blue_shot = false;
    }

    // printing score onto the screen   
    mvprintw(map_height - 4, map_width + 3, "Green : %d", green_score[0]);
    mvprintw(4, map_width + 3, "Blue : %d", blue_score[0]);

    // printing available bullets
    mvprintw(map_height - 1, map_width + 3, "BULLETS : %d", *green_bullets);
    mvprintw(1, map_width + 3, "BULLETS : %d", *blue_bullets);


}


// drawing menu, also returns the players map choice

void draw_menu(){
    
    // drawing the intro frame

    for(size_t j = 0; j < 20; j++){
        for (size_t i = 0; i < 40; i++){ // for for width
            if(j == 0 || j == 19){
                if(i == 0 || i == 39){
                    mvprintw(j + 1, 15 + i - 3, "+");
                }
                else{
                    mvprintw(j + 1, 15 + i - 3, "-");
                }
            }
            else if(i == 0 || i == 39){
                mvprintw(j + 1, 15 + i - 3, "|");
            }
        }
    }
    
    // intro text
    mvprintw(3, 20, "WELCOME TO THE TANK GAME");
    mvprintw(8, 20, " Which map do you want ?");
    mvprintw(10, 29, "(1 - 5)");
    
    refresh();
    getchar();
    
}

int get_map(){
    int map = getch();

    switch (map){
        case '1': { 
            return 1;
            break;
        }
        case '2': { 
            return 2;
            break;
        }
        case '3': { 
            return 3;
            break;
        }
        case '4': { 
            return 4;
            break;
        }
        case '5': { 
            return 5;
            break;
        }
        case '6': case '7': case '8': case '9': case '0':{
            mvprintw(15, 22, "This map doesn't exist"); 
            return 0;
            break;
        }
    }
    return 0;
}

// function for clearing menu
void clear_menu(){
    for(size_t j = 0; j < 20; j++){
        for (size_t i = 0; i < 40; i++){ // for for width
             mvprintw(j + 1, 15 + i - 3, " ");
        }
    }
    refresh();     
}