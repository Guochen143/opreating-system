    #include <iostream>
    #include <fstream>
    #include<string>
    #include <iomanip>
    #include <deque>
    #include <algorithm>
using namespace std;

class Process
{
public:
    int Pid;
    int arrival_t;
    int burst_t;
    int waiting_t; 
    int turnaround_t;
    int terminate_t;
    int remain_t;
    int serve_time;
    bool first_time;
};

int No_procs=0;
Process *p=new Process[20];






void Sort_by_arrivalT(Process *t){
    int i=0,j=0;
    Process temp;
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

    for(int i=0; i<No_procs;i++)
    {
      for( cputime ; cputime<p[i].arrival_t;++cputime)
      {
       cout<<"< system time "<<cputime<<"> is idle"<<endl;
   }

   string queue = "Ready queue: ";
   queue.append ("pid "+(to_string(p[i].Pid)));

   for(int j=i+1; j<No_procs;j++)
   { 
    queue.append ("->pid "+(to_string(p[j].Pid)));
} 

cout<<queue<<endl;
cout<<"< system time "<<cputime<<" > process "<<p[i].Pid<<" starts running "<<endl;

p[i].waiting_t=cputime-p[i].arrival_t;

p[i].terminate_t=cputime+p[i].burst_t;

p[i].turnaround_t=p[i].terminate_t-p[i].arrival_t;

cputime = cputime + 1;


for(cputime; cputime<p[i].terminate_t;++cputime)
{
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

    {str.append ("->pid " + (to_string(list[i].Pid)));}
cout<<str <<endl;

}

void RoundRobin (Process *t,const char * quantum)
{ 
    int q = atoi(quantum);
    string queue = "Ready queue: ";
    deque<Process> list;

    for(int i=0; i<No_procs;i++)
    {
        list.push_back(p[i]);
    }

    print_queue(queue,list);

    while(1)
     {if(!list.empty())
         {
           cputime = cputime + 1;
           list.front().remain_t = list.front().remain_t-1;



           list.front().serve_time = list.front().serve_time + 1;


           if (list.front().first_time)
            { list.front().waiting_t = cputime - list.front().arrival_t-1; 
                list.front().first_time = false;
                cout<<"< system time "<<cputime-1<<" > process "<<list.front().Pid<<" starts running "<<endl;
                cout<<"< system time "<<cputime<<" > process "<<list.front().Pid<<" is running "<<endl;
            }

            else  if (list.front().remain_t == 0)
            {
                cout<<"< system time "<< cputime <<" > process "<< list.front().Pid <<" is finished ....... " <<endl;
                for(int i=0; i < No_procs;i++)
                    {  if(list.front().Pid == p[i].Pid)
                        {
                            list.front().turnaround_t = cputime - list.front().arrival_t;
                            p[i] = list.front();
                            list.pop_front();

                            break;
                        }
                    }
                    if(!list.empty())
                    { 
                        print_queue(queue,list);
                    }
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





     break;
 }
}
}


void print_rqueue(deque<Process> queue)
{
    cout << "Ready queue: ";
 for(int i = 0; i < queue.size(); i++)
 {
    if(i != queue.size() - 1)
    {
        cout << queue[i].Pid << "->";
    }
    else
    {
        cout << queue[i].Pid;
    }
 }
    cout<<endl;
}

bool sjf_comparator(const Process& p1, const Process& p2)
{
    if(p1.arrival_t < p2.arrival_t)
    {
        return true;
    }
    else
    {
        if(p1.remain_t < p2.remain_t)
        {
            return true;
        }
    }
    return false;
}

bool sjrf_comparator(const Process& p1, const Process& p2)
{
    return p1.remain_t < p2.remain_t;
}

void SJF_Simulator(Process *t, bool preemptive)
{
    
 deque<Process> queue;
 //add processes to queue
 int to_finish = No_procs;
 vector<Process> processes;
 for(int i = 0; i < No_procs; i++)
 {
    processes.push_back(t[i]);
 }
 int last = -1;
 std::sort(processes.begin(), processes.end(), sjf_comparator);

while(to_finish > 0)
{

for(int i = 0; i < No_procs; i++)
{
    
    Process p = processes[i];
    if(p.arrival_t == cputime)
    {
            queue.push_back(p);
            if(preemptive)
            {
                std::sort(queue.begin(), queue.end(), sjrf_comparator);
            }
            else
            {
                std::sort(queue.begin() + 1, queue.end(), sjrf_comparator);
            }            
    }
}


if(queue.size() == 0)
{
    cout << "Ready Queue: Idle" << endl;
}
else
{
    if(last > 0 && last != queue.front().Pid)
    {
        for(int i = 0; i < queue.size(); i++)
        {
            if(queue[i].Pid == last && queue[i].remain_t > 0)
            {
            cout<<"< system time "<< cputime <<" > process "<< last << " paused" <<endl;
            queue[i].first_time = true;
            } 
        }
    }
}
last = queue.front().Pid;


if(queue.front().remain_t == 0)
{
    cout<<"< system time "<< cputime <<" > process "<< queue.front().Pid << " finished" <<endl;
    Process fproc = queue.front();
    for(int i = 0; i < No_procs; i++)
    {
        if(t[i].Pid == fproc.Pid)
        {
            t[i].remain_t = 0;
            t[i].serve_time = t[i].burst_t;
            t[i].turnaround_t = cputime - t[i].arrival_t;
            t[i].waiting_t = cputime - (t[i].burst_t + t[i].arrival_t);
        } 
    } 
    queue.pop_front();
    to_finish--;
}

if(to_finish > 0)
{

    if(queue.front().first_time)
    {
        print_rqueue(queue);
        queue.front().first_time = false;
        cout<<"< system time "<< cputime <<" > process "<< queue.front().Pid << " started running" <<endl;
    }
    else
    {
        cout<<"< system time "<< cputime <<" > process "<< queue.front().Pid << " is running" <<endl;
    }
    queue.front().remain_t--;
    cputime++;
}
else
{
    //execution is finished
    cout << "Ready Queue: Idle" << endl;

}


}


}


bool pid_comparator(const Process& p1, const Process& p2)
{
    return p1.Pid < p2.Pid;
}
void Calculate(Process *t)
{

    std::sort(t, t + No_procs, pid_comparator);
    float totalWaitingTime=0 , TotalTurnaroundTime=0 ,totalBurstTime=0;
    cout<<" "<<"PID"<<"\t"<<"BURST TIME"<<"\t"<<"WAITING TIME"<<"\t"<<"TURNAROUND TIME"<<endl;
    for(int i=0;i<No_procs;i++)
    { 
       cout<<" "<<i+1<<"\t"<<p[i].burst_t<<"\t\t"<<p[i].waiting_t<<"\t\t"<<p[i].turnaround_t<<endl;

       totalBurstTime+=p[i].burst_t;
       totalWaitingTime+=p[i].waiting_t;
       TotalTurnaroundTime+=p[i].turnaround_t;
   }
   cout<<"==========================================="<<endl;
   cout <<"Average cpu usage        : "<<setprecision(2)<<fixed<<(totalBurstTime/cputime)*100<<endl;
   cout <<"Average waiting time      : "<<setprecision(2)<<fixed<<totalWaitingTime/No_procs<<endl;
   cout <<"Average turnaround time  : "<<setprecision(2)<<fixed<<TotalTurnaroundTime/No_procs<<endl;
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


    if(myfile.is_open())
    {

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

  cout<<"\n";
  cout<<"===================================================================="<<endl;


  if(algorithm == "FCFS" || algorithm == "fcfs")
  {
    FCFS_Simulator(p);
    cout<<"Scheduling Algorithim: FCFS total "<<No_procs<<" tasks are read from "<<argv[1]<<""<<endl;
}

else if ((algorithm == "RR" || algorithm == "rr") && argv[3] != NULL)
{
    string quantum = argv[3];
    RoundRobin(p,argv[3]);
    cout<<"Scheduling Algorithim: RR total "<<No_procs<<" tasks are read from "<<argv[1]<<""<<endl;
}
else if (algorithm == "SJF" || algorithm == "sjf")
{
    SJF_Simulator(p, false);
    cout<<"Scheduling Algorithim: SJF total "<<No_procs<<" tasks are read from "<<argv[1]<<""<<endl;
}
else if (algorithm == "SRJF" || algorithm == "srjf")
{
    SJF_Simulator(p, true);
    cout<<"Scheduling Algorithim: SRJF total "<<No_procs<<" tasks are read from "<<argv[1]<<""<<endl;
}


else
{
    cout << "Invalid algorithm name." << endl;  return 0;
}




cout<<"===================================================================="<<endl<<endl;


cout<<"\n";

Calculate(p); 





return 0;
}