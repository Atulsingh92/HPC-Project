/**************************************************************************************
* FILE: Task5(a+b).cpp
* DESCRIPTION:
* Comparing time taken by Large matrix computation (AB+c) between Sequential and Parallel
* operations.
* AUTHOR:
* Atul Singh      (216100191) ** Ujjwal Verma               (216100297)
* Onkar Jadhav    (216100299) ** Ranjit Arahatholalu Nadish (216100180)
* Sudhanva Kusuma Chandrashekhara   (216100181)
**************************************************************************************/
#include <iostream>
#include<cstdlib>
#include<ctime>
#include<omp.h>

using namespace std;

double seqtime()                                            //Sequential Matrix computation function
{   double start=omp_get_wtime();                           //Start timer
    const int n=1000;
    static unsigned int a[n][n],b[n][n],c[n][n];
    static unsigned int multi[n][n],sum[n][n];
    int i,j,k;

    srand(1234);                                            //The pseudo-random number generator initialized with seed, here:1234
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            a[i][j]=rand()%10;                              //Storing random elements in matrix a
            b[i][j]=rand()%10;                              //Storing random elements in matrix b
            c[i][j]=rand()%10;                              //Storing random elements in matrix c
        }
    }

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            multi[i][j]=0;                                  //Initializing the Multiplication matrix to zero
            for(k=0;k<n;k++)
            {
                multi[i][j]=multi[i][j]+a[i][k]*b[k][j];    //Multiplying matrix A and B and storing it in matrix multi
            }
        }
    }

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            sum[i][j]=multi[i][j]+c[i][j];                  //Adding matrix c to matrix multi and storing it in matrix sum
        }
    }

    double end = omp_get_wtime();                           //End timer
    double elapsed;
    elapsed = (end - start);
    return elapsed;                                         //Returning the time taken
}

double paratime()                                           //Parallel Matrix computation function
{   double start=omp_get_wtime();                           //Start timer
    const int n=1000;
    static unsigned int a[n][n],b[n][n],c[n][n];
    static unsigned int multi[n][n],sum[n][n];
    int i,j,k,threads;

    srand(1234);                                            //The pseudo-random number generator initialized with seed, here:1234
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            a[i][j]=rand()%10;                              //Storing random elements in matrix a
            b[i][j]=rand()%10;                              //Storing random elements in matrix b
            c[i][j]=rand()%10;                              //Storing random elements in matrix c
        }
    }

    cout<<endl<<"\nMax number of threads used: "<<omp_get_max_threads();//Output the maximum number of threads

    #pragma omp parallel                                                //Output the number of threads available
    threads=omp_get_num_threads();

    cout<<endl<<"\nNumber of threads: "<<threads<<endl;

    # pragma omp parallel shared (a,b,c) private (i,j,k)    //Each thread allocates a private copy of j and k from storage, within the private execution of each thread
    {                                                       //a,b and c are shared among all threads, modifications on which are updated to the global instance
                                                            //OpenMP assigns one iteration to each thread
        # pragma omp for schedule(dynamic)                  //When the thread finishes ,it will be assigned with next iteration that
        for(i=0;i<n;i++)                                    //hasn't been executed yet
        {
            for(j=0;j<n;j++)
            {
                multi[i][j]=0;                              //Initializing the Multiplication matrix to zero
                for(k=0;k<n;k++)
                {
                    multi[i][j]=multi[i][j]+a[i][k]*b[k][j];//Multiplying matrix A and B and storing it in matrix multi
                }
            }
        }

        #pragma omp for
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                sum[i][j]=multi[i][j]+c[i][j];              //Adding matrix c to matrix multi and storing it in matrix sum
            }
        }

    }

    double end = omp_get_wtime();                           //End timer
    double elapsed;
    elapsed = (end - start);
    return elapsed;                                         //Returning the time taken
}

int main ()
{   double seq_time,para_time;
    string ch;
    cout<<endl<<"\t\t\t Large Martrix (1000x1000) Operation\n"<<endl;
    do{
        cout<<endl<<"\nCalculating Sequentially...";
        seq_time=seqtime();                                 //Sequential function call for computation
        cout<<endl<<"\nThe time taken by Operation Sequentially : "<<seq_time<<"s";
        cout<<endl<<"\n\nCalculating Parallely...";
        para_time=paratime();                               //Parallel function call for computation
        cout<<endl<<"\nThe time taken by Operation Parallely : "<<para_time<<"s";
        float factor=(seq_time/para_time);                  //Computing speed factor
        cout<<endl<<"\n\nThe Parallel process is "<<factor<<" times faster than Sequential"<<endl;
        cout<<endl<<"\nWould you like to re-run the test? (y/n) : ";
        cin>>ch;                                            //Asking for re-running the computation
    }while(ch=="y"||ch=="Y");

    return 0;

}

