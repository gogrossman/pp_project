#include <omp.h>
#include <stdlib.h>
#include <stdio.h>

int points_per_thread = 20;
int threads = 2;

int compute_pi(){
    int hits;
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
    
    double total_hits;

    #pragma omp parallel num_threads(threads) reduction(+:total_hits)
    {
        total_hits += compute_pi();
    }

    printf("%lf\n", 4*total_hits/(points_per_thread*threads));

    return 0;
}
