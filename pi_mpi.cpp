#include "mpi.h"
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <cstdio>

#define POINTS 1000000

int main(int argc, char *argv[]) {
	int myId = 0;
	int numProcs = 0;
	int nameLen = 0;
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myId);
	MPI_Get_processor_name(processor_name, &nameLen);	
 
	int s  = (int)floor(POINTS/numProcs);
	int s0 = s + POINTS%numProcs;

	double startwtime;

	if (myId == 0) {
		startwtime = MPI_Wtime();
	}

	int i = 0;
	int localCount = 0;
	double x = 0.0f;
	double y = 0.0f;

	srand(time(NULL) + (unsigned)myId);

	if (myId == 0) { // Master
		for (i = 0; i < s0; i++) {
			x = ((double)rand()) / ((double)RAND_MAX);
			y = ((double)rand()) / ((double)RAND_MAX);
			
			if (x*x + y*y <= 1) {
				localCount++;
			}
		}
		printf("Process %d - hit %d times out of %d tries.\n", myId, localCount, s0);
	} else { // Slave
		for (i = 0; i < s; i++) {
			x = ((double)rand()) / ((double)RAND_MAX);
			y = ((double)rand()) / ((double)RAND_MAX);

			if (x*x + y*y <= 1) {
				localCount++;
			}
		}
		printf("Process %d - hit %d times out of %d tries.\n", myId, localCount, s);
	}

	int totalSum = 0;

	MPI_Reduce(&localCount, &totalSum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if (myId == 0) {
		double ratio = double(totalSum)/POINTS;
		double pi = 4.0f * ratio;
		double runTime = MPI_Wtime() - startwtime;
		printf("Execution time (sec) = %f\nTotal points in circle = %d\nEstimated Pi = %f\n", runTime, totalSum, pi);
		printf("Difference between estimated pi and real pi = %f\n", abs(pi-M_PI));
		printf("Percent error for estimated pi = %.5f%\n", (abs(pi-M_PI)/M_PI * 100));
	}

	MPI_Finalize();
	return 0;
}
