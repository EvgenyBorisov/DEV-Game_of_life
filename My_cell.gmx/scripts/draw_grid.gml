//draw_grid(x,y,w,h,d)
var gx,gy,gw,gh,d,i,n_cx,n_cy;
gx=argument0;
gy=argument1;
gw=argument2;
gh=argument3;
d=argument4;

n_cx=floor(gw/d)
n_cy=floor(gh/d)

for(i=0;i<n_cx;i++){  //рисуем вертикальные линии
draw_line(gx+i*d,gy,gx+i*d,gy+gh)
}
for(i=0;i<n_cy;i++){  //рисуем горизонтальные линии
draw_line(gx,gy+i*d,gx+gw,gy+i*d)
}
