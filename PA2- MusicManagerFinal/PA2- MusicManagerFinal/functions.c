#include "Header.h"
/*************************************************************
* Function: get_data
* Description: Gets manually inputted data from user
* Input parameters: None
* Returns: Record
*************************************************************/
Record *get_data(void) {
	Record *data;
	char song[50];
	data = (Record*)malloc(sizeof(Record));
	printf("Song: ");	//Scans song's fields from user V
	scanf("%s", data->song);
	printf("Artist: ");
	scanf("%s", data->artist);
	printf("Album: ");
	scanf("%s", data->album);
	printf("Genre: ");
	scanf("%s", data->genre);
	printf("Duration: ");
	scanf("%d", &data->length);
	printf("Total # Played: ");
	scanf("%d", &data->played);
	printf("Rating(1-5): ");
	data->rating = scan_int(1, 5);
	return data;
}
/*************************************************************
* Function: insert
* Description: Inserts node of data into beginning of list
* Input parameters: pHead of Node, Record Data
* Returns: None
*************************************************************/
void insert (Node **pHead, Record *data) {
	Node *pCur = *pHead, *pMem = NULL;
	pMem = (Node*)malloc(sizeof(Node));
	pMem->data = (Record*)malloc(sizeof(Record));
	edit_node(pMem, data);
	pMem->pNext = NULL;
	pMem->pPrev = NULL;
	if (pMem != NULL) {	//Inserts at beginning if empty
		if (*pHead == NULL)
			*pHead = pMem;
		else {	//Moves current beginning node up and inserts pMem in beginning
			pCur->pPrev = pMem;		//[pMem]<-[pCur]
			pMem->pNext = pCur;		//[pMem]->[pCur]
			*pHead = pMem;
		}
	}
}
/*************************************************************
* Function: edit_node
* Description: Stores the record data into the node
* Input parameters: pMem of Node, Record Data
* Returns: None
*************************************************************/
void edit_node(Node *pMem, Record *data) {
	strcpy(pMem->data->song, data->song);	//Stores data from record to pMem V
	strcpy(pMem->data->artist, data->artist);
	strcpy(pMem->data->album, data->album);
	strcpy(pMem->data->genre, data->genre);
	pMem->data->length = data->length;
	pMem->data->played = data->played;
	pMem->data->rating = data->rating;
	pMem->pNext = NULL;
}
/*************************************************************
* Function: load
* Description: Loads playlist from file
* Input parameters: pHead of Node
* Returns: None
*************************************************************/
void load(Node *pHead) {
	Record *data;
	FILE *infile = fopen("playlist.txt", "r");
	data = (Record*)malloc(sizeof(Record));
	while (!feof(infile)) {		//Loads through all songs in file
		fscanf(infile, "%s", &data->song);		//Loads all song's fields  and inserts into list V
		fscanf(infile, "%s", &data->artist);
		fscanf(infile, "%s", &data->album);
		fscanf(infile, "%s", &data->genre);
		fscanf(infile, "%d", &data->length);
		fscanf(infile, "%d", &data->played);
		fscanf(infile, "%d", &data->rating);
		insert(pHead, data);
	}
	printf("Data loaded Succesfully.\n\n");
	system("pause");
	fclose(infile);
}
/*************************************************************
* Function: delete_list
* Description: Deletes the whole list
* Input parameters: pHead of Node
* Returns: None
*************************************************************/
void delete_list(Node **pHead) {
	Node *pCur = *pHead, *pTemp;
	while (pCur != NULL) {	//Scrolls through list, deleting each node
		pTemp = pCur->pNext;
		free(pCur);		//Deletes node every scroll through
		pCur = pTemp;
	}
	*pHead = NULL;
}
/*************************************************************
* Function: store
* Description: Stores the current list of data into "storedlist.txt"
* Input parameters: pHead of Node
* Returns: None
*************************************************************/
void store(Node *pHead) {
	Node *pCur = pHead;
	FILE *outfile = fopen("storedlist.txt", "w");	//Writes data into "storedlist.txt"
	if (pCur != NULL) {	//Defense Mechanicism
		while (pCur != NULL) {	//Scrolls through list until empty
			fprintf(outfile, "-SONG: %s", pCur->data->song);	//Stores all fields into outfile V
			fprintf(outfile, "\tARTIST: %s", pCur->data->artist);
			fprintf(outfile, "\tALBUM: %s", pCur->data->album);
			fprintf(outfile, "\tGENRE: %s", pCur->data->genre);
			fprintf(outfile, "\tDURATION: %ds", pCur->data->length);
			fprintf(outfile, "\tTOTAL-PLAYED: %d", pCur->data->played);
			fprintf(outfile, "\tRATING: %d/5\n", pCur->data->rating);
			pCur = pCur->pNext;
		}
		printf("Data Succesfully Stored in \"storedlist.txt\".\n\n");
	}
	else
		printf("No Data Found to Store.\n\n");	//Error Check: Empty List
	fclose(outfile);
}
/*************************************************************
* Function: sort
* Description: Sorts data in order, depending on sort_option
* Input parameters: pHead of Node, Sorting Option
* Returns: None
*************************************************************/
void sort(Node **pHead, int sort_option) {
	Node *pCur = NULL, *pPrev = NULL;
	int compare = 0, i = 0, loop = 1;
	pCur = (Node*)malloc(sizeof(Node));
	pCur->data = (Record*)malloc(sizeof(Record));
	pPrev = (Node*)malloc(sizeof(Node));
	pPrev->data = (Record*)malloc(sizeof(Record));

	if (*pHead != NULL && pPrev->pNext != NULL) {
		while (loop == 1) {
			loop = 0;
			pCur = *pHead;
			pPrev = pCur;
			pCur = pCur->pNext;
			while (pPrev->pNext != NULL) {
				compare = 0;	//Determines whether nodes should be swapped or not
				switch (sort_option) {	//Compares certain fields based on sorting option chose
				case 1:
					compare = strcmp(pPrev->data->song, pCur->data->song);
					break;
				case 2:
					compare = strcmp(pPrev->data->artist, pCur->data->artist);
					break;
				case 3:
					compare = strcmp(pPrev->data->album, pCur->data->album);
					break;
				case 4:
					compare = strcmp(pPrev->data->genre, pCur->data->genre);
					break;
				case 5:
					if (pPrev->data->length > pCur->data->length)
						compare = 1;
					break;
				case 6:
					if (pPrev->data->played > pCur->data->played)
						compare = 1;
					break;
				case 7:
					if (pPrev->data->rating > pCur->data->rating)
						compare = 1;
					break;
				}
				if (compare > 0) {	//Swaps the 2 nodes of Prev and Cur
					swap_nodes(pPrev, pCur);
					loop = 1;
				}
				pPrev = pCur;
				pCur = pCur->pNext;
			}
		}
	}
}
/*************************************************************
* Function: swap_nodes
* Description: Swaps 2 nodes with each other
* Input parameters: Node1, Node2
* Returns: None
*************************************************************/
void swap_nodes(Node *node1, Node *node2) {
	Record *temp = (Record*)malloc(sizeof(Record));
	temp = node1->data;	//Stores node1 into temp
	node1->data = node2->data;	//node2 -> node1
	node2->data = temp;			//node2 <- temp;
}
/*************************************************************
* Function: display_list
* Description: Displays playlist for user to view
* Input parameters: pHead of Node
* Returns: None
*************************************************************/
void display_list(Node *pHead) {
	Node *pCur = pHead;
	printf("SONG\tARTIST\tALBUM\tGENRE\tLENGTH\tPLAYED\tRATING\n");
	printf("______________________________________________________________\n");
	while (pCur != NULL) {	//Prints song's fields while scrolling through playlist
		printf("-%s", pCur->data->song);
		printf("\t%s", pCur->data->artist);
		printf("\t%s", pCur->data->album);
		printf("\t%s", pCur->data->genre);
		printf("\t%ds", pCur->data->length);
		printf("\t%d", pCur->data->played);
		printf("\t%d/5\n", pCur->data->rating);
		pCur->pPrev = pCur;//
		pCur = pCur->pNext;
	}
}
/*************************************************************
* Function: delete_song
* Description: Deletes indiviual song from song search
* Input parameters: pHead of Node
* Returns: None
*************************************************************/
void delete_song(Node **pHead) {
	Node *pCur = *pHead, *pPrev = NULL;
	char search[50];
	printf("Which Song do you want to delete?\n >>");
	scanf("%s", search);
	if (pCur != NULL) {
		while (pCur != NULL && strcmp(pCur->data->song, search) != 0) {	//Searches for song through list
			pPrev = pCur;
			pCur = pCur->pNext;	//Scrolls down songs
		}
		if (pPrev == NULL) {	//Beginning of List
			*pHead = (*pHead)->pNext;
			free(pCur);
			printf("\nSong Succesfully Deleted from the List.\n\n");
		} else if (pCur != NULL) {	//Mid/End of List
			pPrev->pNext = pCur->pNext;
			(pPrev->pNext)->pPrev = pPrev;
			free(pCur);
			printf("\nSong Succesfully Deleted from the List.\n\n");
		} else	//No Song Found
			printf("\nNo Song Found to Delete.\n\n");
	}
	system("pause");
}
/*************************************************************
* Function: edit_search
* Description: Searches for song to edit, based on field
* Input parameters: pHead of Node
* Returns: None
*************************************************************/
void edit_search(Node **pHead) {
	Node *pCur = *pHead, *pPrev = NULL, *pSearch = NULL;
	char search_str[50];
	int option, search_int, check = 1;
	if (*pHead != NULL) {
		printf("1. Song\n2. Artist\n3. Album\n4. Genre\n5. Length\n6. Total Played\n7. Rating\n");
		printf("How would you like to find your song? (Type Corresponding #)\n");
		option = scan_int(1, 7);
		printf("SEARCH: ");
		if (option <= 4)
			scanf("%s", search_str);	//Asks user to input string to search
		else
			scanf("%d", &search_int);	//Asks user to input number to search
		do {
			switch (option) {	//Searches by song's field
			case 1:	//Song
				check = strcmp(search_str, pCur->data->song);
				break;
			case 2:	//Artist
				check = strcmp(search_str, pCur->data->artist);
				break;
			case 3:	//Album
				check = strcmp(search_str, pCur->data->album);
				break;
			case 4:	//Genre
				check = strcmp(search_str, pCur->data->genre);
				break;
			case 5:	//Length
				if (search_int == pCur->data->length)
					check = 0;
				break;
			case 6:	//Times Played
				if (search_int == pCur->data->played)
					check = 0;
				break;
			case 7:	//Rating
				if (search_int == pCur->data->rating)
					check = 0;
				break;
			}
			if (check == 0)
				edit_song(pCur);	//Edits song's fields
			pPrev = pCur;
			pCur = pCur->pNext;	//Scrolls through list if no song found
		} while ((pPrev != NULL || pCur != NULL) && check != 0);	//Exits if no more songs or song is found
	} else {
		printf("List is Empty, No Song to Edit.\n\n");
		system("pause");
	}
}
/*************************************************************
* Function: edit_song
* Description: Edits the song's fields
* Input parameters: pHead of Node
* Returns: None
*************************************************************/
void edit_song(Node *pHead) {
	int edit = 0;
	while (edit != 8) {
		system("cls");
		printf("Located Song: \"%s\".\n[*** EDIT MENU ***]\n", pHead->data->song);
		printf("1. Song \t[%s]\n2. Artist\t[%s]\n3. Album\t[%s]\n4. Genre\t[%s]\n5. Length\t[%d]\n6. Total-Played\t[%d]\n7. Rating\t[%d]\n",
			pHead->data->song, pHead->data->artist, pHead->data->album, pHead->data->genre, pHead->data->length, pHead->data->played, pHead->data->rating);
		printf("8. Exit\n");
		edit = scan_int(1, 8);
		switch (edit) {	//Edits song's fields
		case 1:
			printf("Rename Song: ");
			scanf("%s", pHead->data->song);
			break;
		case 2:
			printf("Rename Artist: ");
			scanf("%s", pHead->data->artist);
			break;
		case 3:
			printf("Rename Album: ");
			scanf("%s", pHead->data->album);
			break;
		case 4:
			printf("Rename Genre: ");
			scanf("%s", pHead->data->genre);
			break;
		case 5:
			printf("Edit Length(sec): ");
			scanf("%d", &pHead->data->length);
			break;
		case 6:
			printf("Edit Total-Played: ");
			scanf("%d", &pHead->data->played);
			break;
		case 7:
			printf("Re-Rate (1-5)");
			pHead->data->rating = scan_int(1, 5);
			break;
		case 8:	//Exits edit menu
			break;
		}
	}
}
/*************************************************************
* Function: rate_song
* Description: Rates the song from 1-5
* Input parameters: pHead of Node
* Returns: None
*************************************************************/
void rate_song(Node **pHead) {
	Node *pCur = *pHead, *pPrev = NULL;
	char search[50];
	if (*pHead != NULL) {
		printf("Which song do you want to rate?\n >>");
		scanf("%s", search);
		while (pCur != NULL && strcmp(pCur->data->song, search) != 0) {	//Searches through list for song
			pPrev = pCur;
			pCur = pCur->pNext;
		}
		if (pCur != NULL) {	//Song is Found
			printf("Rate the Song from 1 - 5.\n >>");
			scanf("%d", &pCur->data->rating);
		}
	}
	else {	//Defense Check if List is Empty
		printf("List is Empty, No Song to Rate.\n\n");
		system("pause");
	}
}
/*************************************************************
* Function: scan_int
* Description: Scans an integer within a limited range
* Input parameters: Min & Max ints
* Returns: Scanned Int
*************************************************************/
int scan_int(int min, int max) {
	int num;
	for (;;) {	//Infinitive loop
		printf("\n >>");
		scanf("%d", &num);
		printf("\n");
		if (num < min || num > max)	//Scanned number can only be within the min & max range
			printf("[(!)ERROR--INPUT OUT OF RANGE]");
		else
			return num;
	}
}
/*************************************************************
* Function: scroll_song [TESTING FUNCTION]
* Description: Created to Test pNext and pPrev
* Input parameters: pHead of Node
* Returns: None
* Error: Crashes when scrolling past beginning/end list.
*************************************************************/
void scroll_songs(Node *pHead) {
	Node *pCur = pHead;
	int exit = 0, direction = 0;
	if (pCur != NULL) {
		printf("TEST SONG- %s\n\n", pCur->data->song);
		while (direction != 2) {
			printf(" Scroll through Song\n(<-0...[2=Exit]...1->)");
			scanf("%d", &direction);
			system("cls");
			if (direction == 1)			//Scrolls up list
				pCur = pCur->pNext;
			else if (direction == 0)	//Scrolls down list
				pCur = pCur->pPrev;
			printf("TEST SONG- %s\n\n", pCur->data->song);
		}
		system("pause");
	}
}