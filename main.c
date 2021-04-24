#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>
#include <libgen.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/time.h>

char *module;
int X = 0, Y = 0;
pid_t pid0 = 0, pid1 = 0, pid2 = 0, pid3 = 0, pid4 = 0, pid5 = 0, pid6 = 0, pid7 = 0, pid8 = 0, group_pid = 0;

void printErr(const char *module, const char *errmsg, const char *filename) {
    fprintf(stderr, "%d %s: %s %s\n", getpid(), module, errmsg, filename ? filename : "");
}

long getTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_usec) % 1000;
}

void debug() {
    printf("PID^ %d", getpid());
    printf("\n%d %d", 1, pid1);
    printf("\n%d %d", 2, pid2);
    printf("\n%d %d", 3, pid3);
    printf("\n%d %d", 4, pid4);
    printf("\n%d %d", 5, pid5);
    printf("\n%d %d", 6, pid6);
    printf("\n%d %d", 7, pid7);
    printf("\n%d %d", 8, pid8);
}

void handler1() {
    static int recieved = 0;
    recieved++;

    printf("1 %d %d получил USR1 %ld\n", getpid(), getppid(), getTime());

    if (recieved == 101) {
        //sleep(5);

        char buffer[256];
        sprintf(buffer, "pstree -p %d", getppid());
        system(buffer);


        if (kill(-pid7, SIGTERM) == -1)
            printErr(module, strerror(errno), NULL);
        int children = 1;
        while (children--)
            wait(NULL);
        printf("%d %d завершил работу после %d-го сигнала SIGUSR1 и %d-го сигнала SIGUSR2\n", getpid(), getppid(), X,
               Y);
        exit(0);
    } else {
        if (kill(-pid7, SIGUSR1) == -1) {
            printErr(module, strerror(errno), NULL);
        } else {
            printf("1 %d %d послал USR1 %ld\n", getpid(), getppid(), getTime());
        }
        //printf("1 %d %d послал USR1 %ld\n", getpid(), getppid(), getTime());
        X++;

    }
}

void handler2() {
    printf("2 %d %d получил USR2 %ld\n", getpid(), getppid(), getTime());
    if (kill(pid1, SIGUSR2) == -1)
        printErr(module, strerror(errno), NULL);
    else
        printf("2 %d %d послал USR2 %ld\n", getpid(), getppid(), getTime());
    Y++;
}

void handler3() {
    printf("3 %d %d получил USR2 %ld\n", getpid(), getppid(), getTime());
//    if (kill(pid6, SIGUSR1) == -1)
//        printErr(module, strerror(errno), NULL);
//    else
//        printf("3 %d %d послал USR1 %ld\n", getpid(), getppid(), getTime());
//    X++;
}

void handler4() {
    printf("4 %d %d получил USR2 %ld\n", getpid(), getppid(), getTime());
//    if (kill(pid5, SIGUSR1) == -1)
//        printErr(module, strerror(errno), NULL);
//    else
//        printf("4 %d %d послал USR1 %ld\n", getpid(), getppid(), getTime());
//    X++;
}

void handler5() {
    printf("5 %d %d получил USR1 %ld\n", getpid(), getppid(), getTime());
    if (kill(-pid2, SIGUSR2) == -1)
        printErr(module, strerror(errno), NULL);
    else
        printf("5 %d %d послал USR3 %ld\n", getpid(), getppid(), getTime());
    Y++;
}

void handler6() {
    printf("6 %d %d получил USR1 %ld\n", getpid(), getppid(), getTime());
//    if (kill(pid7, SIGUSR1) == -1)
//        printErr(module, strerror(errno), NULL);
//    else
//        printf("6 %d %d послал USR1 %ld\n", getpid(), getppid(), getTime());
//    X++;
}

void handler7() {
    printf("7 %d %d получил USR1 %ld\n", getpid(), getppid(), getTime());
//    if (kill(pid8, SIGUSR1) == -1)
//        printErr(module, strerror(errno), NULL);
//    else
//        printf("7 %d %d послал USR1 %ld\n", getpid(), getppid(), getTime());
//    X++;
}

void handler8() {
    printf("8 %d %d получил USR1 %ld\n", getpid(), getppid(), getTime());
    if (kill(-pid5, SIGUSR1) == -1)
        printErr(module, strerror(errno), NULL);
    else
        printf("8 %d %d послал USR1 %ld\n", getpid(), getppid(), getTime());
    X++;
}

