#ifndef _D_TPL_H_
#define _D_TPL_H_

#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "ctype.h"

#include "hash.h"

#ifdef _ENABLE_TRACEBACK
#include "traceback.h"
#endif

#define MAX_TPL_LINE 2048
#define MAX_LINE_LENGTH 1024
#define MAX_KEY_LENGTH 128
#define MAX_VAL_LENGTH 128

#define VAR_DELM '.'

#define VAR_OPEN "{$"
#define VAR_CLOSE "}"

#define TYPE_STRING 1
#define TYPE_HASH 2

typedef struct _node_t
{
	int t;
	void* v;
}node_t, *pnode_t;

char *get_key_val(char *key, hash_t *hash_table);

void render(char *tpl);

void line_handle(char *line);

int load_file(char *tpl);

#endif
