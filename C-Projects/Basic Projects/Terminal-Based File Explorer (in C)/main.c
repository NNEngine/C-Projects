#include "lib.h"
#include "utils.h"

#ifndef NAME_MAX
#define NAME_MAX 255
#endif

void clear_screen()
{
    system("cls"); // Windows command to clear terminal
}

int main()
{
    char current_path[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, current_path);

    while (1)
    {
        list_directory(current_path);

        printf("\nEnter number to open, '..' to go back, 'q' to quit:\n> ");
        char input[100];
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // Remove newline

        if (strcmp(input, "q") == 0)
        {
            printf("Exiting File Explorer...\n");
            break;
        }
        else if (strcmp(input, "..") == 0)
        {
            SetCurrentDirectory("..");
            GetCurrentDirectory(MAX_PATH, current_path);
            continue;
        }
        else
        {
            int choice = atoi(input);
            if (choice == 0)
            {
                printf("Invalid input.\n");
                continue;
            }

            // Re-scan directory to match index to entry
            DIR *dir = opendir(current_path);
            if (!dir)
            {
                perror("opendir failed");
                continue;
            }

            struct dirent *entry;
            int index = 1;
            char selected[NAME_MAX];
            int found = 0;

            while ((entry = readdir(dir)) != NULL)
            {
                if (strcmp(entry->d_name, ".") == 0)
                    continue;
                if (index == choice)
                {
                    strcpy(selected, entry->d_name);
                    found = 1;
                    break;
                }
                index++;
            }

            closedir(dir);

            if (!found)
            {
                printf("Invalid choice.\n");
                continue;
            }

            char *full_path = join_path(current_path, selected);

            if (is_directory(full_path))
            {
                if (SetCurrentDirectory(full_path))
                {
                    GetCurrentDirectory(MAX_PATH, current_path);
                }
                else
                {
                    perror("Failed to enter directory");
                }
            }
            else
            {
                view_file(full_path);
                printf("\nPress Enter to continue...");
                fgets(input, sizeof(input), stdin);
            }
        }

        clear_screen(); // Windows clear
    }

    return 0;
}
