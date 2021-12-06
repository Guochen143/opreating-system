#include <iostream>
#include <fstream>
#include<string>
#include <iomanip>
#include <deque>
using namespace std;

class Process{
    public:
    int Pid;
    int arrival_t;
    int burst_t;
    int wating_t; 
    int turnaround_t;
    int terminate_t;
    int remain_t;
    int serve_time;
    bool first_time;

};

int No_procs=0;
Process *p=new Process[20];






void Sort_by_arrivalT(Process *t){
int i=0,j=0;Process temp;
for(i=0;i<No_procs;i++)
{
 for(j=i;j>=1;j--)
  { if(p[j].arrival_t<p[j-1].arrival_t)
      {
          temp=p[j-1];
          p[j-1]=p[j];
          p[j]=temp;
       }
 }
}
}
int cputime=0;
void FCFS_Simulator(Process *t){
    

    
    
    for(int i=0; i<No_procs;i++){
		for( cputime ; cputime<p[i].arrival_t;++cputime){
			cout<<"< system time "<<cputime<<"> is idle"<<endl;}
		
    string queue = "Ready queue: ";
    queue.append ("pid "+(to_string(p[i].Pid)));
    


    for(int j=i+1; j<No_procs;j++)
       { queue.append ("->pid "+(to_string(p[j].Pid)));}
       cout<<queue<<endl;
        cout<<"< system time "<<cputime<<" > process "<<p[i].Pid<<" starts running "<<endl;

		p[i].wating_t=cputime-p[i].arrival_t;

		p[i].terminate_t=cputime+p[i].burst_t;
                
		p[i].turnaround_t=p[i].terminate_t-p[i].arrival_t;
        
        cputime = cputime + 1;
        

		for(cputime; cputime<p[i].terminate_t;++cputime){
		cout<<"< system time "<<cputime<<" > process "<<p[i].Pid<<" is running "<<endl;}
	

		cout<<"< system time "<<cputime<<" > process "<<p[i].Pid<<" is finished ....... "<<endl;
      


    }


    cout<<"Ready queue: Idle "<<endl;
	cout<<"< system time "<<cputime<<" > All processes are finish ................... "<<endl;
}


void print_queue(string str,deque<Process> list)
{ 
 str.append ("pid "+(to_string(list.front().Pid)));

for(int i = 1;i < list.size(); i++)

{str.append ("->pid "+(to_string(list[i].Pid)));}
 cout<<str <<endl;

                           }










 void RoundRobin (Process *t,const char * quantum)
 { int q = atoi(quantum);
string queue = "Ready queue: ";
 
 deque<Process> list;

  for(int i=0; i<No_procs;i++)
  {list.push_back(p[i]);

  }









print_queue(queue,list);




while(1)
 {if( ! list.empty() )
 {
   cputime = cputime + 1;
		list.front().remain_t = list.front().remain_t-1;
                
        

        list.front().serve_time = list.front().serve_time + 1;


        if (list.front().first_time)
        { list.front().wating_t = cputime - list.front().arrival_t-1; 
        list.front().first_time = false;
        cout<<"< system time "<<cputime-1<<" > process "<<list.front().Pid<<" starts running "<<endl;
        cout<<"< system time "<<cputime<<" > process "<<list.front().Pid<<" is running "<<endl;
        }

       else  if (list.front().remain_t == 0)
        {
            
            
        
            cout<<"< system time "<<cputime<<" > process "<<list.front().Pid<<" is finished ....... "<<endl;
            
            
            for(int i=0; i < No_procs;i++)
        {  if(list.front().Pid == p[i].Pid)
            {list.front().turnaround_t = cputime - list.front().arrival_t;
            p[i] = list.front();
            list.pop_front();
            
            break;}}



            if( ! list.empty() )
           { print_queue(queue,list);}
            
            
            
            
            
            
            
            
            
            
            }

        else if (list.front().serve_time == q)
         {cout<<"< system time "<<cputime<<" > process "<<list.front().Pid<<" is paused ....... "<<endl;
             
             
             
             list.front().serve_time = 0;
            list.push_back(list.front());
         list.pop_front();
         print_queue(queue,list);
          }
          
          
         else{cout<<"< system time "<<cputime<<" > process "<<list.front().Pid<<" is running "<<endl;                                              } 
          
          
          
          
          
          
          
          
          }

else { cout<<"Ready queue: Idle "<<endl;
	cout<<"< system time "<<cputime<<" > All processes are finish ................... "<<endl;
    
    
    
    
    
    break;}}
 }


 

































void Calculate(Process *t){
    
float totalWatingTime=0 , TotalTurnaroundTime=0 ,totalBurstTime=0;
cout<<" "<<"PID"<<"        "<<"BURST TIME"<<"        "<<"WAITING TIME"<<"        "<<"TURNAROUND TIME"<<endl;
	for(int i=0;i<No_procs;i++)
	{   cout<<" "<<i+1<<"              "<<p[i].burst_t<<"                  "<<p[i].wating_t<<"                    "<<p[i].turnaround_t<<endl;

		totalBurstTime+=p[i].burst_t;
		totalWatingTime+=p[i].wating_t;
		TotalTurnaroundTime+=p[i].turnaround_t;
	}
        cout<<"==========================================="<<endl;
cout <<"Avarage cpu usage        : "<<setprecision(2)<<fixed<<(totalBurstTime/cputime)*100<<endl;
cout <<"Avarage wating time      : "<<setprecision(2)<<fixed<<totalWatingTime/No_procs<<endl;
cout <<"Avarage turnaround time  : "<<setprecision(2)<<fixed<<TotalTurnaroundTime/No_procs<<endl;
        cout<<"==========================================="<<endl;
        
}




int main(int argc, const char * argv[]) {
    if (argc < 3)
{
cout<<"Usage: sched input_file FCFS|RR|SRJF|SJF [quantum]"<<endl;

    return -1;
}
    string algorithm = argv[2];
    ifstream myfile(argv[1]);
    string line;  
  

    if(myfile.is_open()){

    getline( myfile, line );
    cout<<line<<endl;


      while(!myfile.eof()&& No_procs<=20){
          
          myfile>>p[No_procs].Pid>>p[No_procs].arrival_t>>p[No_procs].burst_t;
          p[No_procs].remain_t = p[No_procs].burst_t;
          p[No_procs].first_time = true;
          p[No_procs].serve_time = 0;
          cout<<" "<<p[No_procs].Pid<<"        "<<p[No_procs].arrival_t<<"          "<<p[No_procs].burst_t<<endl;
          No_procs++;
          if(No_procs==20) break; 
          }
      myfile.close();
    }
  
   Sort_by_arrivalT(p);
    

//------------------------------------------- 
   
cout<<"\n";
cout<<"===================================================================="<<endl;


 if(algorithm == "FCFS" || algorithm == "fcfs"){
FCFS_Simulator(p);
cout<<"Scheduling Algorthim: FCFS total "<<No_procs<<" tasks are read from "<<argv[1]<<""<<endl;


}

else if (algorithm == "RR" || algorithm == "rr"){

    string quantum = argv[3];
RoundRobin(p,argv[3]);
cout<<"Scheduling Algorthim: RR total "<<No_procs<<" tasks are read from "<<argv[1]<<""<<endl;}





else
{
        cout << "Invalid algorithm name." << endl;  return 0;
    }




cout<<"===================================================================="<<endl<<endl;
       

cout<<"\n";

Calculate(p); 
   

	


    return 0;
}