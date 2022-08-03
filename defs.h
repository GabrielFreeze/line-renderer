#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define W 32
#define H 32
#define D 32


typedef struct point_ {
    float x,y,z;
} point;

bool grid[W*H] = {};

void set(float x, float y) {
    
    if (!(x < 0 || x > W || y < 0 || y > H))
        grid[(int)(x+y*W)] = true;
        
}
bool get(float x, float y) {
    
    if (!(x < 0 || x > W || y < 0 || y > H))
        return grid[(int)(x+y*W)];

    return false;
}


void reset() {
    //Reset previous drawing;
    memset(grid, 0, sizeof(grid));
}

void draw_lineY(point p1, point p2) {

    float error = 0;
    float slope = fabs((float)(p2.x - p1.x)/(p2.y - p1.y));
    
    point start,end;

    if (p1.y < p2.y) {
        start=p1;
        end=p2;
    } else {
        start=p2;
        end=p1;
    }


    bool dir = start.x < end.x;
    int x = start.x;

    //Draw Initial Point
    set(start.x,start.y);


    for (int y = start.y+1; y <= end.y; y++) {

        error += slope;

        // Proceed to the next cell?
        if (error > 0.5) {
            x += dir? 1:-1;
            error--;
        }

        set(x,y);

    }

    return;


}

void draw_lineX(point p1, point p2) {

    float error = 0;
    float slope = fabs((float)(p2.y - p1.y)/(p2.x - p1.x));
    
    point start,end;

    if (p1.x < p2.x) {
        start=p1;
        end=p2;
    } else {
        start=p2;
        end=p1;
    }


    bool dir = start.y < end.y;
    int y = start.y;


    //Draw Initial Point
    set(start.x, start.y);

    for (int x = start.x+1; x <= end.x; x++) {
        error += slope;

        // Proceed to the next cell?
        if (error > 0.5) {
            y += dir? 1:-1;
            error--;
        }

        set(x,y);

    }

    return;
}

void draw_line(point p1, point p2) {

    p1.x = (int) p1.x;
    p1.y = (int) p1.y;
    p2.x = (int) p2.x;
    p2.y = (int) p2.y;

    if (abs(p2.x - p1.x) < abs(p2.y - p1.y)) {
        return draw_lineY(p1,p2);
    }

    return draw_lineX(p1,p2);

}

point rotate(point p, float theta) {
    
    //Rotate around origin

    float x = round((float)(p.x-(W/2))*cos(theta) - (float)(p.y-(H/2))*sin(theta));
    float y = round((float)(p.y-(H/2))*cos(theta) + (float)(p.x-(W/2))*sin(theta));
    
    return {x+(W/2),y+(H/2)};
    
}

point rotateX(point p, float theta) {
    
    //Rotate around origin

   float x = (float)(p.x-(W/2));
   float y = (float)(p.y-(H/2))*cos(theta) - (float)(p.z-(D/2))*sin(theta);
   float z = (float)(p.y-(H/2))*sin(theta) + (float)(p.z-(D/2))*cos(theta);

    return {x+(W/2),y+(H/2),z+(D/2)};
    
}

point rotateY(point p, float theta) {
    
    //Rotate around origin

   float x = (float)(p.x-(W/2))*cos(theta) + (float)(p.z-(D/2))*sin(theta);
   float y = (float)(p.y-(H/2));
   float z = (float)(p.z-(D/2))*cos(theta) - (float)(p.x-(W/2))*sin(theta);
    
    return {x+(W/2),y+(H/2),z+(D/2)};
}

point rotateZ(point p, float theta) {
    
    //Rotate around origin

   float x = (float)(p.x-(W/2))*cos(theta) + (float)(p.y-(H/2))*sin(theta);
   float y = (float)(p.y-(H/2))*cos(theta) - (float)(p.x-(W/2))*sin(theta);
   float z = (float)(p.z-(D/2));
    
    return {x+(W/2),y+(H/2),z+(D/2)};
}


