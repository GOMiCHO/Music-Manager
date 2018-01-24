#include <stdio.h>
#include <string.h>

typedef struct record {
	char song[50];
	char artist[50];
	char album[50];
	char genre[50];
	int length;
	int played;
	int rating; //(1-5)
} Record;

typedef struct node {
	Record *data;
	struct Node *pPrev;
	struct node *pNext;
} Node;

Record *get_data(void);
void insert(Node **pHead, Record *data);
void edit_node(Node *pMem, Record *data);
void load(Node *pHead);
void delete_list(Node **pHead);
void store(Node *pHead);
void delete_song(Node **pHead);
void edit_search(Node **pHead);
void edit_song(Node *pHead);
void sort(Node **pHead, int sort_option);
void swap_nodes(Node *node1, Node *node2);
void rate_song(Node **pHead);
void display_list(Node *pHead);
int scan_int(int min, int max);
void scroll_songs(Node *pHead);
