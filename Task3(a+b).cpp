/**************************************************************************************
* FILE: Task3(a+b).cpp
* DESCRIPTION:
* Random number generator - Fill a n×m matrix with uniformly distributed random numbers
* using both sequential and OpenMP.
* AUTHOR:
* Atul Singh      (216100191) ** Ujjwal Verma               (216100297)
* Onkar Jadhav    (216100299) ** Ranjit Arahatholalu Nadish (216100180)
* Sudhanva Kusuma Chandrashekhara   (216100181)
**************************************************************************************/
#include <iostream>
#include<cstdlib>
#include<omp.h>

using namespace std;

double randomgenerator()                                        //Returns a random number between 0 and 1
{
	double x;
   	x=rand()/double(RAND_MAX);	                                //Rand_MAX value depends on library,
   	return x;                                                   //but is always less than 32767 on any standard library usage
}

double randomgenerator(double a, double b)                      //Returns a random number between the passed parameters
{
	 double t;
     t=(b-a)*randomgenerator() + a;                             //The values a and b (a>b) are the range in which the numbers are required.
	 return t;
}

void seqrand(int n, int m)                                      //Sequential random matrix generation function
{
    srand(101);									                //The pseudo-random number generator is initialized using the argument passed as seed, here : 101
    double mat[n][m];
    int i,j;
    for (i=0;i<n;++i)
    {
        for(j=0;j<m;j++)
        {
            mat[i][j]=randomgenerator(1.0,0.0);                 //Overloaded function for calling randomgenerator function within specified limit [1,0]
		}
	}

    cout<<endl<<"Randomly generated Matrix:"<<endl;

    for(i=0;i<n;++i)
    {
		for(j=0;j<m;++j)
        {
            cout<<" "<<mat[i][j];                               //Displaying the randomly generated matrix
            if(j==m-1)
            cout<<endl;
        }
    }
}

void pararand(int n,int m)				                        //Parallel random matrix generation function
{
    double mat[n][m];
    int i,j,threads;
    srand(101);                                                 //The pseudo-random number generator is initialized using the argument passed as seed, here : 101

    cout<<endl<<"\nMax number of threads used: "<<omp_get_max_threads();//Output the maximum number of threads

    #pragma omp parallel                                                //Output the number of threads available
    threads=omp_get_num_threads();

    cout<<endl<<"\nNumber of threads: "<<threads<<endl;

    #pragma omp parallel for schedule(dynamic)	                        //(??)Parallel is not used in order to generate same values for sequential and parallel
    for (i=0;i<n;++i)
        {
            for(j=0;j<m;j++)
                {
                    mat[i][j]=randomgenerator(1.0,0.0);         //Overloaded function for calling randomgenerator function within specified limit [1,0]
                }
        }

    cout<<endl<<"Randomly generated Matrix:"<<endl;

    for(i=0;i<n;++i)
        {   for(j=0;j<m;++j)
            {
                cout<<" "<<mat[i][j];                           //Displaying the randomly generated matrix
                if(j==m-1)
                cout<<endl;
            }
        }
}

int main ()
{
    int r1, c1;
    int select,count=1;
    string ch;

    cout<<endl<<"\t\t\t\t Random Matrix Generation";
    cout<<endl<< "\nEnter rows and columns for required random matrix: "; //User values for dimensions of the required random matrix
    cin>>r1>>c1;


    do
        {
            cout<<endl<<endl<<"Select your option:"<<endl;		        //Choosing between sequential and parallel program
            cout<<endl<<"1.Sequential Allocation"<<"\t 2.Parallel Allocation(OpenMP) "<<endl<<"\nElse Press 0 to exit"<<endl<<"Choose : ";
            cin>>select;

            switch (select)                                             //Switch case for menu selection
            {
                case 1 :    cout<<endl<<"Allocating Sequentially...:"<<endl;

                            seqrand(r1,c1);						        //Sequential function call

                            break;

                case 2 :    cout<<endl<<"Allocating Parallely..."<<endl;

                            pararand(r1,c1);					        //Parallel function call

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

        }while (select != 0);

    return 0;
}
