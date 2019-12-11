//nUse a Monte-Carlo methodto calculate the value of the mathematical constant π. Pseudocode for this method of solving pie can be found in the book along with more insight on how the algorithm works.

//template:
#include <stdlib.h>

#include <stdio.h>

#include <omp.h>

#include <time.h>

#include <sys/time.h>



// Returns a random value between -1 and 1

double getRand(unsigned int *seed) {


    double r = (double)(rand())/(RAND_MAX);
    //printf("%ld",r);
    return r;

}



double Calculate_Pi_Sequential(long int number_of_tosses) {

    unsigned int seed = (unsigned int) time(NULL);
   double rand_x, rand_y, origin_dist, pi;
    int circle_points = 1, square_points = 0;



   /* initialize random numbers */


   for (long long int i=0; i<number_of_tosses ; i++) {

              rand_x = getRand(seed);
        rand_y = getRand(seed);
        // Distance between (x, y) from the origin
        origin_dist = rand_x * rand_x + rand_y * rand_y;

        // Checking if (x, y) lies inside the define
        // circle with R=1
        if (origin_dist <= 1)
        {
            circle_points++;
        }


        // Total number of points generated
        square_points++;

        // estimated pi after this iteration
        pi = (double)(4 * circle_points) / square_points;

      }



    return pi;



}



double Calculate_Pi_Parallel(long long int number_of_tosses) {

#pragma omp parallel num_threads(omp_get_max_threads())


        unsigned int seed = (unsigned int) time(NULL) + (unsigned int) omp_get_thread_num();



   double rand_x, rand_y, origin_dist, pi;
    int circle_points = 1, square_points = 0;



   /* initialize random numbers */


   for (long long int i=0; i<number_of_tosses ; i++) {

        rand_x = getRand(seed);
        rand_y = getRand(seed);
        // Distance between (x, y) from the origin
        origin_dist = rand_x * rand_x + rand_y * rand_y;

        // Checking if (x, y) lies inside the define
        // circle with R=1
        if (origin_dist <= 1)
        {
            circle_points++;
        }


        // Total number of points generated
        square_points++;

        // estimated pi after this iteration
        pi = (double)(4 * circle_points) / square_points;

      }



    return pi;


}



int main() {

    struct timeval start, end;



    long long int num_tosses = 100000000;



    printf("Timing sequential...\n");

    gettimeofday(&start, NULL);

    double sequential_pi = Calculate_Pi_Sequential(num_tosses);

    gettimeofday(&end, NULL);

    printf("Took %f seconds\n\n", end.tv_sec - start.tv_sec + (double) (end.tv_usec - start.tv_usec) / 1000000);



    printf("Timing parallel...\n");

    gettimeofday(&start, NULL);

    double parallel_pi = Calculate_Pi_Parallel(num_tosses);

    gettimeofday(&end, NULL);

    printf("Took %f seconds\n\n", end.tv_sec - start.tv_sec + (double) (end.tv_usec - start.tv_usec) / 1000000);



    // This will print the result to 10 decimal places

    printf("π = %.10Lf (sequential)\n", sequential_pi);

    printf("π = %.10Lf (parallel)", parallel_pi);



    return 0;

}
