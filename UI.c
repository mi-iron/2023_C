#pragma once
#include "UI.h"

void start() {
    initscr();

    if (has_colors() == FALSE) {
        puts("Terminal does not support colors!");
        endwin();
        return 1;
    } else {
        start_color();
        init_pair(1, COLOR_BLUE, COLOR_WHITE);
        init_pair(2, COLOR_WHITE, COLOR_BLUE);
    }
    refresh();

    startPage();

    endwin();
    return 0;
}

void startPage() {
    while (true) {
        curs_set(0);
        keypad(stdscr, TRUE);
        noecho();

        WINDOW *win1 = newwin(18, 80, 0, 0);
        WINDOW *win2 = newwin(6, 80, 18, 0);

        wbkgd(win1, COLOR_PAIR(1));
        wbkgd(win2, COLOR_PAIR(2));

        mvwprintw(win1, 6, 38, "Login");
        mvwprintw(win1, 8, 37, "Sign up");

        mvwprintw(win1, 6, 36, ">");

        wrefresh(win1);
        wrefresh(win2);

        wchar_t key;
        int i = 1;
        while (TRUE) {
            key = getch();
            if (key == KEY_DOWN) {
                cursorDOWN();
                i = 2;
            } else if (key == KEY_UP) {
                cursorUP();
                i = 1;
            } else if (key == 27) {
                endwin();
                exit(0);
            } else if (key == 10) {
                if (i == 1) {
                    clear();
                    refresh();
                    loginPage();
                } else if (i == 2) {
                    clear();
                    refresh();
                    signPage();
                }
            }
        }
    }
}

void cursorDOWN() {
    WINDOW *win1 = newwin(18, 80, 0, 0);
    WINDOW *win2 = newwin(6, 80, 18, 0);

    wbkgd(win1, COLOR_PAIR(1));
    wbkgd(win2, COLOR_PAIR(2));

    mvwprintw(win1, 6, 38, "Login");
    mvwprintw(win1, 8, 35, "> Sign up");

    wrefresh(win1);
    wrefresh(win2);
}

void cursorUP() {
    WINDOW *win1 = newwin(18, 80, 0, 0);
    WINDOW *win2 = newwin(6, 80, 18, 0);

    wbkgd(win1, COLOR_PAIR(1));
    wbkgd(win2, COLOR_PAIR(2));

    mvwprintw(win1, 6, 36, "> Login");
    mvwprintw(win1, 8, 37, "Sign up");

    wrefresh(win1);
    wrefresh(win2);
}

void signPage() {

    WINDOW *win1 = newwin(18, 80, 0, 0);
    WINDOW *win2 = newwin(6, 80, 18, 0);

    wbkgd(win1, COLOR_PAIR(1));
    wbkgd(win2, COLOR_PAIR(2));

    int cur_name = 36;
    int cur_ID = 34;
    int cur_PW = 34;

    mvwprintw(win1, 14, 37, "Sign up");
    mvwprintw(win1, 8, 30, "ID: ");   // 34
    mvwprintw(win1, 11, 30, "PW: ");  // 34
    mvwprintw(win1, 5, 30, "Name: "); // 36

    curs_set(1);

    wrefresh(win2);
    wrefresh(win1);

    wchar_t key;
    int i_n = 0;
    int i_i = 0;
    int i_p = 0;
    int cursor = 1;

    char name[10];
    char ID[10];
    char PW[10];

    for (int i = 0; i < MAX_LENGTH; i++) {
        name[i] = '\0';
        ID[i] = '\0';
        PW[i] = '\0';
    }

    while (TRUE) {
        switch (cursor) {
        case 1:
            curs_set(0);
            mvwprintw(win1, 14, 35, " ");
            move(5, cur_name);
            curs_set(1);
            wrefresh(win1);
            break;
        case 2:
            curs_set(0);
            mvwprintw(win1, 14, 35, " ");
            move(8, cur_ID);
            curs_set(1);
            wrefresh(win1);
            break;
        case 3:
            curs_set(0);
            mvwprintw(win1, 14, 35, " ");
            move(11, cur_PW);
            curs_set(1);
            wrefresh(win1);
            break;
        case 4:
            curs_set(0);
            mvwprintw(win1, 14, 35, ">");
            wrefresh(win1);
            break;
        }

        key = getch();
        if (key == KEY_DOWN) {
            cursor = cursor + 1;
            if (cursor >= 4)
                cursor = 4;
        } else if (key == KEY_UP) {
            cursor = cursor - 1;
            if (cursor <= 1)
                cursor = 1;
        } else if ((48 <= key & key <= 57) | (65 <= key & key <= 90) |
                   (97 <= key & key <= 122)) { // 48~57, 65~90, 97~122
            if (cursor == 1 & i_n < 10) {
                name[i_n] = key;
                mvwprintw(win1, 5, cur_name++, "%c", (char)name[i_n]);
                i_n++;
                wrefresh(win1);
            } else if (cursor == 2 & i_i < 10) {
                ID[i_i] = key;
                mvwprintw(win1, 8, cur_ID++, "%c", (char)ID[i_i]);
                i_i++;
                wrefresh(win1);
            } else if (cursor == 3 & i_p < 10) {
                PW[i_p] = key;
                mvwprintw(win1, 11, cur_PW++, "*");
                i_p++;
                wrefresh(win1);
            }
        } else if (key == 27) {
            clear();
            refresh();
            startPage();
        } else if (key == 10 & cursor == 4) {
            if (i_n == 0 | i_i == 0 | i_p == 0) {
                mvwprintw(win2, 0, 27, "Please fill out all blacks");
                wrefresh(win2);
                getch();
                clear();
                refresh();
                signPage();
            } else {
                char pathName[20] = "./";
                strcat(pathName, ID);
                strcat(pathName, ".dat");

                Data *data = (Data *)malloc(sizeof(Data));
                memset(data->name, '\0', 11);
                memset(data->ID, '\0', 11);
                memset(data->PW, '\0', 11);

                strcpy(data->name, name);
                strcpy(data->ID, ID);
                strcpy(data->PW, PW);

                int fd = open(pathName, O_RDONLY);
                if (fd != -1) {
                    mvwprintw(win2, 0, 30, "Already exits ID");
                    wrefresh(win2);
                    getch();
                    clear();
                    refresh();
                    signPage();
                }

                fd = open(pathName, O_CREAT | O_RDWR, 0644);

                int wSize = write(fd, (Data *)data, sizeof(Data));

                close(fd);
                free(data);
                clear();
                refresh();
                loginPage();
            }
        }
    }
}

