/**********************************************************************/
/*  Spencer Goles        COEN 11        29 November 2018  Version 9.0 */
/*  This program will administer a Urgent Care waiting list.          */
/*  It will be able to add, modify, view, and exit the linked list.   */
/*  Autosave feature updating into a binary file                      */
/*  Add XOR encryption to the text file before and after saving       */          
/*  Array of linked lists for each dept with text file I/O            */
/*  The program has been split into multiple files with a makefile    */
/**********************************************************************/

#include "link.h"
//Global Variables
struct head_tail lists[4];
pthread_mutex_t mutex;
//Main Control Function
int main(int argc, char *argv[ ])
{
        if (argc == 1)
        {
                printf("The name of the file is missing!\n");
                return 1;
        }
        //Convert key to int
        int key = atoi(argv[3]);
        read_file(argv[1],key);
	    //Create thread and mutex
        pthread_t thr;
        pthread_mutex_init (&mutex, NULL);
        pthread_create(&thr,NULL, auto_save,(void *) argv[2]);
        int cmd, i;
        printf("\n\nWelcome to the Urgent Care Waiting List\n\n");
        while(1)
        {
                printf("\n\nPlease Select a Command Below\n\n");
                printf("1. View List              3. Add Patient        5. Search Name          7. Read Autosave\n");
                printf("2. Show Department        4. Remove Patient     6. Change Department    8. Quit\n\n");
                printf("Enter Command: ");
                scanf("%d",&cmd);
                //Switch statement controls calling C modules from the main menu
                switch(cmd)
                {
                        case 1:
                                list();
                                break;
                        case 2:
                                show_dept();
                                break;
                        case 3:
                                collectInfo();
                                break;
                        case 4:
                                discard();
                                break;
                        case 5:
                                show_name();
                                break;
                        case 6:
                                change_dept();
                                break;
                        case 7:
                                read_auto_save(argv[2]);
                                break;
                        case 8:
				//Cancel thread
                                pthread_mutex_lock(&mutex);
                                pthread_cancel(thr);
                                pthread_mutex_unlock(&mutex);
                                write_all(argv[1],key);
                                //For loop uses recursive delete on array of linked lists
                                for(i = 0; i < 4; i++)
                                {
                                	delete_all(lists[i].head);
                                }
                                printf("\nHave a great day!\n\n");
                                exit(0);
                        default:
                                printf("That was not a valid responce. Please try again.");
                }
        }
        return 0;
}
