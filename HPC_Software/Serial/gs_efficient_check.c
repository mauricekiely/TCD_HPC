// 	MAP55611 - Gauss-Seidel solver for the Laplace equation
//	using xy site ordering for updates (not even-odd!) 
//      	Mike Peardon (mjp@maths.tcd.ie) 

#include <stdio.h>
#include <omp.h>	// Using omp_get_wtime
#include <math.h>	// Using sqrt
#include <stdlib.h>

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

double gauss_seidel_checkerboard(int n, double phi[n+1][n+1]){ 
    double phi_xy_old, diff=0;
    int x,y,p;

   for (x = 1; x < n; x++) {
        for (y = 1 + (x % 2); y < n; y += 2) { 
            phi_xy_old = phi[x][y];
            phi[x][y] = 0.25 * (phi[x+1][y] + phi[x-1][y] + phi[x][y+1] + phi[x][y-1]);
            diff += sqr(phi_xy_old - phi[x][y]);
        }
    }

    // Update odd points
    for (x = 1; x < n; x++) {
        for (y = 1 + ((x + 1) % 2); y < n; y += 2) { 
            phi_xy_old = phi[x][y];
            phi[x][y] = 0.25 * (phi[x+1][y] + phi[x-1][y] + phi[x][y+1] + phi[x][y-1]);
            diff += sqr(phi_xy_old - phi[x][y]);
        }
    }
    diff=sqrt(diff / (double) ((n-1)*(n-1)) ); 
    // fprintf(stderr,"diff=%e\n", diff);	// enable for debugging
    return diff;
}

//   ============================================================
// Print for gnuplot pm3d style - add a blank line between y values
void print_grid_2d(int np, double phi[np][np]) {
    FILE *fp = fopen("plot_data_2d.gp", "w");
    if (fp == NULL) {
        perror("Failed to open file for writing");
        return;
    }

    // Set up the plot for 2D heatmap
    fprintf(fp, "set pm3d map\n"); // Use pm3d for coloring and map for 2D
    fprintf(fp, "set palette defined (0 \"blue\", 1 \"white\", 2 \"red\")\n");
    fprintf(fp, "splot '-' with pm3d\n");

    // Print the data
    for (int y = 0; y < np; y++) {
        for (int x = 0; x < np; x++)
            fprintf(fp, "%d %d %lf\n", x, y, phi[x][y]);
        fprintf(fp, "\n");
    }

    // Close the data block for splot
    fprintf(fp, "e\n");
    fclose(fp);

    // Execute the GNUplot script
    system("gnuplot -persist plot_data_2d.gp");
}

void print_grid_3d(int np, double phi[np][np]) {
    FILE *fp = fopen("plot_data_3d.gp", "w");
    if (fp == NULL) {
        perror("Failed to open file for writing");
        return;
    }

    // Set up the plot for 3D visualization
    fprintf(fp, "set pm3d at s\n");
    fprintf(fp, "set hidden3d\n");
    fprintf(fp, "set style data pm3d\n");
    fprintf(fp, "set style function pm3d\n");
    fprintf(fp, "set ticslevel 0\n");
    fprintf(fp, "splot '-' with pm3d\n");

    // Print the data
    for (int y = 0; y < np; y++) {
        for (int x = 0; x < np; x++)
            fprintf(fp, "%d %d %lf\n", x, y, phi[x][y]);
        fprintf(fp, "\n");
    }

    // Close the data block for splot
    fprintf(fp, "e\n");
    fclose(fp);

    // Execute the GNUplot script
    system("gnuplot -persist plot_data_3d.gp");
}

//   ============================================================

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <size>\n", argv[0]);
        return EXIT_FAILURE;
    }
    int n=atoi(argv[1]);
    int count = 0;
    double time;
    double phi[n+1][n+1]; 

    init_boundaries(n,phi);

    time = omp_get_wtime(); 

    do {
        count++;
    } while (gauss_seidel_checkerboard(n,phi) > 1.0e-10);
    fprintf(stderr,"Time: %lf seconds\nIterations: %d\t%d\n", omp_get_wtime() - time, count, n);

    // print_grid_2d(n+1,phi);
    // print_grid_3d(n+1,phi);

    return 0;
}