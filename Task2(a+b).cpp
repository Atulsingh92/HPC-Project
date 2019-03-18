/**************************************************************************************************
* FILE: Task2(a+b).cpp
* DESCRIPTION:
* Matrix multiplication and Summation using both sequential and Parallel computing(OpenMP) Methods
* AUTHOR:
* Atul Singh      (216100191) ** Ujjwal Verma               (216100297)
* Onkar Jadhav    (216100299) ** Ranjit Arahatholalu Nadish (216100180)
* Sudhanva Kusuma Chandrashekhara   (216100181)
**************************************************************************************************/

#include <iostream>
#include <omp.h>

using namespace std;

void seqmultisum(int n, int m, int p)							        //Sequential Matrix multiplication and summation function
{
    int a[n][m],b[m][p],mult[n][p],c[n][p],sum[n][p],i,j,k;

    cout<<endl<<"Enter elements of matrix A:"<<endl;

    for(i=0;i<n;++i)
        {   for(j=0;j<m;++j)
            {
                cout<<"Enter element A"<<i+1<<j+1<<" : ";
                cin>>a[i][j];                                           //Storing elements in matrix a
            }
        }

    cout<<endl<<"Enter elements of matrix B:"<<endl;

    for(i=0;i<m;++i)
        {   for(j=0;j<p;++j)
            {
                cout<<"Enter element B"<<i+1<<j+1<<" : ";
                cin>>b[i][j];                                           //Storing elements in matrix b
            }
        }

    cout<<endl<<"Enter elements of matrix C:"<<endl;

    for(i=0;i<n;++i)
        {   for(j=0;j<p;++j)
            {
                cout<<"Enter element C"<<i+1<<j+1<<" : ";
                cin>>c[i][j];                                           //storing elements in matrix c
            }
        }

     for(i = 0; i < n; ++i)
            {   for(j = 0; j < p; ++j)							        //Initializing the Multiplication matrix to zero
                {   mult[i][j]=0;
                    for(k=0;k<m;++k)
                    {
                        mult[i][j]+=a[i][k]*b[k][j];			        //Multiplying matrix A and B and storing it in matrix mult

                    }
                    sum[i][j]=mult[i][j]+c[i][j];				        //Adding matrix c to matrix mult and storing it in matrix sum
                }

            }

    cout<<endl<<"A:"<<endl;

    for(i=0;i<n;++i)
        {   for(j=0;j<m;++j)
            {
                cout<<" "<<a[i][j];							            //Displaying matrix a
                if(j==m-1)
                cout<<endl;
            }
        }

    cout<<endl<<"B: "<<endl;

    for(i=0;i<m;++i)
        {   for(j=0;j<p;++j)
            {
                cout<<" "<<b[i][j];							            //Displaying matrix b
                if(j==p-1)
                cout<<endl;
            }
        }


    cout<<endl<<"C: "<<endl;

    for(i=0;i<n;++i)
        {   for(j=0;j<p;++j)
            {
                cout<<" "<<c[i][j];							            //Displaying matrix c
                if(j==p-1)
                cout<<endl;
            }
        }

    cout<<endl<<"Output Matrix  AB: "<<endl;

    for(i=0;i<n;++i)
        {   for(j=0;j<p;++j)
            {
                cout<<" "<<mult[i][j];					                //Displaying multiplied matrix
                if(j==p-1)
                cout<<endl;
            }
        }

    cout<<endl<<"Output Matrix  AB+C: "<<endl;

    for(i=0;i<n;++i)
        {   for(j=0;j<p;++j)
            {
                cout<<" "<<sum[i][j];				                    //Displaying summed matrix
                if(j==p-1)
                cout<<endl;
            }
        }



}

