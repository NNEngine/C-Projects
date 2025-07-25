#include "lib.h"
#include "utils.h"

void list_directory(const char *path)
{
    DIR *dir = opendir(path);
    if (!dir)
    {
        perror("Failed to open directory");
        return;
    }

    struct dirent *entry;
    struct stat file_stat;
    int index = 1;

    printf("Directory: %s\n", path);
    printf("---------------------------------------\n");

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0)
            continue;

        char fullpath[PATH_MAX];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        if (stat(fullpath, &file_stat) == -1)
        {
            perror("stat error");
            continue;
        }
        printf("%2d.%-25s", index++, entry->d_name);

        if (S_ISDIR(file_stat.st_mode))
        {
            printf("    <DIR>\n");
        }
        else
        {
            printf("    %ld bytes\n", file_stat.st_size);
        }
    }
    printf("%2d. .. (Go Back)\n", index);
    printf("-------------------------------------------\n");
    closedir(dir);
}

void view_file(const char *filepath)
{
    FILE *fp = fopen(filepath, "r");
    if (!fp)
    {
        perror("Failed to open file");
        return;
    }

    char line[1024];
    printf("\n--- File: %s ---\n", filepath);
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        printf("%s", line);
    }
    printf("\n--- End of File ---\n");

    fclose(fp);
}

int is_directory(const char *path)
{
    struct stat statbuf;
    if (stat(path, &statbuf) != 0)
        return 0;
    return S_ISDIR(statbuf.st_mode);
}

char *join_path(const char *base, const char *entry)
{
    static char fullpath[PATH_MAX];
    snprintf(fullpath, sizeof(fullpath), "%s/%s", base, entry);
    return fullpath;
}