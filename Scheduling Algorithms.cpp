#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <utility>
#include <algorithm>
#include <climits>
#include <queue>

using namespace std;

// DEFINITION
struct procs
{
    int pid;
    int arrival_time;
    int Burst_time;
    int wait_time;
    int response_time;
    int turnaround_time;
    int start;
    int end;
    int rem;
    bool status;
    bool cpu;
    bool invector;
    bool queue1;
    bool queue2;
    int working_cycles;
};

void FCFS(procs proc[], int size)
{
    int total = proc[0].arrival_time;
    double avrg_wait = 0;
    double avrg_turnaround = 0;
    double avrg_response = 0;
    vector<procs *> v3;

    /*for(int k=0;k<size;k++)
   {
       cout<< proc[k].arrival_time<<","<< proc[k].Burst_time<<endl;
   }*/

    for (int l = 0; l < size; l++)
    {
        total = total + proc[l].Burst_time;
    }

    for (int m = 0; m < size; m++)
    {
        proc[m].start = 0;
        proc[m].end = 0;
        proc[m].wait_time = 0;
        proc[m].response_time = 0;
        proc[m].turnaround_time = 0;
        proc[m].status = 0;
        proc[m].rem = proc[m].Burst_time;
    }

    for (int i = 0; i <= total; i++) // time
    {
        for (int j = 0; j < size; j++)
        {
            if (proc[j].arrival_time == i)
            {
                if (proc[j].status == 0)
                {
                    v3.push_back(&proc[j]);
                }
            }
        }

        if (v3.size() == 0)
            continue;
        if (v3[0]->rem != 0)
        {
            v3[0]->rem--;
            if (v3[0]->rem == 0)
            {
                v3[0]->end = i + 1;
                v3[0]->turnaround_time = v3[0]->end - v3[0]->arrival_time;
                v3[0]->wait_time = v3[0]->turnaround_time - v3[0]->Burst_time;
                v3[0]->start = v3[0]->arrival_time + v3[0]->wait_time;
                v3[0]->response_time = v3[0]->start - v3[0]->arrival_time;
                v3.erase(v3.begin());
            }
        }
    }

    for (int h = 0; h < size; h++)
    {
        /*cout << "pid:" << proc[h].pid << endl;
        cout << "start time:" << proc[h].start << endl;
        cout << "end time:" << proc[h].end << endl;
        cout << "wait time:" << proc[h].wait_time << endl;
        cout << "Turnaround time:" << proc[h].turnaround_time << endl;
        cout << "response time:" << proc[h].response_time << endl;*/
        avrg_wait = avrg_wait + proc[h].wait_time;
        avrg_turnaround = avrg_turnaround + proc[h].turnaround_time;
        avrg_response = avrg_response + proc[h].response_time;
    }
    avrg_wait = avrg_wait / size;
    avrg_turnaround = avrg_turnaround / size;
    avrg_response = avrg_response / size;

    //cout <<avrg_wait<<"\t";
    //cout << avrg_turnaround <<"\t";
    cout << avrg_response <<"\t";
}
void SJF_Non_Preemptive(struct procs proc[], int size)
{
    int total = 0;
    double avrg_wait = 0;
    double avrg_turnaround=0;
    double avrg_response=0;

    vector<procs*> v3;

    // total cpu time expected
    for (int i = 0; i < size; i++)
    {
        total = total + proc[i].Burst_time;
    }

    for (int m = 0; m < size; m++)
    {
        proc[m].start = 0;
        proc[m].end = 0;
        proc[m].wait_time = 0;
        proc[m].response_time = 0;
        proc[m].turnaround_time = 0;
        proc[m].status = 0;
        proc[m].rem = proc[m].Burst_time;
    }

    int num = 0;
    int lowestBurstTime = 0;
    int indexLowest;
    int indexCurrent;
    for (int i = 0; i <= total; i++) // time
    {
        for (int j = 0; j < size; j++)
        {
            if (proc[j].arrival_time == i)
            {
                if (proc[j].status == 0)
                {
                    v3.push_back(&proc[j]);
                }
            }
        }

        if (v3.size() == 0)
            continue;

        if (v3[0]->rem != 0)
        {
            v3[0]->rem--;
            if (v3[0]->rem == 0)
                v3[0]->end = i+1;
        }
        else
        {
            v3[0]->turnaround_time = v3[0]->end - v3[0]->arrival_time;
            v3[0]->wait_time = v3[0]->turnaround_time - v3[0]->Burst_time;
            v3[0]->start = v3[0]->arrival_time + v3[0]->wait_time;
            v3[0]->response_time = v3[0]->start - v3[0]->arrival_time;
            v3[0]->status = 1;
            v3.erase(v3.begin());
            i = i - 1;

            auto comp = [](procs* a, procs* b)
            {
                return a->rem < b->rem;
            };
            sort(v3.begin(), v3.end(), comp);
        }
    }

    for (int i = 0; i < size; i++)
    {
        /*cout << "pid:" << proc[i].pid << endl;
        cout << "start time:" << proc[i].start << endl;
        cout << "end time:" << proc[i].end << endl;
        cout << "wait time:" << proc[i].wait_time << endl;
        cout << "Turnaround time:" << proc[i].turnaround_time << endl;
        cout << "response time:" << proc[i].response_time << endl;*/
        avrg_wait = avrg_wait + proc[i].wait_time;
        avrg_turnaround=avrg_turnaround+proc[i].turnaround_time;
        avrg_response=avrg_response+proc[i].response_time;
    }

    avrg_wait = avrg_wait / size;
    avrg_turnaround = avrg_turnaround / size;
    avrg_response = avrg_response / size;

    //cout << avrg_wait <<"\t";
    cout << avrg_turnaround <<"\t";
    //cout << avrg_response<<"\t";

}

