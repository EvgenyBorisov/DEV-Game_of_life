#include <graphics.h>
#include <time.h>
//#include <math.h>

#define W 100
void pointer(int x, int y,int col){
     putpixel(x,y,col);
     putpixel(x+1,y,col);
     putpixel(x+2,y,col);
     putpixel(x,y+1,col);
     putpixel(x+1,y+1,col);
     putpixel(x+2,y+1,col);
     putpixel(x,y+2,col);
     putpixel(x+1,y+2,col);
     putpixel(x+2,y+2,col);
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
      

      for (int ix=1;ix<W-1;ix++) for (int iy=1; iy<W-1;iy++){  
      	int m = field[ix-1][iy-1]+field[ix][iy-1]+field[ix+1][iy-1]+field[ix-1][iy]+field[ix+1][iy]+field[ix-1][iy+1]+field[ix][iy+1]+field[ix+1][iy+1];
      	
        if (field[ix][iy]==0){
        	if (m==3) { field2[ix][iy]=1;}
      	}
      	else{
       		if  ((m==2) || (m==3)){field2[ix][iy]=1;} else { field2[ix][iy]=0;}
      	}
       
      }
      
      /*for (int ix=1;ix<29;ix++){
        for (int iy=1;iy<29;iy++){
          int s;
          s=field[ix-1][iy-1]+field[ix][iy-1]+field[ix+1][iy-1]+field[ix+1][iy]+field[ix+1][iy+1]+field[ix][iy+1]+field[ix-1][iy+1]+field[ix-1][iy];
          if (field[ix][iy]==0){
            if (s==3){field2[ix][iy]=1;}
              else {field2[ix][iy]=0;}
          }
          else{
            if ((s==3) || (s==2)){
              field2[ix][iy]=1;
            }
            else {
              field2[ix][iy]=0;
            }
          }
          for (int ix=0;ix<30;ix++){
            for (int iy=0;iy<30;iy++){
              field[ix][iy]=field2[ix][iy];
            }
          }
         
        }delay(100);
      }*/
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
      for (int ix=1;ix<W-1;ix++) for (int iy=1; iy<W-1;iy++){
		field[ix][iy]=field2[ix][iy];
		//field2[ix][iy]=0;
		}
    //delay(1);
    }

    getch();
    closegraph();
return 0;
}

