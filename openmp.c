// Created by Gavin Grossman & Spencer Bao on 4/30/20.

#include <omp.h>
#include <stdlib.h>
#include <stdio.h>

int total_points = 0;

int randSample() {
    int r = (rand() % (1000000 + 1 - 500000) + 500000);
    total_points += r;
    return r;
}

int compute_pi(){
    int hits = 0;
    int points_per_thread = randSample();
    double x_coord, y_coord;
    for (int i = 0; i < points_per_thread; i++){
        x_coord = (double) rand() / (RAND_MAX) - 0.5;
        y_coord = (double) rand() / (RAND_MAX) - 0.5;
        if ((x_coord * x_coord + y_coord * y_coord) < 0.25){
            hits++;
        }
    }
    return hits;
}

int main(){

    double total_hits = 0.0;
    int threads; 
    #pragma omp parallel reduction(+:total_hits)
    {
        threads = omp_get_num_threads();
        total_hits += compute_pi();
    }
    printf("%lf\n", 4*total_hits/(total_points));

    return 0;
}
