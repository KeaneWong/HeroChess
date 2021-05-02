/* code below is temporary, will push code that actually 
  works later to avoid conflicts with any updates -rachel */
/**********************************************************/

/* player and game settings menu and handling */
void settings()
{
	int valid_input = 0;
	int option = 0;
	int mainmenu = 0;
	
	while (mainmenu == 0)
	{
	    /* Settings Menu */
    	printf("Welcome to Settings!\n");
    	printf("1. Change Player Colors\n");
    	printf("2. Go Back to Main Menu\n");
    	scanf("%d", &option);
    	getchar();
    	
    	while (valid_input == 0)
    	{
    		switch(option)
    		{
    			/* variables to store player numbers when user makes customizations */
    			int wp = 0; 
    			int bp = 0; 
    			
    			case 1:
    			{
    			    printf("case 1\n");
    			    int error = 0;
    			    
    			    /* remind user of chess's color rule and ask for the changes */
    			    printf("Please keep in mind that by the rules of chess, the player with white pieces goes first!\n");
    			    wp = whitepnum();
    			    
    			    /* automatically assign the black player's color */
    			    
    			    
    			    
    			    
    			    break;
    			}
    			
    			case 2:
    			{
    				printf("case 2\n");
    				mainmenu = 1;
    			    break;
    			}
    		
    			default:
    			{
    			    printf("Invalid input!\n");
    			    valid_input = 1;
    			    break;
    			}
    		}
    	}
    	
    	/* if no changes are made,keep default settings */
    	
	}
}

/* function to set the white player's to 1 or 2 */
int whitepnum(int wp)
{
	printf("Enter which player will have the white pieces (1 or 2):");
    scanf("%d", &wp);
    getchar();
    printf("Player %d ") 
    
	return wp;
}

/* function to set the black player's to 1 or 2 */
int blackpnum(int bp)
{
	wp =
	return bp;
}
