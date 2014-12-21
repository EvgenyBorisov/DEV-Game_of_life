/*
    rule_basic(Height,Weidth)
    
*/

var ix,iy,W,H;

W=argument0;
H=argument1;

for (ix=0;ix<W;ix++) for (iy=0; iy<H;iy++){
    map[ix,iy]=0
}

for (ix=1;ix<W;ix++) for (iy=1; iy<H-1;iy++){
    hmap[ix]=median(hmap[ix-1],hmap[ix],hmap[ix+1])
    iy=hmap[ix]
    while iy<H{
    map[ix,iy]=1
    iy++
} 
}








