/*
    rule_life(Height,Weidth)
    
*/

var ix,iy,W,H,m;

W=argument0;
H=argument1;

for (ix=1;ix<W-1;ix++) for (iy=1; iy<H-1;iy++){  //Избегание границ
      m=map[ix-1,iy-1]+map[ix,iy-1]+map[ix+1,iy-1]+map[ix-1,iy]+map[ix+1,iy]+map[ix-1,iy+1]+map[ix,iy+1]+map[ix+1,iy+1]
      if map[ix,iy]=0{
         if m=3 { temp_map[ix,iy]=1}
      }
      else{
       if  (m=2 or m=3){temp_map[ix,iy]=1} else { temp_map[ix,iy]=0}
      }
      
}

for (ix=1;ix<W-1;ix++) for (iy=1; iy<H-1;iy++){
map[ix,iy]=temp_map[ix,iy]
temp_map[ix,iy]=0
}

