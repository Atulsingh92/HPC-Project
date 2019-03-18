/**************************************************************************************
* FILE: Task4(a+b).cpp
* DESCRIPTION:
* Filling a larger matrix with random numbers both sequentially and  parallely and
* creating heatmap of the generated matrix using R.
* AUTHOR:
* Atul Singh      (216100191) ** Ujjwal Verma               (216100297)
* Onkar Jadhav    (216100299) ** Ranjit Arahatholalu Nadish (216100180)
* Sudhanva Kusuma Chandrashekhara   (216100181)
**************************************************************************************/
#include <iostream>
#include<cstdlib>
#include<unistd.h>
#include<omp.h>
#include<fstream>
#include<windows.h>
#include<ctime>

using namespace std;

void seqrand()                                                  //Sequential heatmap generation function
{   const int s=1000;
    srand(time(0));                                             //Seeding for generating pseudo random numbers, Seeded with distinctive runtime value
	static int mat[s][s];
	int i,j;
	string ch,ch2;
	for (i=0;i<s;++i)
    {
        for(j=0;j<s;j++)
		{
		    mat[i][j]=rand();                                   //Storing randomly generated elements in matrix
        }
    }

    ofstream fout("seq.csv");                                   //Opening an output stream for file seq.csv

    if(fout.is_open())                                          //checking whether file could be opened or not.
	{
	    cout<<endl<<"File Opened successfully!!!. Writing data from array to file"<<endl;

		for (i=0;i<s;++i)
        {
            for(j=0;j<s;j++)
            {
                fout<<mat[i][j]<<",";                           //writing matrix element array in the file
                if(j==s-1)
                fout<<endl;
            }
        }

        cout<<endl<<"Array data successfully saved into the file seq.csv"<<endl;
	}

	else                                                        //file could not be opened

	{

		cout <<endl<< "File could not be opened." << endl;

	}

    cout<<endl<<"Create heatmap?  (y/n): ";

    cin>>ch;

	if(ch=="y"||ch=="Y")                                        //Asking to create a heatmap using R
        {
            ShellExecuteA(0,"open",".\\seq_heatmap.R",NULL,NULL,SW_SHOW); //Starting the Rscript in Rscript shell

            sleep(6);

            cout<<endl<<"Heat map Created...";

            cout<<endl<<"View the heatmap in a separate window as .TIFF file?  (y/n): ";

            cin>>ch2;

            if(ch2=="y"||ch2=="Y")                              //Asking to open the created heatmap
                {
                    ShellExecuteA(0,"open",".\\seq_heatmap.tiff",NULL,NULL,SW_SHOW); //Opening the created high resolution heatmap using shell

                    sleep(2);
                }

            else
                {
                   return;
                }
        }
    else
        {
            return;
        }

}

void pararand()                                                 //Parallel heatmap generation function
{   const int s=1000;
    srand(time(0));                                             //Seeding for generating pseudo random numbers, Seeded with distinctive runtime value
	static int mat[s][s];
	int i,j,threads;
	string ch,ch2;

    cout<<endl<<"\nMax number of threads used: "<<omp_get_max_threads();//Output the maximum number of threads

    #pragma omp parallel                                                //Output the number of threads available
    threads=omp_get_num_threads();

    cout<<endl<<"\nNumber of threads: "<<threads<<endl;

	#pragma omp                                                 //Setting up an omp region
	{
		#pragma omp prallel for                                 //Setting up parallel region and worksharing among threads
        for (i=0;i<s;++i)
        {
            for(j=0;j<s;j++)
            {
                mat[i][j]=rand();                               //Storing randomly generated elements in matrix
            }

        }
        #pragma omp barrier                                     //Barrier assures multi matrix to complete multiplication first by each of the threads,
                                                                //before starting addition
        ofstream fout("para.csv");                              //Opening an output stream for file para.csv

        if(fout.is_open())                                      //checking whether file could be opened or not.

        {
            cout<<endl<<"File Opened successfully!!!. Writing data from array to file"<<endl;

            for (i=0;i<s;++i)
            {
                for(j=0;j<s;j++)
                {
                    fout<<mat[i][j]<<",";                       //writing matrix element array in the file
                    if(j==s-1)
                    fout<<endl;
                }
            }

            cout<<endl<<"Array data successfully saved into the file para.csv"<<endl;
        }

        else                                                    //file could not be opened

        {

            cout<<endl<<"File could not be opened."<<endl;

        }

        cout<<endl<<"Create heatmap?  (y/n): ";

        cin>>ch;

        if(ch=="y"||ch=="Y")                                    //Asking to create a heatmap using R
            {
                ShellExecuteA(0,"open",".\\para_heatmap.R",NULL,NULL,SW_SHOW); //Starting the Rscript in Rscript shell

                sleep(6);

                cout<<endl<<"Heat map Created...";

                cout<<endl<<"View the heatmap in a separate window as .TIFF file?  (y/n): ";

                cin>>ch2;

                if(ch2=="y"||ch2=="Y")                          //Asking to open the created heatmap
                    {
                        ShellExecuteA(0,"open",".\\para_heatmap.tiff",NULL,NULL,SW_SHOW); //Opening the created high resolution heatmap using shell

                        sleep(2);
                    }
                else
                {
                    return;
                }
            }

        else
            {
                return;
            }
	}
}
int main ()
{
	int select,count=1;;
    string ch;
    cout<<endl<<"\t\t\tRandom Matrix Generation";

    do
        {
            cout<<endl<<endl<<"Select your option: ";           //Choosing between sequential and parallel program
            cout<<endl<<"1. Sequential Allocation"<<"\t 2.Parallel Allocation (OpenMP)"<<endl<<"Else Press 0 to exit"<<endl<<" Choose : ";
            cin>>select;
            count++;
            switch (select)                                     //Switch case for menu selection

            {
                case 1 :    cout<<endl<<"Allocating Sequentially..."<<endl;

                            seqrand();                          //Sequential function call

                            break;

                case 2 :    cout<<endl<<"Allocating Parallely..."<<endl;

                            pararand();                         //Parallel function call

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
