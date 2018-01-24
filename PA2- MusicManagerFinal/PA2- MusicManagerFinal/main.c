/*******************************************************************************************
* Programmer: Cong Trinh
* Class: CptS 122, Spring 2016; Lab Section 01
* Programming Assignment: PA2 Music Manager (Resubmission)
* Date: February 19, 2016
* Description: Organizes a list of music based off of song title, album, artist, etc
*******************************************************************************************/
#include "Header.h"

int main(void) {
	Node *pHead = NULL;
	Record *data = NULL;
	int option, sort_opt = 1, exit = 0;

	while (exit == 0) {
		printf("1. Load\n2. Store\n3. Display\n4. Insert\n5. Delete\n6. Edit\n7. Sort\n8. Rate\n9. Exit\n\nSelect an Option.");
		option = scan_int(1, 10);
		system("cls");
		switch (option) {
		case 1:	//*Load
			delete_list(&pHead);
			load(&pHead);
			break;
		case 2:	//*Store
			store(pHead);
			system("pause");
			break;
		case 3:	//*Display
			display_list(pHead);
			system("pause");
			break;
		case 4:	//*Insert
			data = get_data();
			insert(&pHead, data);
			break;
		case 5:	//*Delete
			delete_song(&pHead);
			break;
		case 6:	//*Edit
			edit_search(&pHead);
			break;
		case 7:	//Sort
			printf("1. Song\n2. Artist\n3. Album\n4. Genre\n5. Length\n6. Total Played\n7. Rating\n\n");
			printf("How would you like to sort your list? (Type Corresponding #)");
			sort_opt = scan_int(1, 7);
			break;
		case 8:	//*Rate
			rate_song(&pHead);
			break;
		case 9:	//*Exit
			exit = 1;
			break;
		case 10:	//Scrolls through songs (Meant more for TESTING pNext and pPrev... not apart of assignment.
			scroll_songs(pHead);										//does not work after display() is used)
			break;
		}
		sort(&pHead, sort_opt);	//Sorts & Updates List every run-through
		system("cls");
	}
	printf("Music Manager Successfully Terminated.\n");
	store(pHead);
	return 0;
}