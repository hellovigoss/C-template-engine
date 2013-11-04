#include "tpl.h"

hash_t *g_var;

#define ASSIGN(key, val) do{	\
	hash_set(g_var, key, val);	\
}while(0);

char *get_key_val(char *key, hash_t *hash_table){
	char *pos, *val;
	if((pos = strchr(key, VAR_DELM)) != NULL){
		*(pos++) = '\0';
		if((val = hash_get(hash_table, key)) != NULL){
			return get_key_val(pos, val);			
		}
		else{
			return "";
		}
	}
	else{
		if((val = hash_get(hash_table, key)) != NULL){
			return val;
		}
		else{
			return "";
		}
	}
}

void render(char *tpl){
	int tpl_line_num;
	tpl_line_num = load_file(tpl);
	hash_free(g_var);
}

void line_handle(char *line){
	char key[1024], new_line[MAX_LINE_LENGTH];
	memset(new_line, '\0', sizeof(new_line));
	while('\0' != *line && NULL != *line){
		//handle common var		
		if(*line == VAR_OPEN[0] && *(line+1) == VAR_OPEN[1]){
			line = line + 2;
			memset(key, '\0', sizeof(key));
			while(*(line) != VAR_CLOSE[0]){
			 	sprintf(key, "%s%c", key, *line);
			 	line ++;
			}
			sprintf(new_line, "%s%s", new_line, get_key_val(key, g_var));
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
			if(NULL != fgets(line, MAX_LINE_LENGTH, fp)){			
				line_handle(line);
				i++;				
			}			
		}
		
	}
	fclose(fp);
	return i;
}

int main(int argc, char *argv[]){
	g_var = hash_new();
	ASSIGN("a", "三金个小王八蛋");

	hash_t *n_h1 = hash_new();
	hash_set(n_h1, "c", "确实");

	hash_t *n_h2 = hash_new();
	hash_set(n_h2, "e", "确实啊");
	hash_set(n_h1, "d", n_h2);

	ASSIGN("b", n_h1);	

	render("a.tpl");
	return 0;
}
