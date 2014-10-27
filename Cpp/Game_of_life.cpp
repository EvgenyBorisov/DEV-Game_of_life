#include <graphics.h>
#include <time.h>
//#include <math.h>


int main()  {
    initwindow(200,200);
    int color = 15;
    srand(time(NULL));
    int field[30][30]={0};
    int field2[30][30]={0};



    for (int ix=0;ix<30;ix++){
      for (int iy=0;iy<30;iy++){
        field[ix][iy]=rand()%2*rand()%2;
      }
    }

    while (1){
      //clearviewport();
      for (int ix=0;ix<30;ix++){
        for (int iy=0;iy<30;iy++){
          if (field[ix][iy]==0){
            putpixel(ix,iy,15);
          }
          else{
            putpixel(ix,iy,0);
          }
          
        }
      }

      for (int ix=1;ix<30-1;ix++) for (int iy=1; iy<30-1;iy++){  //Избегание границ
      	int m = field[ix-1][iy-1]+field[ix][iy-1]+field[ix+1][iy-1]+field[ix-1][iy]+field[ix+1][iy]+field[ix-1][iy+1]+field[ix][iy+1]+field[ix+1][iy+1];
      	if (field[ix][iy]==0){
        	if (m==3) { field2[ix][iy]=1;}
      	}
      	else{
       		if  ((m==2) || (m==3)){field2[ix][iy]=1;} else { field2[ix][iy]=0;}
      	}
      }
      for (int ix=1;ix<30-1;ix++) for (int iy=1; iy<30-1;iy++){
		field[ix][iy]=field2[ix][iy];
		field2[ix][iy]=0;
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
    delay(100);
    }

    getch();
    closegraph();
return 0;
}

