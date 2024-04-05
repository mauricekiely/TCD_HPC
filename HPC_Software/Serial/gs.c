// 	MAP55611 - Gauss-Seidel solver for the Laplace equation
//	using xy site ordering for updates (not even-odd!) 
//      	Mike Peardon (mjp@maths.tcd.ie) 

#include <stdio.h>
#include <omp.h>	// Using omp_get_wtime
#include <math.h>	// Using sqrt

//   ============================================================
void init_boundaries(int n, double phi[n+1][n+1])
{
  int x,y;

  for (y=0;y<=n;y++) {
    for (x=0;x<=n;x++) {
        phi[x][y] = 0.0;
    }
  }

  for (y=0;y<=n;y++) {
    phi[0][y] = 1.0; 
  }
  for (x=0;x<=n;x++) {
    phi[x][0] =-1.0; 
  }
}

//   ============================================================

double sqr(double x) { 
    return x*x; 
} 

double gauss_seidel(int n, double phi[n+1][n+1]){ 
    double phi_xy_old, diff=0;
    int x,y,p;

    for (x=1;x<n;x++) 
    {
        for (y=1;y<n;y++)   
        {
        phi_xy_old = phi[x][y]; 
        phi[x][y] = 0.25 * (phi[x+1][y]  +  phi[x-1][y]  +  phi[x][y+1] +  phi[x][y-1]);
        diff += sqr(phi_xy_old - phi[x][y]); 
        }
    }
    diff=sqrt(diff / (double) ((n-1)*(n-1)) ); 
    // fprintf(stderr,"diff=%e\n", diff);	// enable for debugging
    return diff;
}

//   ============================================================
// Print for gnuplot pm3d style - add a blank line between y values
void print_grid(int np, double phi[np][np])
{
  int x,y; 
  for (y=0;y<np;y++)
  {
    for (x=0;x<np;x++)
      printf("%d %d %lf\n",x,y,phi[x][y]);
    printf("\n");
  }
}

//   ============================================================

int main()
{
  int n=250;
  double time;
  double phi[n+1][n+1]; 

  init_boundaries(n,phi);

  time = omp_get_wtime(); 
  do {} while (gauss_seidel(n,phi) > 1.0e-10);
  fprintf(stderr,"Time: %lf seconds\n", omp_get_wtime() - time); 

  //print_grid(n+1,phi);

  return 0;
}