void SJF_Preemptive(struct procs proc[], int size)
{
    int total = proc[0].arrival_time;
    double avrg_wait = 0;
    double avrg_turnaround = 0;
    double avrg_response = 0;
    vector<procs *> v3;

    // total cpu time expected
    for (int i = 0; i < size; i++)
    {
        total = total + proc[i].Burst_time;
    }

    for (int m = 0; m < size; m++)
    {
        proc[m].start = INT_MAX;
        proc[m].end = 0;
        proc[m].wait_time = 0;
        proc[m].response_time = 0;
        proc[m].turnaround_time = 0;
        proc[m].status = 0;
        proc[m].rem = proc[m].Burst_time;
    }

    int num = 0;

    for (int i = 0; i <= total; i++) // time
    {
        for (int j = 0; j < size; j++)
        {
            if (proc[j].arrival_time == i)
            {
                if (proc[j].status == 0)
                {
                    if (v3.size() > 0)
                    {
                        if (v3[0]->rem > proc[j].rem)
                        {
                            v3.insert(v3.begin(), &proc[j]);
                            v3[0]->start = i;
                        }
                        else
                        {
                            v3.insert(v3.begin() + 1, &proc[j]);
                        }
                    }
                    else
                    {
                        v3.insert(v3.begin(), &proc[j]);
                        v3[0]->start = i;
                    }
                }
            }
        }

        if (v3.size() == 0)
            continue;

        if (v3[0]->rem != 0)
        {
            v3[0]->rem--;
            if (v3[0]->rem == 0)
            {
                v3[0]->end = i + 1;
            }
        }
        else
        {
            v3[0]->turnaround_time = v3[0]->end - v3[0]->arrival_time;
            v3[0]->wait_time = v3[0]->turnaround_time - v3[0]->Burst_time;
            v3[0]->response_time = v3[0]->start - v3[0]->arrival_time;
            v3[0]->status = 1;
            v3.erase(v3.begin());

            auto comp = [](procs *a, procs *b)
            {
                return a->rem < b->rem;
            };
            sort(v3.begin(), v3.end(), comp);

            // We did not start preemptively, so we set it here
            if (v3.size() > 0)
                if (v3[0]->start == INT_MAX)
                    v3[0]->start = i;

            i = i - 1;
        }
    }

    for (int h = 0; h < size; h++)
    {
        /*cout << "pid:" << proc[h].pid << endl;
        cout << "start time:" << proc[h].start << endl;
        cout << "end time:" << proc[h].end << endl;
        cout << "wait time:" << proc[h].wait_time << endl;
        cout << "Turnaround time:" << proc[h].turnaround_time << endl;
        cout << "response time:" << proc[h].response_time << endl;*/
        avrg_wait = avrg_wait + proc[h].wait_time;
        avrg_turnaround = avrg_turnaround + proc[h].turnaround_time;
        avrg_response = avrg_response + proc[h].response_time;
    }
    avrg_wait = avrg_wait / size;
    avrg_turnaround = avrg_turnaround / size;
    avrg_response = avrg_response / size;

    //cout <<avrg_wait <<"\t";    //cout << "avrg turnaround time:" << avrg_turnaround << endl;
    //cout << avrg_turnaround <<"\t";
    cout << avrg_response<<"\t";
}

