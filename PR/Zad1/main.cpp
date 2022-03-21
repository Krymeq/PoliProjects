#include <stdio.h>
#include <time.h>
#include <omp.h>
#include <math.h> 
#include <vector>
#include <string>

typedef uint32_t u32;
using namespace std;

#pragma region Number filter method
vector<u32> find_primes_con1_seq(u32 n, u32 m) {
	double tstart, tend;
	tstart = omp_get_wtime();

	vector<u32> primes;
	for (u32 i = n; i <= m; i++) {
		u32 j = 2;
		bool had_div = false;
		while (j <= sqrt(i)) {
			if (i % j == 0) {
				had_div = true;
				break;
			}
			j++;
		}
		if (!had_div)primes.push_back(i);
	}

	tend = omp_get_wtime();
	printf("Con1 Seq: %f seconds\n", ((double)(tend - tstart)));

	return primes;
}
vector<u32> find_primes_con1_par_ver1(u32 n, u32 m) {
	double tstart, tend;
	tstart = omp_get_wtime();
	vector<u32> primes;
	omp_set_num_threads(8);
	#pragma omp parallel
	{
		#pragma omp for
		for (int i = n; i <= m; i++) {
			u32 j = 2;
			bool had_div = false;
			while (j <= sqrt(i)) {
				if (i % j == 0) {
					had_div = true;
					break;
				}
				j++;
			}
			# pragma omp critical
			if (!had_div)primes.push_back(i);
		}

	
	}
	tend = omp_get_wtime();
	printf("Con1 Par V1: %f seconds\n", ((double)(tend - tstart)));
	return primes;
}
vector<u32> find_primes_con1_par_ver2(u32 n, u32 m) {
	double tstart, tend;
	tstart = omp_get_wtime();
	vector<u32> primes;
	omp_set_num_threads(8);
	#pragma omp parallel
	{
	vector<u32> local_primes;
	#pragma omp for
		for (int i = n; i <= m; i++) {
			u32 j = 2;
			bool had_div = false;
			while (j <= sqrt(i)) {
				if (i % j == 0) {
					had_div = true;
					break;
				}
				j++;
			}
			if (!had_div)local_primes.push_back(i);
		}
		#pragma omp critical
		{
			for (int i = 0; i < local_primes.size(); i++) {
				primes.push_back(local_primes[i]);
			}

		}
	}
	tend = omp_get_wtime();
	printf("Con1 Par V2: %f seconds\n", ((double)(tend - tstart)));
	return primes;
}
#pragma endregion

#pragma region Sieve method

#pragma endregion


int main(int argc, char* argv[])
{	

	/*long long num_steps = 100000000;
	double step;
	clock_t start, stop;
	double x, pi, sum = 0.0;
	volatile double tab[52];
	int i;
	omp_set_num_threads(2);
	step = 1. / (double)num_steps;
	for (int j = 0; j < 50; j++) {
		tab[j] = 0.0;
		tab[j + 1] = 0.0;
		start = clock();
		#pragma omp parallel
		{
			#pragma omp for private(x)
			for (i = 0; i < num_steps; i++) {
				x = (i + 0.5) * step;
				tab[j + omp_get_thread_num()] += 4.0 / (1.0 + x * x);
			}
			pi = tab[j] * step;
			stop = clock();
			printf("iteracja: %d, %f sekund\n", j, ((double)(stop - start) / 1000.0));
		}
	}
	printf("Wartosc liczby PI wynosi %15.12f\n", pi);*/

	u32 n = 2;
	u32 m = 90000000;
	
	vector<u32> primes;
	primes = find_primes_con1_seq(n, m);
	primes = find_primes_con1_par_ver1(n, m);
	primes = find_primes_con1_par_ver2(n, m);
	
	/*for (int i = 0; i < primes.size(); i++) {
		printf("%d\n",primes[i]);
	}*/


	return 0;
}