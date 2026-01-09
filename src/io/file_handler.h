#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "../hero/hero_list.h"

#define MAX_FILE_NAME_LENGTH 256

bool save_list_to_file(HeroList* list);
HeroList* load_list_from_file();

#endif // FILE_HANDLER_H