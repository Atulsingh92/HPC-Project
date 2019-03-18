/**************************************************************************************
* FILE: Task1(a+b).cpp
* DESCRIPTION:
* Matrix multiplication using both sequential and Parallel computing(OpenMP) Methods
* AUTHOR:
* Atul Singh      (216100191) ** Ujjwal Verma               (216100297)
* Onkar Jadhav    (216100299) ** Ranjit Arahatholalu Nadish (216100180)
* Sudhanva Kusuma Chandrashekhara   (216100181)
**************************************************************************************/

#include <iostream>
#include <omp.h>

using namespace std;

void seqmulti(int n, int m, int p)                                      //Sequential Matrix multiplication function
{
    int a[n][m],b[m][p],multi[n][p],i,j,k;

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

    for(i=0;i<n;++i)
        {   for(j=0;j<p;++j)
            {   multi[i][j]=0;                                          //Initializing the Multiplication matrix to zero
                for(k=0;k<m;++k)
                {
                    multi[i][j]+=a[i][k]*b[k][j];                       //Multiplying matrix A and B and storing it in matrix multi
                }
            }
        }

    cout<<endl<<"A:"<<endl;

    for(i=0;i<n;++i)
        {   for(j=0;j<m;++j)
            {
                cout<<" "<<a[i][j];                                     //Displaying the matrix a
                if(j==m-1)
                cout<<endl;
            }
        }

    cout<<endl<<"B: "<<endl;

    for(i=0;i<m;++i)
        {   for(j=0;j<p;++j)
            {
                cout<<" "<<b[i][j];                                     //Displaying the matrix b
                if(j==p-1)
                cout<<endl;
            }
        }

    cout<<endl<<"Output Matrix  AB: "<<endl;

    for(i=0;i<n;++i)
        {   for(j=0;j<p;++j)
            {
                cout<<" "<<multi[i][j];                                  //Displaying multiplied matrix
                if(j==p-1)
                cout<<endl;
            }
        }
}

void paramulti(int n, int m, int p)                                     //Parallel matrix multiplication function
{
    int a[n][m],b[m][p],multi[n][p],i,j,k,threads;

    cout<<endl<<"Enter elements of matrix A:"<<endl;

    for(i=0;i<n;++i)
        {   for(j=0;j<m;++j)
            {//
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

    cout<<endl<<"\nMax number of threads used: "<<omp_get_max_threads();//Output the maximum number of threads

    #pragma omp parallel                                                //Output the number of threads available
    threads=omp_get_num_threads();

    cout<<endl<<"\nNumber of threads: "<<threads<<endl;

    #pragma omp parallel for private(j,k) schedule(dynamic)				//OpenMP assigns one iteration to each thread.
        for(i=0;i<n;++i)                                                //When the thread finishes ,it will be assigned with next iteration that
            {   for(j=0;j<p;++j)                                        //hasn't been executed yet
                {   multi[i][j]=0;                                      //Initializing the Multiplication matrix to zero
                    for(k=0;k<m;++k)
                    {
                        multi[i][j]+=a[i][k]*b[k][j];                   //Multiplying matrix A and B and storing it in matrix multi
                    }
                }
            }

    cout<<endl<<"A:"<<endl;

    for(i=0;i<n;++i)
        {   for(j=0;j<m;++j)
            {
                cout<<" "<<a[i][j];                                     //Displaying matrix a
                if(j==m-1)
                cout<<endl;
            }
        }

    cout<<endl<<"B: "<<endl;

    for(i=0;i<m;++i)
        {   for(j=0;j<p;++j)
            {
                cout<<" "<<b[i][j];                                     //Displaying matrix b
                if(j==p-1)
                cout<<endl;
            }
        }

    cout<<endl<<"Output Matrix  AB: "<<endl;

    for(i=0;i<n;++i)
        {   for(j=0;j<p;++j)
            {
                cout<<" "<<multi[i][j];                                  //Displaying multiplied matrix
                if(j==p-1)
                cout<<endl;
            }
        }

}

int main ()
{
	int r1, c1, r2, c2;
	int select,count=1;
    string ch;

    cout<<endl<<"\t\t\t Matrix Multiplication";
    cout<<endl<< "\nEnter rows and columns for first matrix: ";
    cin>>r1>>c1;                                                        //User values for dimensions of the matrix a
    cout<<endl<< "Enter rows and columns for second matrix: ";
    cin>>r2>>c2;                                                        //User values for dimensions of the matrix b

    while (c1!=r2)                                                      //Checking for the dimensions of the two matrices for multiplication
    {                                                                   //If not equal the the user re-enters the value
        cout << "Error! column of first matrix not equal to row of second.";
        cout << "Enter rows and columns for first matrix: ";
        cin>> r1 >> c1;
        cout << "Enter rows and columns for second matrix: ";
        cin >> r2 >> c2;
    }


    do
        {
            cout<<endl<<endl<<"Select your option:";                    //Choosing between sequential and parallel program
            cout<<endl<<"1. Sequential Matrix Multiplication"<<"\t 2.Parallely Multiply Matrix (OpenMP)"<<endl<<"Else Press 0 to exit"<<endl<<" Choose : ";
            cin>>select;

            switch (select)                                             //Switch case for menu selection

            {
                case 1 :    cout<<endl<<"Using Sequential Matrix Multiplication"<<endl;

                            seqmulti(r1,c1,c2);                         //Sequential function call for multiplication

                            break;

                case 2 :    cout<<endl<<"Use Parallel Matrix Multiplication"<<endl;

                            paramulti(r1,c1,c2);                        //Parallel function call for multiplication

                            break;

                case 0 :    break;

                default :   cout<<"Invalid selection... Press 0 to exit" << endl;

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
        }while (select!=0);

    return 0;

}