void handlerTerm2() {
    if (kill(pid1, SIGTERM) == -1)
        printErr(module, strerror(errno), NULL);
    int children = 1;
    while (children--)
        wait(NULL);
    printf("%d %d завершил работу после %d-го сигнала SIGUSR1 и %d-го сигнала SIGUSR2\n", getpid(), getppid(), X, Y);
    exit(0);
}

void handlerTerm3() {
//    if (kill(pid6, SIGTERM) == -1)
//        printErr(module, strerror(errno), NULL);
//    int children = 1;
//    while(children--)
//        wait(NULL);
    printf("%d %d завершил работу после %d-го сигнала SIGUSR1 и %d-го сигнала SIGUSR2\n", getpid(), getppid(), X, Y);
    exit(0);
}

void handlerTerm4() {
//    if (kill(pid5, SIGTERM) == -1)
//        printErr(module, strerror(errno), NULL);
//    int children = 1;
//    while(children--)
//        wait(NULL);
    printf("%d %d завершил работу после %d-го сигнала SIGUSR1 и %d-го сигнала SIGUSR2\n", getpid(), getppid(), X, Y);
    exit(0);
}

void handlerTerm5() {
    if (kill(-pid2, SIGTERM) == -1)
        printErr(module, strerror(errno), NULL);
    int children = 3;
    while (children--)
        wait(NULL);
    printf("%d %d завершил работу после %d-го сигнала SIGUSR1 и %d-го сигнала SIGUSR2\n", getpid(), getppid(), X, Y);
    exit(0);
}

void handlerTerm6() {
//    if (kill(pid7, SIGTERM) == -1)
//        printErr(module, strerror(errno), NULL);
//    int children = 1;
//    while (children--)
//        wait(NULL);
    printf("%d %d завершил работу после %d-го сигнала SIGUSR1 и %d-го сигнала SIGUSR2\n", getpid(), getppid(), X, Y);
    exit(0);
}

void handlerTerm7() {
//    if (kill(pid8, SIGTERM) == -1)
//        printErr(module, strerror(errno), NULL);
//    int children = 1;
//    while (children--)
//        wait(NULL);
    printf("%d %d завершил работу после %d-го сигнала SIGUSR1 и %d-го сигнала SIGUSR2\n", getpid(), getppid(), X, Y);
    exit(0);
}

void handlerTerm8() {
    //  потому что последний
    printf("%d %d завершил работу после %d-го сигнала SIGUSR1 и %d-го сигнала SIGUSR2\n", getpid(), getppid(), X, Y);
    exit(0);
}

void createFile(char N) {
    char *filename = (char *) malloc(16);
    sprintf(filename, "/tmp/lab4/%c.pid", N);
    FILE *f = NULL;
    f = fopen(filename, "w");
    if (f == NULL) {
        printErr(module, strerror(errno), filename);
        return;
    }
    fprintf(f, "%d", getpid());
    fclose(f);

    free(filename);
}

pid_t getPidFromFile(char N) {
    char *filename = (char *) malloc(16);
    sprintf(filename, "/tmp/lab4/%c.pid", N);
    pid_t result = 0;

    while (result == 0) {
        FILE *f = NULL;
        while ((f = fopen(filename, "r")) == NULL);
        fscanf(f, "%d", &result);
        fclose(f);
    }

    free(filename);
    return result;
}

