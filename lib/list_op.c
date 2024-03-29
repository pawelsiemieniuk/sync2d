#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>

#include "dir_op.h"

f_list *push(f_list *list_head, char *path, char *name, off_t size, time_t mod_time){
    f_list *head = list_head;
    f_list *last = calloc(1, sizeof(f_list));
    f_info *file_info = calloc(1, sizeof(f_info));

    file_info->f_size  = size;
    file_info->f_mtime = mod_time;
    strcpy(file_info->f_name, name);


    last->checked = false;
    last->file_i  = (struct f_info*)file_info;
    last->next    = NULL;    
    last->path    = calloc(strlen(path) + 1, sizeof(char));
    strcat(last->path, path);
    
    if(!list_head){ return last; }

    while(head->next){ head = (f_list*)head->next; }

    head->next = (struct f_list*)last;

    return list_head;
}

void clean(f_list *list_head){
    if(!list_head) { return; }


    while(list_head->next){
        f_list *tmp = (f_list*)list_head->next;
        free(list_head->path);
        free(list_head->file_i);
        free(list_head);
        list_head = tmp;
    }
    free(list_head->file_i);
    free(list_head);
}