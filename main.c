#include <time.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

void Rock(int start_row, int start_col) {
    char *ascii_art[] = {
        "    _______",
        "---'   ____)",
        "      (_____)",
        "      (_____)",
        "      (____)",
        "---.__(___)"
    };

    int num_lines = sizeof(ascii_art) / sizeof(ascii_art[0]);

    for (int i = 0; i < num_lines; i++) {
        mvprintw(start_row + i, start_col, "%s", ascii_art[i]);
    }
}

void Scissors(int start_row, int start_col) {
    char *ascii_art[] = {
        "    _______",
        "---'   ____)____",
        "          ______)",
        "       __________)",
        "      (____)",
        "---.__(___)"
    };

    int num_lines = sizeof(ascii_art) / sizeof(ascii_art[0]);

    for (int i = 0; i < num_lines; i++) {
        mvprintw(start_row + i, start_col, "%s", ascii_art[i]);
    }
}

void Paper(int start_row, int start_col) {
    char *ascii_art[] = {
        "     _______",
        "---'    ____)____",
        "           ______)",
        "          _______)",
        "         _______)",
        "---.__________)"
    };

    int num_lines = sizeof(ascii_art) / sizeof(ascii_art[0]);

    for (int i = 0; i < num_lines; i++) {
        mvprintw(start_row + i, start_col, "%s", ascii_art[i]);
    }
}

void draw_menu(int selected) {
    clear();
    printw("cy-e-fa by 4o4.\n\n\n");
    printw("Use arrows to choose and Enter to confirm:\n\n");
    
    if (selected == 0) {
        attron(A_REVERSE);
        printw("> Rock <\n");
        attroff(A_REVERSE);
    } else {
        printw("  Rock  \n");
    }
    
    if (selected == 1) {
        attron(A_REVERSE);
        printw("> Scissors <\n");
        attroff(A_REVERSE);
    } else {
        printw("  Scissors  \n");
    }
    
    if (selected == 2) {
        attron(A_REVERSE);
        printw("> Paper <\n");
        attroff(A_REVERSE);
    } else {
        printw("  Paper  \n");
    }
    
    printw("\nPress ENTER to confirm your choice");
    refresh();
}

int main(int argc, char **argv) {
    initscr();
    srand(time(NULL));
    
    curs_set(0);
    keypad(stdscr, TRUE); 
    noecho();
    
    int hum_choice = 0;
    int comp_choice;
    int ch;
    
    draw_menu(hum_choice);
    
    while ((ch = getch()) != '\n' && ch != KEY_ENTER) {
        switch (ch) {
            case KEY_UP:
                hum_choice = (hum_choice - 1 + 3) % 3;
                break;
            case KEY_DOWN:
                hum_choice = (hum_choice + 1) % 3;
                break;
        }
        draw_menu(hum_choice);
    }
    
    clear();

    if (hum_choice == 0) {
        printw("You have chosen a rock!\n");
        Rock(2, 0);
    } else if (hum_choice == 1) {
        printw("You have chosen scissors!\n");
        Scissors(2, 0);
    } else if (hum_choice == 2) {
        printw("You have chosen paper!\n");
		Paper(2, 0);
    }

    refresh();
    napms(1000);

    comp_choice = rand() % 3;

    if (comp_choice == 0) {
        printw("\n\nComputer choised Rock!\n");
        Rock(10, 0);
    } else if (comp_choice == 1) {
        printw("\n\nComputer choise Scissors!\n");
        Scissors(10, 0);
    } else if (comp_choice == 2) {
        printw("\n\nComputer choised Paper!\n");
        Paper(10, 0);
    }

    refresh();
    napms(1000);

    if (hum_choice == comp_choice) {
        printw("\n\nDraw!\n");
    } else if ((hum_choice == 0 && comp_choice == 1) ||
              (hum_choice == 1 && comp_choice == 2) ||
              (hum_choice == 2 && comp_choice == 0)) {
        printw("\n\nYou won!\n");
    } else {
        printw("\n\nThe computer won!\n");
    }

    refresh();
    printw("\n\nPlease, press any key to exit. . .");
    getch();

    endwin();
    return 0;
}