void makeTree() {
    pid0 = getpid();

    pid1 = fork();

    if (!pid1) {
        pid1 = getpid();
        pid2 = fork();
        if (!pid2)
            pid2 = getpid();
        else if (pid2 < 0)
            printErr(module, strerror(errno), NULL);
    } else if (pid1 < 0)
        printErr(module, strerror(errno), NULL);


    if (getpid() == pid2) {
        pid3 = fork();
        if (!pid3)
            pid3 = getpid();
        else if (pid3 < 0)
            printErr(module, strerror(errno), NULL);
    }


    if (getpid() == pid3) {
        pid4 = fork();
        if (!pid4)
            pid4 = getpid();
        else if (pid4 < 0)
            printErr(module, strerror(errno), NULL);
    }

    if (getpid() == pid3) {
        pid5 = fork();
        if (!pid5)
            pid5 = getpid();
        else if (pid5 < 0)
            printErr(module, strerror(errno), NULL);
    }

    if (getpid() == pid3) {
        pid6 = fork();
        if (!pid6)
            pid6 = getpid();
        else if (pid6 < 0)
            printErr(module, strerror(errno), NULL);
    }

    if (getpid() == pid4) {
        pid7 = fork();
        if (!pid7) {
            pid7 = getpid();
        }
        else if (pid7 < 0)
            printErr(module, strerror(errno), NULL);
    }

    if (getpid() == pid6) {
        pid8 = fork();
        if (!pid8)
            pid8 = getpid();
        else if (pid8 < 0)
            printErr(module, strerror(errno), NULL);
    }
}


