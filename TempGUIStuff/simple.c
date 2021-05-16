/***********************************************************
*
*A simple GTK example
*simple.c: show a 2x2 board and move the king by clicking
*author: Weiwei Chen
*initial version: 01/22/13 EECS22L Winter 2013
*
***********************************************************/

#include <gtk/gtk.h>
#include "simple.h"
#include "string.h"
/*Global Variables */

GtkWidget *window ;  
GtkWidget *fixed ; 
GtkWidget *chess_icon ; 
GtkWidget *table ; 


enum GRID Board[8][8];

void InitBoard()
{
	Board[0][0] = BROOK;
	Board[3][0] = BQUEEN;
	Board[4][0] = BKING;
	Board[1][0] = WHITE;
        Board[1][1] = BLACK;
	Board[0][1] = WHITE;
}

void ResetBoard()
{
	int i, j;
	
	for (i = 0; i < 8; i++) 
	{
		Board[i][1] = BPAWN;
		Board[i][6] = WPAWN;	
	} 

	Board[0][0] = BROOK;
	Board[1][0] = BKNIGHT;
	Board[2][0] = BBISHOP;
	Board[3][0] = BQUEEN;
	Board[4][0] = BKING;
	Board[5][0] = BBISHOP;
	Board[6][0] = BKNIGHT;
	Board[7][0] = BROOK;

	Board[0][7] = WROOK;
	Board[1][7] = WKNIGHT;
	Board[2][7] = WBISHOP;
	Board[3][7] = WQUEEN;
	Board[4][7] = WKING;
	Board[5][7] = WBISHOP;
	Board[6][7] = WKNIGHT;
	Board[7][7] = WROOK;

	for (i = 0; i < 8; i++) 
	{
		for (j = 2; j < 6; j++)
		{
			if ((i%2 == 0) && (j%2 == 0))
			{
				Board[i][j] = WHITE;	
			}
		
			else if((i%2 == 0) && (j%2 != 0))
			{
				Board[i][j] = BLACK;
			}

			else if ((i%2 != 0) && (j%2 == 0))
			{
				Board[i][j] = BLACK;
			}
			
			else if ((i%2 != 0) && (j%2 != 0))
			{	
				Board[i][j] = WHITE;
			}
		}
	} 
}

void ReverseGridColor(int g_x, int g_y)
{
	if(Board[g_x][g_y] == BLACK)
	{
		Board[g_x][g_y] = WHITE;
	}
	else
	{
		Board[g_x][g_y] = BLACK;
	}
}

void MoveTheKing(int g_x, int g_y)
{
	ResetBoard();
	Board[g_x][g_y] = BKING;
}

void MoveTheQueen(int g_x, int g_y)
{
	ResetBoard();
	Board[g_x][g_y] = BQUEEN;
}

void MoveTheRook(int g_x, int g_y)
{
	ResetBoard();
	Board[g_x][g_y] = BROOK;
}

void DrawBoard()
{
	int i, j;

        for(i = 0; i < 8; i ++)
	{
		for(j = 0; j < 8; j ++)
		{
			switch(Board[i][j])
			{
				case BLACK:
					chess_icon = gtk_image_new_from_file("blacksquare_80x80.png") ;
					break;
				case WHITE:
					chess_icon = gtk_image_new_from_file("whitesquare_80x80.png") ;
					break;
				case BKING:
					chess_icon = gtk_image_new_from_file("./chess_icon/blackking_80x80.png") ;
					break;
				case BQUEEN: 
					chess_icon = gtk_image_new_from_file("./chess_icon/blackqueen_80x80.png");
					break;
				case BROOK: 
					chess_icon = gtk_image_new_from_file("./chess_icon/blackrook_80x80.png");
					break;
				case BKNIGHT:
					chess_icon = gtk_image_new_from_file("./chess_icon/blackknight_80x80.png");
					break;
				case BBISHOP:
					chess_icon = gtk_image_new_from_file("./chess_icon/blackbishop_80x80.png");
					break;
				case BPAWN:
					chess_icon = gtk_image_new_from_file("./chess_icon/blackpawn_80x80.png");
					break;
				case WKING:
					chess_icon = gtk_image_new_from_file("./chess_icon/whiteking_80x80.png");
					break;
				case WQUEEN:
					chess_icon = gtk_image_new_from_file("./chess_icon/whitequeen_80x80.png");
					break;
				case WROOK:
					chess_icon = gtk_image_new_from_file("./chess_icon/whiterook_80x80.png");
					break;
				case WKNIGHT:
					chess_icon = gtk_image_new_from_file("./chess_icon/whiteknight_80x80.png");
					break;
				case WBISHOP:
					chess_icon = gtk_image_new_from_file("./chess_icon/whitebishop_80x80.png");
					break;
				case WPAWN:
					chess_icon = gtk_image_new_from_file("./chess_icon/whitepawn_80x80.png");
					break;
				default:
					break;
				
			}
			gtk_table_attach(GTK_TABLE(table), chess_icon, i, i + 1, j, j + 1, GTK_FILL, GTK_FILL, 0, 0) ;
		}
	}	
}