void loginPage() {

    WINDOW *win1 = newwin(18, 80, 0, 0);
    WINDOW *win2 = newwin(6, 80, 18, 0);

    wbkgd(win1, COLOR_PAIR(1));
    wbkgd(win2, COLOR_PAIR(2));

    int cur_ID = 34;
    int cur_PW = 34;

    mvwprintw(win1, 12, 38, "Login");
    mvwprintw(win1, 9, 30, "PW: "); // 34
    mvwprintw(win1, 6, 30, "ID: "); // 34

    curs_set(1);

    wrefresh(win2);
    wrefresh(win1);

    wchar_t key;
    int i_i = 0;
    int i_p = 0;
    int cursor = 1;

    char ID[10];
    char PW[10];

    for (int i = 0; i < 10; i++) {
        ID[i] = '\0';
        PW[i] = '\0';
    }

    while (TRUE) {
        switch (cursor) {
        case 1:
            curs_set(0);
            mvwprintw(win1, 12, 35, " ");
            move(6, cur_ID);
            curs_set(1);
            wrefresh(win1);
            break;
        case 2:
            curs_set(0);
            mvwprintw(win1, 12, 35, " ");
            move(9, cur_PW);
            curs_set(1);
            wrefresh(win1);
            break;
        case 3:
            curs_set(0);
            mvwprintw(win1, 12, 35, ">");
            wrefresh(win1);
            break;
        }

        key = getch();
        if (key == KEY_DOWN) {
            cursor = cursor + 1;
            if (cursor >= 3)
                cursor = 3;
        } else if (key == KEY_UP) {
            cursor = cursor - 1;
            if (cursor <= 1)
                cursor = 1;
        } else if ((48 <= key & key <= 57) | (65 <= key & key <= 90) |
                   (97 <= key & key <= 122)) { // 48~57, 65~90, 97~122
            if (cursor == 1 & i_i < 10) {
                ID[i_i] = key;
                mvwprintw(win1, 6, cur_ID++, "%c", (char)ID[i_i]);
                i_i++;
                wrefresh(win1);
            } else if (cursor == 2 & i_p < 10) {
                PW[i_p] = key;
                mvwprintw(win1, 9, cur_PW++, "*");
                i_p++;
                wrefresh(win1);
            }
        } else if (key == 27) {
            clear();
            refresh();
            startPage();
        } else if (key == 10 & cursor == 3) {
            char pathName[20] = "./";
            strcat(pathName, ID);
            strcat(pathName, ".dat");

            Data *data = (Data *)malloc(sizeof(Data));
            memset(data->name, '\0', 11);
            memset(data->ID, '\0', 11);
            memset(data->PW, '\0', 11);

            int fd = open(pathName, O_RDONLY);
            if (fd == -1) {
                mvwprintw(win2, 0, 30, "ID doesn't exist");
                wrefresh(win2);
                getch();
                clear();
                refresh();
                loginPage();
            }

            int rSize = read(fd, (Data *)data, sizeof(Data));

            if (strcmp(PW, data->PW) != 0) {
                mvwprintw(win2, 0, 30, "Incorrect Password");
                wrefresh(win2);
                getch();
                close(fd);
                free(data);
                clear();
                refresh();
                loginPage();
            } else if (strcmp(PW, data->PW) == 0) {

                close(fd);
                free(data);

                clear();
                refresh();

                WINDOW *win = newwin(1, 80, 0, 0);
                wbkgd(win, COLOR_PAIR(2));
                mvwprintw(win, 0, 0, "ID: %s", ID);
                wrefresh(win);

                // mainPage(pathName);
                simsimeTalk(ID);
            }
        }
    }
}
