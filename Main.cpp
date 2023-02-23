#include<math.h>
#include<mpi.h>

int main(int argc, char *argv[]) {
	int myId;
	int numProcs;
	int count;
	int sum;
	long points = 10000;
	double x;
	double y;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myId);

	srand((unsigned)(myId));

	if (myId == 0) { // Master
		x = ((double)rand()) / ((double)RAND_MAX);
		y = ((double)rand()) / ((double)RAND_MAX);
		
		if (x*x + y*y <= 1) {
		
		}
	} else { // Slave
		x = ((double)rand()) / ((double)RAND_MAX);
		y = ((double)rand()) / ((double)RAND_MAX);

		if (x*x + y*y <= 1) {
		
		}
	}

	sum = MPI.Reduce();

	MPI_Finalize();
	return 0;
}
