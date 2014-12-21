/*
    rule_basic(Height,Weidth)
    
*/

var ix,iy,W,H;

W=argument0;
H=argument1;

for (ix=0;ix<W;ix++) for (iy=0; iy<H;iy++){
    map[ix,iy]=0
}

hmap[0]=irandom_range(2,H-2)
hmap[W]=irandom_range(2,H-2)

for(ix=0;ix<W;ix++){
hmap[ix]=irandom_range(2,H-2)
iy=hmap[ix]
while iy<H{
map[ix,iy]=1
iy++
} 
}

hmap[0]=H
hmap[W]=H