void paramultisum(int n, int m, int p)					                //Parallel Matrix multiplication and summation function
{
    int a[n][m],b[m][p],multi[n][p],c[n][p],sum[n][p],i,j,k,threads;

    cout<<endl<<"Enter elements of matrix A:"<<endl;

    for(i=0;i<n;++i)
        {   for(j=0;j<m;++j)
            {
                cout<<"Enter element A"<<i+1<<j+1<<" : ";
                cin>>a[i][j];                                           //Storing elements in matrix a
            }
        }

    cout<<endl<<"Enter elements of matrix B:"<<endl;

    for(i=0;i<m;++i)
        {   for(j=0;j<p;++j)
            {
                cout<<"Enter element B"<<i+1<<j+1<<" : ";
                cin>>b[i][j];                                           //Storing elements in matrix b
            }
        }

    cout<<endl<<"Enter elements of matrix C:"<<endl;

    for(i=0;i<n;++i)
        {   for(j=0;j<p;++j)
            {
                cout<<"Enter element C"<<i+1<<j+1<<" : ";
                cin>>c[i][j];                                           //Storing elements in matrix c
            }
        }

    cout<<endl<<"\nMax number of threads used: "<<omp_get_max_threads();//Output the maximum number of threads

    #pragma omp parallel                                                //Output the number of threads available
    threads=omp_get_num_threads();

    cout<<endl<<"\nNumber of threads: "<<threads<<endl;

    # pragma omp parallel private (j,k) shared(a,b,c,multi)		        //Each thread allocates a private copy of j and k from storage, within the private execution of each thread
	{															        //a,b,c and multi are shared among all threads, modifications on which are updated to the global instance
        # pragma omp for schedule(dynamic)						        //OpenMP assigns one iteration to each thread
			for(i=0;i<n;i++)									        //When the thread finishes ,it will be assigned with next iteration that
        	{													        //hasn't been executed yet
            for(j=0;j<p;j++)
            {
               multi[i][j]=0;						                    //Initializing the Multiplication matrix to zero
                for(k=0;k<m;k++)
                {
                    multi[i][j]=multi[i][j]+a[i][k]*b[k][j];
                }
            }
        	}

        #pragma omp barrier                                             //Barrier assures multi matrix to complete multiplication first by each of the threads,
        #pragma omp for	                                                //before starting addition
        for(i=0;i<n;i++)
        {
            for(j=0;j<p;j++)
            {
                sum[i][j]=multi[i][j]+c[i][j];			                //Adding matrix c to matrix mult and storing it in matrix sum
            }
        }

    }

    cout<<endl<<"A:"<<endl;

    for(i=0;i<n;++i)
        {   for(j=0;j<m;++j)
            {
                cout<<" "<<a[i][j];						                //Displaying matrix a
                if(j==m-1)
                cout<<endl;
            }
        }

    cout<<endl<<"B: "<<endl;

    for(i=0;i<m;++i)
        {   for(j=0;j<p;++j)
            {
                cout<<" "<<b[i][j];						                //Displaying matrix b
                if(j==p-1)
                cout<<endl;
            }
        }


    cout<<endl<<"C: "<<endl;

    for(i=0;i<n;++i)
        {   for(j=0;j<p;++j)
            {
                cout<<" "<<c[i][j];                                     //Displaying matrix c
                if(j==p-1)
                cout<<endl;
            }
        }

    cout<<endl<<"Output Matrix  AB: "<<endl;

    for(i=0;i<n;++i)
        {   for(j=0;j<p;++j)
            {
                cout<<" "<<multi[i][j];                                 //Displaying multiplied matrix
                if(j==p-1)
                cout<<endl;
            }
        }

    cout<<endl<<"Output Matrix  AB+C: "<<endl;

    for(i=0;i<n;++i)
        {   for(j=0;j<p;++j)
            {
                cout<<" "<<sum[i][j];                                   //Displaying summed matrix
                if(j==p-1)
                cout<<endl;
            }
        }
}

int main ()
{
    int r1, c1, r2, c2, row3, col3;
    int select,count=1;
    string ch;

    cout<<endl<<"\t\t\t Multiplication and Summation ";
    cout<<endl<<"\nEnter rows and columns for first matrix: ";			//User values for dimensions of the matrix a
    cin>>r1>>c1;
    cout<<endl<<"Enter rows and columns for second matrix: ";			//User values for dimensions of the matrix b
    cin>>r2>>c2;
    cout<<endl<<"Enter rows and columns for third matrix: ";			//User values for dimensions of the matrix c
    cin>>row3>>col3;

    while (c1!=r2)											            //Checking for the dimensions of the two matrices for multiplication
    {                                                                   //If not equal the the user re-enters the value
        cout<<endl<<"Error! column of first matrix not equal to row of second.";
        cout<<endl<<"Enter rows and columns for first matrix: ";
        cin>>r1>>c1;
        cout<<"Enter rows and columns for second matrix: ";
        cin>>r2>>c2;
    }

     while ((c2!=col3)||(r1!=row3))						                //Checking for the dimensions of the c matrix with multiplied matrix for summation
    {
        cout<<endl<<"Error! Size of Summation matrix is not equal to the Multiplied matrix";
        cout<<endl<<"Enter rows and columns for third matrix: ";
        cin>>row3>>col3;
    }


    do
        {
            cout<<endl<<endl<<"Select your option:";                    //Choosing between sequential and parallel program
            cout<<endl<<"1. Sequential Multiplication and Summation"<<"\t 2.Parallely Multiplication and Summation (OpenMP)"<<endl<<"\nElse Press 0 to exit"<<endl<<"Choose : ";
            cin>>select;

            switch (select)                                             //Switch case for menu selection

            {
                case 1 :    cout<<endl<<"Using Sequential Matrix Multiplication"<<endl;

                            seqmultisum(r1,c1,c2);				        //Sequential function call for multiplication then summation

                            break;

                case 2 :    cout<<endl<<"Use Parallel Matrix Multiplication"<<endl;

                            paramultisum(r1,c1,c2);				        //Parallel function call for multiplication then summation

                            break;

                case 0 :    break;

                default : cout<<"Invalid selection" << endl;

            }
            if(count>=2)                                               //After 2 function call asking user to Exit
            {
                cout<<endl<<"\nExit?? (y/n): ";
                cin>>ch;
                if(ch=="y"||ch=="Y")
                    break;
                else
                    continue;
            }
            count++;

        }while (select != 0);

    return 0;

}
