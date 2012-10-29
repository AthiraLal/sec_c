#include<stdio.h>

#define true 1
#define false 0

int no_prcs,no_resrc,i,j,count=0,process,s=0,prcs;
int maximum[10][10],allocated[10][10],need[10][10],max_resrc[10],available[10],finish[10], work[10],safe_state[10],reqrd[10];

void readtable(int t[10][10])
{
    for(i=0;i<no_prcs;i++)
        for(j=0;j<no_resrc;j++)
            scanf("%d",&t[i][j]);   
}

void printtable(int t[10][10])
{
    for(i=0;i<no_prcs;i++)
    {
        for(j=0;j<no_resrc;j++)
            printf("\t%d",t[i][j]);   
        printf("\n");
    }
}

void readvector(int v[10])
{
    for(j=0;j<no_resrc;j++)
        scanf("%d",&v[j]);   
}

void printvector(int v[10])
{
    for(j=0;j<no_resrc;j++)
        printf("\t%d",v[j]);   
}

void proc_need()
{
    for(i=0;i<no_prcs;i++)
    {
        for(j=0;j<no_resrc;j++)   
        {
            need[i][j]=maximum[i][j]-allocated[i][j];
        }

    }

    for(i=0;i<no_prcs;i++)
    {
        for(j=0;j<no_resrc;j++)   
        {
            printf("\t %d", need[i][j]);

        }
        printf ("\n");

    }
}


void findavail()
{
    int sum;
    for(j=0;j<no_resrc;j++)
    {
        sum=0;
        for(i=0;i<no_prcs;i++)   
        {
            sum=sum+allocated[i][j];
        }
        available[j]=max_resrc[j]-sum;
    }
}



void init()
{
    printf("Enter the total number of process :\n");
    scanf("%d",&no_prcs);
    printf("Enter the total number of resources :\n");
    scanf("%d",&no_resrc);
    printf("Enter the maximum units of each resource for each of %d resources) :\n", no_resrc);
    readvector(max_resrc);
    printf("Enter the maximum resources needed by each of the %d processes :\n", no_prcs);
    readtable(maximum);
    printf("Enter the resources being already allocated to each process :\n");
    readtable(allocated);
    for(i=0;i<no_prcs;i++)
        finish[i]=false;
    printf("\n Additional Resources Required by each process :\n");
    proc_need();
    printf("\n Availble Resources : \n");
    findavail();
    for(j=0;j<no_resrc;j++) {
        printf("\t %d", available[j]);
    } 
    for(j=0;j<no_resrc;j++) {
        work[j]=available[j];
    }
    printf("\n Work:\n");
    for(j=0;j<no_resrc;j++) {
        printf("\t %d ",work[j]);
    }




}




void findneed()
{
    for(i=0;i<no_prcs;i++)
    {
        for(j=0;j<no_resrc;j++)   
        {
            need[i][j]=maximum[i][j]-allocated[i][j];

        }

    }
}


void selectprocess() {
    int flag;

    for(i=0;i<no_prcs;i++) { 
        for(j=0;j<no_resrc;j++) { 

            if(need[i][j]<=work[j])
                flag=1;
            else {
                flag=0;       
                break;
            }
        }
        if((flag==1)&&(finish[i]==false)) {
            process=i;

            safe_state[s++]=i;
            count++;
            break;
        } 



    }


    if(flag==0) {

        printf("system is in unsafe state\n");
        printf("\nNot possible to allocate resources \n");
        exit(1);
    }

}




void recvr_resrc(int p)
{
    finish[p]=true;

    for(j=0;j<no_prcs;j++) {
        work[j]=work[j]+allocated[p][j];
    }


}


void main()
{
    int choice,prcs,flg=0;
    init();
    findavail();
    findneed();

    do  {
        selectprocess();
        recvr_resrc(process);

    } while(count<no_prcs);

    printf("\nSafe State :\n ");

    for(i=0;i<no_prcs;i++) {

        printf("-->P%d", safe_state[i]);
    }

    while(1) {
        printf("\n Does any of the process require additional resource (1=yes, 0=no: )");
        scanf("%d", &choice);
        if(choice==1) {
            for(i=0;i<no_prcs;i++) {
                finish[i]=false;
                safe_state[i]=0;
            } 
            s=0;

            printf("\n Which process requires additional resource (Pr0cess0 to process%d ): ", no_prcs-1);
            scanf("%d", &prcs);
            printf("\n Enter the additional no of instances of the resources required by the process%d :", prcs);
            for(j=0;j<no_resrc;j++) {
                scanf("%d", &reqrd[j]);
            }

            for(j=0;j<no_resrc;j++) {

                if(reqrd[j]<= available[j] && reqrd[j]<= need[prcs][j]) {

                    flg=1;
                }

                else {

                    flg=0;
                    break;
                } 
            }
            if(flg==1) {

                for(i=0;i<no_resrc;i++) {

                    work[i]= available[i];
                    work[i]= work[i]-reqrd[i];
                    allocated[prcs][i]+=reqrd[i];
                    need[prcs][i]-=reqrd[i];
                }

                count=0;
                process=-1;

                do {
                    selectprocess();
                    recvr_resrc(process);

                } while(count<no_prcs);


                printf("\n Possible to allocate resources \n");
                printf("\nSafe State :\n ");

                for(i=0;i<no_prcs;i++) {

                    printf("--> P%d", safe_state[i]);
                }

            }


        }
        else {

            exit(1);
        }




    }


}

