#include "tpl.h"

hash_t *g_var;

#define ASSIGN(key, val) do{	\
	hash_set(g_var, key, val);	\
}while(0);

void render(char *tpl){
	int tpl_line_num;
	tpl_line_num = load_file(tpl);
	hash_free(g_var);
}

void line_handle(char *line){
	int i = 0, j = 0, k = 0, last_start = 0;	
	char key[1024], temp[1024], new_line[MAX_LINE_LENGTH];
	memset(new_line, '\0', sizeof(new_line));
	while('\0' != *line && NULL != *line){
		if(*line == VAR_OPEN[0] && *(line+1) == VAR_OPEN[1]){
			line = line + 2;
			memset(key, '\0', sizeof(key));
			while(*(line) != VAR_CLOSE[0]){
			 	sprintf(key, "%s%c", key, *line);
			 	line ++;
			}
			sprintf(new_line, "%s%s", new_line, hash_get(g_var, key));
		}
		else{
			sprintf(new_line, "%s%c", new_line, *line);
		}
		line++;
	}
	printf("%s", new_line);
}

int load_file(char *tpl){
	FILE *fp;
	int i = 0;
	char line[MAX_LINE_LENGTH];
	if(NULL != (fp = fopen(tpl, "r"))){
		while(!feof(fp)){
			fgets(line, MAX_LINE_LENGTH, fp);
			line_handle(line);
			i++;
		}
		
	}
	fclose(fp);
	return i;
}

int main(int argc, char *argv[]){
	g_var = hash_new();
	ASSIGN("head", "this is head");
	ASSIGN("body", "this is body");	
	render("a.tpl");	
	return 0;
}
