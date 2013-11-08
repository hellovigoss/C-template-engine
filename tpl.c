
#include "tpl.h"

hash_t *g_var;

#define ARRAY_INIT(name) hash_t *tmp_ht_##name = hash_new();

#define ARRAY_INSERT(name, key, val) hash_set(tmp_ht_##name, key, new_node(TYPE_STRING, val));

#define ARRAY_DONE(name) hash_set(g_var, #name, new_node(TYPE_HASH, tmp_ht_##name));

#define ARRAY_APPEND(name, to) hash_set(tmp_ht_##to, #name, new_node(TYPE_HASH, tmp_ht_##name));

#define ASSIGN(key, val) do{	\
	hash_set(g_var, key, new_node(TYPE_STRING, val));	\
}while(0);

pnode_t new_node(int t, void* val){
	pnode_t pnode;
	pnode = (pnode_t)malloc(sizeof(node_t));
	pnode->t = t;
	pnode->v = val;
	return pnode;
}

char *get_key_val(char *key, hash_t *hash_table){
	char *pos;
	if((pos = strchr(key, VAR_DELM)) != NULL){
		*(pos++) = '\0';
		if(hash_has(hash_table, key)){
			if(TYPE_HASH == ((pnode_t)hash_get(hash_table, key))->t){
				return get_key_val(pos, ((pnode_t)hash_get(hash_table, key))->v);
			}
			else{
				return "";
			}
			
		}
		else{
			return "";
		}
	}
	else{
		if(TYPE_STRING == ((pnode_t)hash_get(hash_table, key))->t){			 
			return (char *)((pnode_t)hash_get(hash_table, key))->v;
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
	#ifdef _ENABLE_TRACEBACK
	init_environments();
	#endif
	g_var = hash_new();

	ASSIGN("a", "三金个小王八蛋");

	ARRAY_INIT(b);
	ARRAY_INSERT(b, "c", "确实啊ccccc");
	ARRAY_INSERT(b, "d", "ed");
	ARRAY_INIT(e);
	ARRAY_INSERT(e, "C", "小儿");
	ARRAY_APPEND(e, b);
	ARRAY_DONE(b);
	
	render("a.tpl");
	return 0;
}
