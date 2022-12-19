#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAXCHAR 1000

void listFiles(char *basePath, char *find);
int isDirectory(char *path);
int isRegularFile(char *path);
void searchFile(char *file, char *find);

int main(int argc, char *argv[]){
    printf("\n");

   if(argc != 3){
        printf("Not enough arguments passed!\n");
        printf("./test \"Directory Path\" \"Search Word\"\n\n");

        return 1;
    }

    char *path = argv[1];
    char *find = argv[2];

    listFiles(path, find);

    printf("\n");

    return 0;
}

void listFiles(char *basePath, char *find){
    char path[MAXCHAR];
    struct dirent *dp;
    DIR *dir = opendir(basePath);
    int isDir;
    int isRegFile;

    if(!dir){
        return;
    }

    while((dp = readdir(dir)) != NULL){
        if(strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0){
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            isDir = isDirectory(path);

               if(isDir == 1){
                   printf("%s\n", path);
            }else{
                isRegFile = isRegularFile(path);

                if(isRegFile == 1){
                    printf("%s\n", path);
                    searchFile(path, find);
                }else{
                    printf("%s\n", path);
                }
            }

            listFiles(path, find);
        }
    }

   closedir(dir);
}

int isDirectory(char *path){
    struct stat sb;
    stat(path, &sb);

    return S_ISDIR(sb.st_mode);
}

int isRegularFile(char *path){
    struct stat sb;
    stat(path, &sb);

    return S_ISREG(sb.st_mode);
}

void searchFile(char *file, char *find){
    FILE *regFile;
    char line[MAXCHAR];

    regFile = fopen(file, "r");

    if(regFile == NULL){
        return;
    }else{
        while(fgets(line, MAXCHAR, regFile) != NULL){
            if(strstr(line, find) != NULL){
                printf("%s", line);
            }
        }
    }

	fclose(regFile);
}