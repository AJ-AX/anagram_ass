#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

int count = 0;
int lists = 0;

void print_list(VNode *head){
	VNode *cur = head;
	int r = 0;
	while(cur){
		r++;
		cur = cur->next;
	}
	if(r > 1){
		cur = head;
		while(cur){
			printf("[%s] ", cur->value);
			cur = cur->next;
		}
		printf("End of List. Size [%d]\n", r);
		count += r;
		lists++;
	}
}

int comp(const void *a, const void *b){
	return *(char*)a - *(char*)b;
}

void dict_print(DNode *head){
	DNode *curr = head;
	while(curr){
		print_list(curr->values);
		curr = curr->next;
	}
}

int main (int argc, char ** argv) {
	
	/*DNode* result;
	
	//either static or use calloc - to set all bytes initially to 0
	static DNode* dictionary [DEFAULT_HASH_SIZE]; 
	
	
	set(dictionary, DEFAULT_HASH_SIZE, "pore", "repo");
	set(dictionary, DEFAULT_HASH_SIZE, "pore", "rope");
	
	
	result = get (dictionary, DEFAULT_HASH_SIZE, "pore");
	if (result != NULL) {
		printf("Anagrams for 'pore':\n");
		print_list (result->values);
	}
	else
		printf ("'pore' not found\n");
	
	set(dictionary, DEFAULT_HASH_SIZE, "bore", "robe");
	result = get (dictionary, DEFAULT_HASH_SIZE, "bore");
	if (result != NULL) {
		printf("Anagrams for 'bore':\n");
		print_list (result->values);
	}
	else
		printf ("'bore' not found\n");
	
	free_dictionary(dictionary, DEFAULT_HASH_SIZE);*/

	static DNode *Dictionary[DEFAULT_HASH_SIZE];

	FILE *fp;

	fp = fopen("words.txt", "r");
	char buffer[100];

	while(fscanf(fp, "%s", buffer) != EOF){
		char *sort = malloc(sizeof(char) * strlen(buffer));
		strcpy(sort, buffer);
		int len = strlen(sort);
		qsort(sort, len, sizeof(char), comp);
		set(Dictionary, DEFAULT_HASH_SIZE, sort, buffer);
		//printf("Inserted [%s] to key [%s]\n", buffer, sort);
		free(sort);
	}
	fclose(fp);

	for(int i = 0; i < DEFAULT_HASH_SIZE; i++){
		if(Dictionary[i]){dict_print(Dictionary[i]);}
	}

	printf("Total Anagrams: [%d]\n", count);
	printf("Total Anagram Lists/Groups: [%d]\n", lists);
	
	return 0;
}