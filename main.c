#define _POSIX_C_SOURCE 200201L
#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include "funcs.h"


int main(){
    srand(time(NULL));
    // initializing curses library
    initscr();

    // setting modes
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(FALSE);
    nodelay(stdscr, TRUE);

    // variables
    int map_height, map_width, bar_lvl;
    int green_position, blue_position;
    int green_score[1] = {0}, blue_score[1] = {0};
    bool green_shot = false, blue_shot = false;
    int green_x = map_height - 5, blue_x = 4;
    int green_bullets = 5, blue_bullets = 5;
    
    // calling func for drawing intro menu
    draw_menu();
    int map_num ;
    do{
        map_num = get_map();
    }while(map_num > 6 || map_num == 0);

    
    // clearing menu
    clear_menu();

    // concanetating returned int and string (path to a file)
    char map_file[14];
    snprintf(map_file, 14, "maps/map_%d", map_num);

    // getting informations from file 
    FILE *fp = NULL;
    fp = fopen(map_file, "r");

        if(fp == NULL){
            perror("Error opening file");
           return EXIT_FAILURE;
        }

        fscanf(fp, "%d %d %d", &map_width, &map_height, &bar_lvl);
        char bar[map_width - 2];
        fscanf(fp, "%s", bar);

    fclose(fp);


    draw_tanks(map_height, map_width, &green_position, &blue_position);
    

    while(green_bullets > 0 || blue_bullets > 0){
        controls(map_height, map_width, &green_position, &blue_position, &green_shot, &blue_shot, &green_x, &blue_x, &green_bullets, &blue_bullets);
     
        draw(map_height, map_width, green_position, blue_position, &green_shot, &blue_shot, &green_x, &blue_x, bar_lvl, bar, green_score, blue_score, &green_bullets, &blue_bullets);
    }
    draw(map_height, map_width, green_position, blue_position, &green_shot, &blue_shot, &green_x, &blue_x, bar_lvl, bar, green_score, blue_score, &green_bullets, &blue_bullets);


    if(green_score[0] > blue_score[0]){
        mvprintw(map_height / 2, map_width / 2 - 8, "Green player won !");
    }
    else if(green_score[0] < blue_score[0]){
        mvprintw(map_height / 2, map_width / 2 - 8, "Blue player won !");
    }
    else if (green_score[0] == blue_score[0]){
        mvprintw(map_height / 2, map_width / 2 - 4, "Game tied");
    }
    mvprintw(map_height / 2, map_width / 2 - 8, "Press Q to quit");
        refresh();

    
    bool end = false;

    while(!end){
        int quit = getch();
        switch(quit){
                case 'q' : case 'Q' : {
                    end = true;
                    break;
                }
        }
    }

    // closing curses library
    endwin();


    return EXIT_SUCCESS;
}
