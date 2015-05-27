#include "db_json.h"
#include "json.h"



json_t *Json_create_title(int type)
{
    json_t *entry;
    entry = json_new_object();
    Json_insert_int(entry,JSON_TYPE,type);
    return entry;
}

json_t * Json_insert_head(json_t *entry)
{
    json_t *root = NULL;
    json_t *label;
    root = json_new_object();
    label = json_new_string(JSON_HEAD);
    json_insert_child(label,entry);
    json_insert_child(root,label);
    return root;
}


void Json_insert_str(json_t *json,char *label,char *value)
{
    json_t *j_label,*j_value;
    if(label == NULL || value == NULL || json == NULL )
        return;
    j_label = json_new_string(label);
    j_value = json_new_string(value);
    json_insert_child(j_label,j_value);
    json_insert_child(json,j_label);


}


void Json_insert_int(json_t *json,char *label,long value)
{
    json_t *j_label,*j_value;
    char buf[10] = {0};
    if(label == NULL || json == NULL )
        return;
    sprintf(buf,"%ld",value);
    j_label = json_new_string(label);
    j_value = json_new_number(buf);


    json_insert_child(j_label,j_value);
    json_insert_child(json,j_label);
}
