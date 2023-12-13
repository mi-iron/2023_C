#pragma once
#include "Play.h"

void mainPage(char *pathName) {

    WINDOW *win1 = newwin(4, 80, 0, 0);
    WINDOW *win2 = newwin(18, 80, 3, 0);
    WINDOW *win3 = newwin(2, 80, 21, 0);

    wbkgd(win1, COLOR_PAIR(2));
    wbkgd(win2, COLOR_PAIR(1));
    wbkgd(win3, COLOR_PAIR(2));

    Data *data = (Data *)malloc(sizeof(Data));
    memset(data->name, '\0', 11);
    memset(data->ID, '\0', 11);
    memset(data->PW, '\0', 11);

    mvwprintw(win3, 0, 0, "%s", *pathName);
    wrefresh(win3);
    getch();

    int fd = open(pathName, O_RDONLY);
    if (fd == -1) {
        mvwprintw(win3, 0, 30, "ID doesn't exist");
        wrefresh(win3);
    }

    int rSize = read(fd, (Data *)data, sizeof(Data));

    char ID = data->ID;

    wrefresh(win3);
    wrefresh(win2);
    wrefresh(win1);

    close(fd);
    free(data);

    simsimeTalk(ID);
}

void simsimeTalk(char ID) {
    WINDOW *win1 = newwin(3, 80, 1, 0);
    WINDOW *win2 = newwin(18, 80, 4, 0);
    WINDOW *win3 = newwin(2, 80, 21, 0);

    wbkgd(win1, COLOR_PAIR(2));
    wbkgd(win2, COLOR_PAIR(1));
    wbkgd(win3, COLOR_PAIR(2));

    wrefresh(win1);
    wrefresh(win2);
    wrefresh(win3);

    FILE *file = fopen("qnadata.txt", "ra");

    if (file == NULL) {
        mvwprintw(win1, 0, 1, "Can't open file");
        wrefresh(win1);
        mvwprintw(win1, 1, 1, "Program end");
        wrefresh(win1);
        return;
    }

    mvwprintw(win1, 0, 1, "Loading...");
    wrefresh(win1);
    sleep(2);
    mvwprintw(win1, 1, 1, "SimSim has been loaded! Try texting");
    mvwprintw(win1, 2, 1, "If you want to finish the program type \"end\"");
    wrefresh(win1);

    mvwprintw(win3, 0, 0, "> ");
    wrefresh(win3);

    char line[MAX_LENGTH];
    char userInput[MAX_LENGTH];

    for (int i = 0; i < MAX_LENGTH; i++) {
        line[i] = '\0';
        userInput[i] = '\0';
    }

    // mvwprintw(win2, 0, 0, "0000000000");
    // wrefresh(win2);

    wchar_t key;
    int i = 0;
    int cursor = 2;
    int win2_line = 0;

    while (1) {
        move(21, cursor);
        curs_set(1);
        key = getch();

        if ((32 <= key & key <= 33) | key == 63 | key == 126 |
            (48 <= key & key <= 57) | (65 <= key & key <= 90) |
            (97 <= key & key <= 122)) {
            // 32 = space, 33 = !, 63 = ?, 126 = ~, 48~57, 65~90, 97~122
            userInput[i] = key;
            mvwprintw(win3, 0, cursor++, "%c", (char)userInput[i]);
            i++;
            wrefresh(win3);
        } else if (key == 10) {
            if (userInput[0] == NULL) {
                continue;
            }
            wclear(win3);
            mvwprintw(win3, 0, 0, ">");
            cursor = 2;
            wrefresh(win3);

            mvwprintw(win2, win2_line++, 0, "<< %s", userInput);
            wrefresh(win2);

            userInput[strcspn(userInput, "\n")] = '\0'; // 공백 개행 제거
            userInput[strcspn(userInput, " ")] = '\0';
            if (strcmp(userInput, "end") == 0) {
                fclose(file);
                return;
            }

            int lineNumber = 1;
            int Found = 0;
            while (fgets(line, MAX_LENGTH, file) != NULL) {
                if (lineNumber % 2 != 0) { // 홀수
                    // printf("확인 2 %s\n", line); //인코딩 문제인지
                    // txt에서 한국어 읽어올때마다 에러남. 일단 영어로 대체
                    line[strcspn(line, "\n")] = '\0';
                    line[strcspn(line, " ")] = '\0';
                    if (strcmp(line, userInput) == 0) {

                        // 사용자 입력과 일치하는지 확인
                        if (fgets(line, MAX_LENGTH, file) != NULL) { // 다음 줄
                            mvwprintw(win2, win2_line++, 0, ">>");
                            wrefresh(win2);

                            for (int j = 0; j < MAX_LENGTH; j++) {
                                if (line[j] == NULL)
                                    break;
                                mvwprintw(win2, win2_line - 1, j + 3, "%c",
                                          line[j]);
                                wrefresh(win2);
                            }
                            Found = 1;
                            i = 0;
                            break;
                        }
                    }
                }
                lineNumber++;
            }

            if (!Found) {
                mvwprintw(win2, win2_line++, 0,
                          ">> I don\'t know what you say, Please write QnA in "
                          "text page");
                wrefresh(win2);
                i = 0;
            }

            if (win2_line >= 16) {
                curs_set(0);
                getch();
                wclear(win2);
                wrefresh(win2);

                mvwprintw(win3, 0, 0, ">");
                wrefresh(win3);
                win2_line = 0;
            }
            rewind(file); // 파일포인터 초기화, 갱신
            // userInput initialize
            for (int k = 0; k < MAX_LENGTH; k++) {
                line[k] = '\0';
                userInput[k] = '\0';
            }
        }
    }
}
