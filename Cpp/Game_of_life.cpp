#include <graphics.h>
#include <time.h>
//#include <math.h>

#define W 100
void pointer(int x, int y,int col){
     setcolor(col);
     
     rectangle(x,y,x+2,y+2);
     putpixel(x+1,y+1,col);
     /*
     putpixel(x,y,col);
     putpixel(x+1,y,col);
     putpixel(x+2,y,col);
     putpixel(x,y+1,col);
     putpixel(x+1,y+1,col);
     putpixel(x+2,y+1,col);
     putpixel(x,y+2,col);
     putpixel(x+1,y+2,col);
     putpixel(x+2,y+2,col);*/
}     

int main()  {
    initwindow(W*3,W*3);
    int color = 15;
    srand(time(NULL));
    int field[W][W]={0};
    int field2[W][W]={0};



    for (int ix=0;ix<W;ix++){
      for (int iy=0;iy<W;iy++){
        field[ix][iy]=rand()%2*rand()%2;
      }
    }

    while (1){
      //clearviewport();
      

      for (int ix=0;ix<W;ix++) for (int iy=0; iy<W;iy++){  
      	int m = field[ix-1][iy-1]+field[ix][iy-1]+field[ix+1][iy-1]+field[ix-1][iy]+field[ix+1][iy]+field[ix-1][iy+1]+field[ix][iy+1]+field[ix+1][iy+1];
      	
        if (field[ix][iy]==0){
        	if (m==3) { field2[ix][iy]=1;}
      	}
      	else{
       		if  ((m==2) || (m==3)){field2[ix][iy]=1;} else { field2[ix][iy]=0;}
      	}
       
      }
      
      for (int ix=0;ix<W;ix++){
        for (int iy=0;iy<W;iy++){
          if (field[ix][iy] != field2[ix][iy]){
          if (field2[ix][iy]==0){
            pointer(ix*3,iy*3,0);
            
          }
          else{
            pointer(ix*3,iy*3,15);
          }
          } 
        }
      }
      for (int ix=0;ix<W;ix++) for (int iy=0; iy<W;iy++){
		field[ix][iy]=field2[ix][iy];
		//field2[ix][iy]=0;
		}
    delay(1);
    }

    getch();
    closegraph();
return 0;
}