void RoundRobin(struct procs proc[], int size, int quantum)
{
    int total = proc[0].arrival_time;
    double avrg_wait = 0;
    double avrg_turnaround = 0;
    double avrg_response = 0;
    // int quantum=20;
    int strt;
    int stop;
    vector<procs *> v3;

    // total cpu time expected
    for (int i = 0; i < size; i++)
    {
        total = total + proc[i].Burst_time;
    }

    for (int m = 0; m < size; m++)
    {
        proc[m].start = INT_MAX;
        proc[m].end = 0;
        proc[m].wait_time = 0;
        proc[m].response_time = 0;
        proc[m].turnaround_time = 0;
        proc[m].status = 0;
        proc[m].rem = proc[m].Burst_time;
        proc[m].cpu = 0;
        proc[m].invector = 0;
    }

    strt = proc[0].arrival_time;
    for (int i = 0; i <= total; i++) // time
    {
        // cout<<i<<"-";
        for (int j = 0; j < size; j++)
        {
            if (proc[j].arrival_time == i)
            {
                if (proc[j].status == 0)
                {
                    v3.push_back(&proc[j]);
                    // cout<<v3[v3.size()-1]->pid<<endl;
                }
            }
        }
        if (v3.size() == 0)
            continue;

        if (v3[0]->rem != 0 && (i - strt != quantum))
        {
            // cout<<v3[0]->pid<<endl;
            v3[0]->rem--;
            if (v3[0]->cpu == 0)
            {
                v3[0]->start = i;
            }
            v3[0]->cpu = 1;

            if (v3[0]->rem == 0)
            {
                v3[0]->end = i + 1;
                strt = i + 1;
                v3[0]->cpu = 0;
            }
        }

        else if (i - strt == quantum)

        {
            v3[0]->end = i - 1;
            rotate(v3.begin(), v3.begin() + 1, v3.end());
            strt = i;
            // cout<<v3[0]->pid<<endl;
            v3[0]->rem--;
            // cout<<v3[0]->pid<<endl;

            if (v3[0]->cpu == 0)
            {
                v3[0]->start = i;
            }

            v3[0]->cpu = 1;

            if (v3[0]->rem == 0)
            {
                v3[0]->cpu = 0;
                v3[0]->end = i + 1;
                strt = i + 1;
            }
        }

        else

        {
            v3[0]->turnaround_time = v3[0]->end - v3[0]->arrival_time;
            v3[0]->wait_time = v3[0]->turnaround_time - v3[0]->Burst_time;
            v3[0]->start = v3[0]->arrival_time + v3[0]->wait_time;
            v3[0]->response_time = v3[0]->start - v3[0]->arrival_time;
            v3[0]->status = 1;
            v3.erase(v3.begin());
            // strt = v3[0]->end;
            i = i - 1;

            /*auto comp = [](procs *a, procs *b)
            {
                return a->rem < b->rem;
            };
            sort(v3.begin(), v3.end(), comp);*/
        }
    }

    for (int h = 0; h < size; h++)
    {
        /*cout << "pid:" << proc[h].pid << endl;
        cout << "start time:" << proc[h].start << endl;
        cout << "end time:" << proc[h].end << endl;
        cout << "wait time:" << proc[h].wait_time << endl;
        cout << "Turnaround time:" << proc[h].turnaround_time << endl;
        cout << "response time:" << proc[h].response_time << endl;*/
        avrg_wait = avrg_wait + proc[h].wait_time;
        avrg_turnaround = avrg_turnaround + proc[h].turnaround_time;
        avrg_response = avrg_response + proc[h].response_time;
    }
    avrg_wait = avrg_wait / size;
    avrg_turnaround = avrg_turnaround / size;
    avrg_response = avrg_response / size;

    //cout <<avrg_wait<<"\t";
   // cout << avrg_turnaround <<"\t";
   cout << avrg_response <<"\t";
}

