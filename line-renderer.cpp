#include <stdio.h>
#include <time.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "defs.h"

#define N 26

void display_grid() {

    for (int y=0; y<H; y+=2) {
        for (int x=0; x<W; x+=1) {

            unsigned char a = grid[x+y*W];
            unsigned char b = grid[x+(y+1)*W];
            putc(" _^|"[((a<<1)|b)], stdout);
            // putc(" ###"[((a<<1)|b)], stdout);
        }
        putc('\n',stdout);
    }

}

int main() {
    
    system("clear");
    float theta = 0;
    
    //Pyramid
    // point shape[N] = {{0,0,0},{1,0,0},{1,0,1},{0,0,1},{0,0,0},{0,0,1},{0.5,1,0.5},{1,0,0},{1,0,1},{0.5,1,0.5},{0,0,0}};


    //Cube
    point shape[N] = {{0,0,0},{0,0,1},{1,0,1},{1,0,0},{0,0,0},{0,1,0},{0,1,1},{0,0,1},{0,0,0},{1,0,0},{1,1,0},{0,1,0}
    ,{0,0,0},{0,0,1},{1,0,1},{1,1,1},{0,1,1},{0,0,1},{1,0,1},{1,1,1},{1,1,0},{1,0,0},{1,0,1},{1,0,0},{1,1,0},{0,1,0}};


    //Scale by factor
    for (int i=0;i<N;i++) shape[i].x *= 20;
    for (int i=0;i<N;i++) shape[i].y *= 20;
    for (int i=0;i<N;i++) shape[i].z *= 20;

    //Cente on (0,0,0)
    for (int i=0;i<N;i++) shape[i].x -= 10;
    for (int i=0;i<N;i++) shape[i].y -= 10;
    for (int i=0;i<N;i++) shape[i].z -= 10;
    

    //Center in middle of grid
    for (int i=0;i<N;i++) shape[i].x += W/2;
    for (int i=0;i<N;i++) shape[i].y += H/2;
    for (int i=0;i<N;i++) shape[i].z += D/2;

    // for (int i=0;i<N;i++) printf("%d %d \n",shape[i].x,shape[i].y);
    
    //Initial skew
    for (int i=0;i<N;i++) shape[i] = rotateX(shape[i],M_PI/16);
    for (int i=0;i<N;i++) shape[i] = rotateY(shape[i],M_PI/16);
    for (int i=0;i<N;i++) shape[i] = rotateZ(shape[i],M_PI/16);
    
    while (true) {
        
        reset();

        //Rotate
        for (int i=0;i<N;i++) shape[i] = rotateX(shape[i],M_PI/96);
        for (int i=0;i<N;i++) shape[i] = rotateY(shape[i],M_PI/72);
        for (int i=0;i<N;i++) shape[i] = rotateZ(shape[i],M_PI/48);
        
        //Draw line
        for (int i=0;i<N;i++) draw_line(shape[i],shape[(i+1)%N]);


        //Display
        display_grid();
        
        usleep(50000);
        printf("\x1b[H");
    }





    return 0;
}