void exchangeSignals(const char *dirname) {
    struct sigaction sg;
    sigemptyset(&sg.sa_mask);
    sg.sa_flags = SA_SIGINFO;

    struct sigaction sgTerm;
    sigemptyset(&sgTerm.sa_mask);
    sgTerm.sa_flags = SA_SIGINFO;


    if (getpid() == pid1) {
        createFile('1');

        const int required = 8;
        int curr = 0;
        //todo ?????????????????????
        while (curr != required) {
            curr = 0;
            DIR *currdir;
            if (!(currdir = opendir(dirname))) {
                printErr(module, strerror(errno), dirname);
                exit(1);
            }

            struct dirent *cdirent;
            errno = 0;

            while ((cdirent = readdir(currdir))) {
                if (!strcmp(".", cdirent->d_name) || !strcmp("..", cdirent->d_name)) {
                    continue;
                }
                curr++;
            }
            if (errno)
                printErr(module, strerror(errno), dirname);
            if (closedir(currdir) == -1)
                printErr(module, strerror(errno), dirname);
        }
        pid7 = getPidFromFile('7');
        pid8 = getPidFromFile('8');

        if (kill(-pid7, SIGUSR1) == -1)
            printErr(module, strerror(errno), NULL);
        else
            printf("1 %d %d послал USR1 %ld\n", getpid(), getppid(), getTime());
        X++;
        //pid2 = getPidFromFile('2');
    }

//    debug();
    if (getpid() == pid2) {
        printf("TUT");
        sg.sa_sigaction = handler2;
        if (sigaction(SIGUSR1, &sg, NULL) == -1) {
            printErr(module, strerror(errno), NULL);
            exit(1);
        }
        sgTerm.sa_sigaction = handlerTerm2;
        if (sigaction(SIGTERM, &sgTerm, NULL) == -1) {
            printErr(module, strerror(errno), NULL);
            exit(1);
        }
        if (setpgid(pid2, pid2) == -1) {
            printErr(module, strerror(errno), NULL);
            exit(1);
        }
        createFile('2');
    }

    if (getpid() == pid3) {
        sg.sa_sigaction = handler3;
        if (sigaction(SIGUSR2, &sg, NULL) == -1) {
            printErr(module, strerror(errno), NULL);
            exit(1);
        }
        sgTerm.sa_sigaction = handlerTerm3;
        if (sigaction(SIGTERM, &sgTerm, NULL) == -1) {
            printErr(module, strerror(errno), NULL);
            exit(1);
        }
        if (setpgid(pid3, pid2) == -1) {
            printErr(module, strerror(errno), NULL);
            exit(1);
        }
        createFile('3');
    }

    if (getpid() == pid4) {
        sg.sa_sigaction = handler4;
        if (sigaction(SIGUSR2, &sg, NULL) == -1) {
            printErr(module, strerror(errno), NULL);
            exit(1);
        }
        sgTerm.sa_sigaction = handlerTerm4;
        if (sigaction(SIGTERM, &sgTerm, NULL) == -1) {
            printErr(module, strerror(errno), NULL);
            exit(1);
        }

        if (setpgid(pid4, pid2) == -1) {
            printErr(module, strerror(errno), NULL);
            exit(1);
        }
//        pid5 = getPidFromFile('5');
        createFile('4');
    }

    if (getpid() == pid5) {
        sg.sa_sigaction = handler5;
        if (sigaction(SIGUSR1, &sg, NULL) == -1) {
            printErr(module, strerror(errno), NULL);
            exit(1);
        }
        sgTerm.sa_sigaction = handlerTerm5;
        if (sigaction(SIGTERM, &sgTerm, NULL) == -1) {
            printErr(module, strerror(errno), NULL);
            exit(1);
        }
        pid4 = getPidFromFile('4');

        if (setpgid(pid5, pid5) == -1) {
            printErr(module, strerror(errno), NULL);
            exit(1);
        }
        createFile('5');
    }

    //todo
    if (getpid() == pid6) {
        sg.sa_sigaction = handler6;
        if (sigaction(SIGUSR1, &sg, NULL) == -1) {
            printErr(module, strerror(errno), NULL);
            exit(1);
        }
        sgTerm.sa_sigaction = handlerTerm6;
        if (sigaction(SIGTERM, &sgTerm, NULL) == -1) {
            printErr(module, strerror(errno), NULL);
            exit(1);
        }
        pid6 = getPidFromFile('6');
        if (setpgid(pid6, pid5) == -1) {
            printErr(module, strerror(errno), NULL);
            exit(1);
        }
        createFile('6');
    }

    if (getpid() == pid7) {
        sg.sa_sigaction = handler7;
        if (sigaction(SIGUSR1, &sg, NULL) == -1) {
            printErr(module, strerror(errno), NULL);
            exit(1);
        }
        sgTerm.sa_sigaction = handlerTerm7;
        if (sigaction(SIGTERM, &sgTerm, NULL) == -1) {
            printErr(module, strerror(errno), NULL);
            exit(1);
        }
        if (setpgid(pid7, pid7) == -1) {
            printErr(module, strerror(errno), NULL);
            exit(1);
        }
        createFile('7');
    }

    if (getpid() == pid8) {
        sg.sa_sigaction = handler8;
        if (sigaction(SIGUSR1, &sg, NULL) == -1) {
            printErr(module, strerror(errno), NULL);
            exit(1);
        }
        sgTerm.sa_sigaction = handlerTerm8;
        if (sigaction(SIGTERM, &sgTerm, NULL) == -1) {
            printErr(module, strerror(errno), NULL);
            exit(1);
        }
        pid7 = getPidFromFile('7');
        if (setpgid(pid8, pid7) == -1) {
            printErr(module, strerror(errno), NULL);
            exit(1);
        }
        pid5 = getPidFromFile('5');
        createFile('8');
    }

    if (getpid() == pid0) {
        wait(NULL);

        DIR *currdir;
        if (!(currdir = opendir(dirname))) {
            printErr(module, strerror(errno), dirname);
            exit(1);
        }

        struct dirent *cdirent;
        errno = 0;

        while ((cdirent = readdir(currdir))) {
            if (!strcmp(".", cdirent->d_name) || !strcmp("..", cdirent->d_name)) {
                continue;
            }
            char *filename = (char *) malloc(strlen(dirname) + 7);
            sprintf(filename, "%s/%s", dirname, cdirent->d_name);
            if (remove(filename) == -1) printErr(module, strerror(errno), filename);
            free(filename);
        }
        if (errno)
            printErr(module, strerror(errno), dirname);
        if (closedir(currdir) == -1)
            printErr(module, strerror(errno), dirname);

        if (rmdir(dirname) == -1) {
            printErr(module, strerror(errno), dirname);
            exit(1);
        }
    } else/*{
        pid_t myPid = getpid();
        int me = 0;
        if (pid1 == myPid) me = 1;
        if (pid2 == myPid) me = 2;
        if (pid3 == myPid) me = 3;
        if (pid4 == myPid) me = 4;
        if (pid5 == myPid) me = 5;
        if (pid6 == myPid) me = 6;
        if (pid7 == myPid) me = 7;
        if (pid8 == myPid) me = 8;
        printf("я %d %d %d\n", me, getpid(), getpgid(0));
    }
        */while (1) pause();
}


int main(int argc, char *argv[]) {
    printf("TUT");
    module = basename(argv[0]);
    char *dirname = "/tmp/lab4";
    printf("TUT");
    if (mkdir(dirname, 0777) == -1) {
        printErr(module, strerror(errno), dirname);
        exit(1);
    }
    printf("TUT");
    makeTree();
    exchangeSignals(dirname);
    exit(0);
}