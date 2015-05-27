#ifndef _DB_JSON_H_
#define _DB_JSON_H_

#include "db_driver.h"
#include "json.h"

#define JSON_HEAD		"EV_json"
#define JSON_TYPE		"EV_type"

void Json_insert_str(json_t *json,char *label,char *value);
void Json_insert_int(json_t *json,char *label,long value);
json_t * Json_insert_head(json_t *entry);
json_t *Json_create_title(int type);
#endif // DB_JSON_H