void MLFQ(procs proc[], int size, int quantum1, int quantum2)
{
    double avrg_wait = 0;
    double avrg_turnaround = 0;
    double avrg_response = 0;

    queue<procs *> Q0;
    queue<procs *> Q1;
    queue<procs *> Q2;
    // bool NewQuantum = 0;

    for (int m = 0; m < size; m++)
    {
        proc[m].start = INT_MAX;
        proc[m].end = 0;
        proc[m].wait_time = 0;
        proc[m].response_time = 0;
        proc[m].turnaround_time = 0;
        proc[m].status = 0;
        proc[m].rem = proc[m].Burst_time;
        proc[m].cpu = 0;
        proc[m].invector = 0;
        proc[m].working_cycles=0;
    }




    int total = proc[0].arrival_time;
    // total cpu time expected
    for (int i = 0; i < size; i++)
    {
        total = total + proc[i].Burst_time;
    }

    for (int m = 0; m < size; m++) // initializations
    {
        proc[m].start = INT_MAX;
        proc[m].end = 0;
        proc[m].wait_time = 0;
        proc[m].response_time = 0;
        proc[m].turnaround_time = 0;
        proc[m].status = 0;
        proc[m].rem = proc[m].Burst_time;
        proc[m].cpu = 0;
        proc[m].invector = 0;
        proc[m].working_cycles = 0;
    }
    int l = 0;

    int finished_count = 0;
    while (finished_count != size)
    {

        for (int j = 0; j < size; j++)
        {
            if (proc[j].arrival_time == l)
            {
                if (proc[j].status == 0)
                {
                    Q0.push(&proc[j]);
                    // cout<<v3[v3.size()-1]->pid<<endl;
                }
            }
        }

        if (Q0.empty() == false)
        {
            procs *p = Q0.front();
            if (p->rem == p->Burst_time)
            {
                p->start = l;
            }

            if (p->rem != 0 && p->working_cycles != quantum1)
            {
                p->working_cycles++;
                p->rem--;
                if (p->rem == 0)
                {
                    p->end = l + 1;
                    Q0.pop();
                    finished_count++;
                }
            }
            else if (p->rem != 0 && p->working_cycles == quantum1)
            {
                p->working_cycles = 0;
                Q1.push(p);
                Q0.pop();
            }

    
        }

        if (Q1.empty() == false && Q0.empty())
        {
            procs *p = Q1.front();
            if (p->rem != 0 && p->working_cycles != quantum2)
            {
                p->working_cycles++;
                p->rem--;
                if (p->rem == 0)
                {
                    p->end = l + 1;
                    //Q2.push(Q1.front());
                    Q1.pop();
                    finished_count++;
                }
            }
            else if (p->rem != 0 && p->working_cycles == quantum2)
            {
                p->working_cycles = 0;
                Q2.push(p);
                Q1.pop();
            
            }
        }

        if ((Q2.empty() == false)&& (Q1.empty()==true) && (Q0.empty()==true))
        {
            procs *p = Q2.front();
            p->rem--;
            if (p->rem == 0)
            {
                p->end = l + 1;
                Q2.pop();
                finished_count++;
            }
        }
        l++;
    }


    for(int t=0;t<size;t++)
    {
        proc[t].turnaround_time=proc[t].end-proc[t].arrival_time;
        proc[t].wait_time=proc[t].turnaround_time-proc[t].Burst_time;
        //proc[t].start =proc[t].arrival_time + proc[t].wait_time;
        proc[t].response_time=proc[t].start-proc[t].arrival_time;
    }

    for (int h = 0; h < size; h++)
    {
    /* cout << "pid:" << proc[h].pid << endl;
        cout << "start time:" << proc[h].start << endl;
        cout << "end time:" << proc[h].end << endl;
        cout << "wait time:" << proc[h].wait_time << endl;
        cout << "Turnaround time:" << proc[h].turnaround_time << endl;
        cout << "response time:" << proc[h].response_time << endl;*/
        avrg_wait = avrg_wait + proc[h].wait_time;
        avrg_turnaround = avrg_turnaround + proc[h].turnaround_time;
        avrg_response = avrg_response + proc[h].response_time;
    }
    avrg_wait = avrg_wait / size;
    avrg_turnaround = avrg_turnaround / size;
    avrg_response = avrg_response / size;

    //cout <<avrg_wait<<"\t";
   // cout << avrg_turnaround <<"\t";
    cout <<avrg_response <<"\t";
}

bool compare(procs a, procs b)
{
    if (a.arrival_time < b.arrival_time)
        return 1;
    else
        return 0;
}

int main()
{
    vector<string> v;
    vector<string> row;
    fstream myfile;
    string line, line1;
    string word;
    int size;
    int j = 0;

    myfile.open("test1.txt");

    while (getline(myfile, line))
    {
        stringstream element(line);
        while (getline(element, word, ','))
        {
            v.push_back(word);
        }
    }

    myfile.close();
    size = v.size() / 3;
    procs *proc = new procs[size];

    for (int i = 0; i < v.size() / 3; i++)
    {
        proc[i].pid = stoi(v[j]);
        proc[i].arrival_time = stoi(v[j + 1]);
        proc[i].Burst_time = stoi(v[j + 2]);
        j = j + 3;
    }

    sort(proc, proc + size, compare);
    /*   for(int m=0;m<size;m++)
   {
       cout<<proc[m].pid<<","<<proc[m].arrival_time<<","<<proc[m].Burst_time<<endl;
   }*/
    
    FCFS(proc,size);
     //cout<<"\t";
    SJF_Non_Preemptive(proc, size);
       //cout<<"\t";
    SJF_Preemptive(proc,size);
      // cout<<"\t";
    RoundRobin(proc, size, 20);
     // cout<<"\t";
    MLFQ(proc, size, 5, 20);

     }