void CoordToGrid(int c_x, int c_y, int *g_x, int *g_y)
{
	*g_x = (c_x - BOARD_BORDER) / SQUARE_SIZE;
	*g_y = (c_y - BOARD_BORDER) / SQUARE_SIZE;
}

/* This is a callback function. The data arguments are ignored
 * in this example. More on callbacks below.
 */
static void
print_hello (GtkWidget *widget,
     gpointer   data)
{
  g_print ("Hello World\n");
}

static gboolean
on_delete_event (GtkWidget *widget,
         GdkEvent  *event,
         gpointer   data)
{
  /* If you return FALSE in the "delete_event" signal handler,
   * GTK will emit the "destroy" signal. Returning TRUE means
   * you don't want the window to be destroyed.
   *
   * This is useful for popping up 'are you sure you want to quit?'
   * type dialogs.
   */

  g_print ("delete event occurred\n"); 
  gtk_main_quit();
  return TRUE;
}

gint area_click (GtkWidget *widget,
                 GdkEvent  *event, 
                 gpointer  data)
{
  int x1, y1 ; 
  char words[MAX_MSGLEN] ; 

  int coord_x, coord_y, grid_x, grid_y; 

  struct BOARD *chess_board ; 
  struct SQUARE *chess_piece ;
  struct SQUARE *piece_dest ;   

  GdkModifierType state ; 

  gdk_window_get_pointer(widget->window, &coord_x, &coord_y, &state) ; 

  CoordToGrid(coord_x, coord_y, &grid_x, &grid_y);

  printf("coord_x = %d, coord_y = %d, grid_x = %d, grid_y = %d \n", coord_x, coord_y, grid_x, grid_y);

  MoveTheKing(grid_x, grid_y);


    gtk_container_remove(GTK_CONTAINER(window), fixed) ; 
    table = gtk_table_new (2, 2, TRUE) ;
    gtk_widget_set_size_request (table, BOARD_WIDTH, BOARD_HEIGHT) ;
    DrawBoard(); 

    /*set fixed*/

    fixed = gtk_fixed_new() ;
    gtk_fixed_put(GTK_FIXED(fixed), table, 0, 0) ;
    gtk_container_add(GTK_CONTAINER(window), fixed) ;
    gtk_widget_show_all(window) ; 

  return TRUE ; 
}



int
main (int   argc,
      char *argv[])
{
  char str[MAX_MSGLEN]; 
 
  gtk_init(&argc, &argv) ;
  ResetBoard(); 
 
  /*create a new window */
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL) ;
  gtk_widget_set_size_request(window, WINDOW_WIDTH, WINDOW_HEIGHT) ; 
  gtk_container_set_border_width (GTK_CONTAINER(window), WINDOW_BORDER) ; 
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER) ; 
  gtk_window_set_title(GTK_WINDOW(window), "Let's play HeroChess 2.0!") ; 
  gtk_window_set_resizable(GTK_WINDOW(window), FALSE) ; 


  /*register event handlers*/
  g_signal_connect(window, "delete_event", G_CALLBACK(on_delete_event), NULL) ; 
  gtk_widget_set_events(window, GDK_BUTTON_PRESS_MASK) ; 
  g_signal_connect(window, "button_press_event", G_CALLBACK(area_click), NULL) ; 

  /*create a table and draw the board*/
  table = gtk_table_new (8, 8, TRUE) ; 
  gtk_widget_set_size_request (table, BOARD_WIDTH, BOARD_HEIGHT) ; 
  DrawBoard();
  
  fixed = gtk_fixed_new() ; 
  gtk_fixed_put(GTK_FIXED(fixed), table, 0, 0) ; 
  gtk_container_add(GTK_CONTAINER(window), fixed) ; 


  /*show the window*/
  gtk_widget_show_all(window) ; 
  gtk_main() ; 

  return 0 ;
}

// EOF //
