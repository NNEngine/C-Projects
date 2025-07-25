#ifndef UTILS_H
#define UTILS_H

void list_directory(const char *path);
void view_file(const char *filepath);
char *join_path(const char *base, const char *entry);
int is_directory(const char *path);

#endif