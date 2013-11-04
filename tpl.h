#ifndef _D_TPL_H_
#define _D_TPL_H_

#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "ctype.h"

#include "hash.h"
//#include "mix_val.h"

#define MAX_TPL_LINE 2048
#define MAX_LINE_LENGTH 1024
#define MAX_KEY_LENGTH 128
#define MAX_VAL_LENGTH 128

#define VAR_DELM '.'

#define VAR_OPEN "{$"
#define VAR_CLOSE "}"

void render(char *tpl);

void line_handle(char *line);

int load_file(char *tpl);

#endif
