#include <iostream>
#include <bits/stdc++.h>
#include "CPU_sched.h"

using namespace std;


vector<int>* FCFS(vector<int> start_time, vector<int> service_time,int n, int maxtime){
    vector<int> freq_sequence;
    vector<int> proc_sequence;
    vector<int> finish_time(n) , turnaround(n) , wait_time(n) , normturn(n);
    vector<char> processes_name(n);

    vector<int>  ss = service_time;
    bool isDone[n];
    fill(isDone, isDone+n, false);
    map<int, int> finish_map;
    int jobDone = 0,curTime=start_time[0];
    int p;
    int i,j,tem;
     for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {


            if (start_time[i] > start_time[j]) {

                tem = start_time[i];
                start_time[i] = start_time[j];
                start_time[j] = tem;
            }
        }
    }   
    
    do{
            
            for (int id = 0; id < n; id++) {

            if (start_time[id] <= curTime && isDone[id]==false) {
                    p = id;
                    break;
            }
        }

        curTime += service_time[p];
        // cout << "\n" << service_time[p] << "\n";
        proc_sequence.push_back(p);
        finish_time[p] = curTime;
        finish_map[p]=finish_time[p];
        isDone[p] = true;
        jobDone++;
        // cout << curTime << "\n";

    } while(jobDone!=n);
    

      for (int i = 0; i < n; i++)
    {
        finish_time[i] = finish_map[i];
        turnaround[i] = finish_time[i] - start_time[i];
        wait_time[i] = turnaround[i] - service_time[i];
        normturn[i] = (float)turnaround[i] / (float)ss[i];
    }

    static vector<int> resultFCFS[5];
    resultFCFS[0] = finish_time;
    resultFCFS[1] = turnaround;
    resultFCFS[2] = wait_time;
    resultFCFS[3] = normturn;
    resultFCFS[4] = proc_sequence;

    return resultFCFS;

}

void FCFSstats(vector<int> turnaround,vector<int>normturn ,vector<int> finish_time, vector<int> service_time,vector<int> start_time ,vector<char> processes_name , int n, int maxtime){
float avgN,avgT;
int avgNorm=0,avgturn=0;
vector<int> ss= service_time;
vector< vector<char> > stats(n, vector<char>(maxtime,' '));
    cout << "FCFS";
  cout << "\nProcess    |" <<"";
  for (int i = 0; i < stats.size(); i++)
    {cout <<std::setw(3)<<processes_name[i] <<"  |";
         }
          cout << "\nArrival    |";
  for (int i = 0; i < stats.size(); i++)
    {cout <<std::setw(3)<<start_time[i] <<"  |";
         }
 cout << "\nService    |" ;
  for (int i = 0; i < stats.size(); i++)
    {
        cout <<std::setw(3)<<ss[i] <<"  |";


         }cout << " Mean|";


    cout << "\nFinish     |" <<"";
  for (int i = 0; i < stats.size(); i++)
    {cout <<std::setw(3)<<finish_time[i] <<"  |";

         }cout << "-----|";
  cout << "\nTurnaround |" <<"";
  for (int i = 0; i < stats.size(); i++)
    {
       cout <<std::setw(3)<<turnaround[i] <<"  |";
         avgturn=avgturn+ turnaround[i];
      avgT=(float)avgturn/(float)n;
         }
         cout << fixed << setprecision(2)<<std::setw(5) << avgT<<"|";

cout << "\nNormTurn   |";
  for (int i = 0; i < stats.size(); i++)
    { vector<float>m(n); m[i] = (float)turnaround[i] / (float)ss[i];
avgNorm+=m[i];
        avgN=(float)avgNorm/(float)n;

     cout<<" "<<fixed<<std::setw(4)<<setprecision(2)<< m[i]<<"|";
             }
         cout << fixed << setprecision(2)<<std::setw(5) << avgN<<"|";

cout << "\n";
cout << endl;   

}

void FCFStrace(vector<int> result_proc_seq, vector<int> finish_time, vector<int> service_time,vector<int> start_time ,vector<char> processes_name , int n, int maxtime){
   
    vector<int> proc_sequence = result_proc_seq;
    vector<int> freq_sequence;

    vector< vector<char> > status(n, vector<char>(maxtime, ' ')); // Result Board
    vector<int>  temp  = service_time;
    vector<int> finish = finish_time;
    for(int i = 0 ; i < proc_sequence.size();i++){
        for(int x = 0 ; x < temp[proc_sequence[i]] ; x++) {
        freq_sequence.push_back(proc_sequence[i]);
        }
    }
    for(int i = 0 ; i < status[0].size();i++){  //0 1 2 3 4 ....
        for(int x = 0 ; x < status.size();x++){ //A B C D E
            if(finish[x] > i && start_time[x] <= i) status[x][i] = '.'; //  finish > i >= start time
        }
    }
     for(int i = 0, k = start_time[0]; i < freq_sequence.size() && k < (freq_sequence.size()+start_time[0]) ; i++, k++){
        status[freq_sequence[i]][k] = '*';
    }

    cout << "FCFS" <<"  ";
    for (int i = 0; i <= maxtime; i++)
        cout << i % 10 << " ";
    cout << "\n";
    cout << "------";
    for (int i = 0; i <= maxtime * 2; i++)
        cout << "-";
    cout << "-\n";
    for (int i = 0; i < status.size(); i++)
    {
        cout << processes_name[i] << "     |";
        for (int x = 0; x < status[i].size(); x++)
        {
            cout << status[i][x] << "|";
        }
        cout << " \n";
    }
    cout << "------";
    for (int i = 0; i <= maxtime * 2; i++)
        cout << "-";
    cout << "-\n";
    cout << endl;

}


vector<int>* SRN(vector<int> start_time, vector<int> service_time,int n, int maxtime){
vector<int> finish_time(n) , turnaround(n) , wait_time(n) , normturn(n);
vector<char> processes_name(n);
vector<int>  sst= service_time;
vector<int> freq_sequence;
    bool isDone[n];
    fill(isDone, isDone+n, false);
    map<int, int> finish_map;
    int jobDone = 0,curTime=start_time[0],minRemSer;
     int p;

    do{
        minRemSer = 1000;
         for (int i = 0; i < n; i++) {
            if(isDone[i]==false && start_time[i]<=curTime) {
                if(service_time[i] < minRemSer){
                    minRemSer = service_time[i];
                     p = i;
            } if(service_time[i] == minRemSer){
                if(start_time[i] < start_time[p]){
                    minRemSer = service_time[i];
                    p = i;
                }
            }
        }
   
    } 

        if(service_time[p]>0){
        freq_sequence.push_back(p);
        service_time[p]--;
        }
        curTime++;
        if(service_time[p]==0 && isDone[p]==false) {
                jobDone++;
                finish_time[p] = curTime;
                finish_map[p]=finish_time[p];
                isDone[p]=true;
                }

    } while(jobDone!=n);

      for (int i = 0; i < n; i++)
    {
        finish_time[i] = finish_map[i];
        turnaround[i] = finish_time[i] - start_time[i];
        wait_time[i] = turnaround[i] - service_time[i];
        normturn[i] = (float)turnaround[i] / (float)sst[i];
    }

    static vector<int> resultSRN[5];
    resultSRN[0] = finish_time;
    resultSRN[1] = turnaround;
    resultSRN[2] = wait_time;
    resultSRN[3] = normturn;
    resultSRN[4] = freq_sequence;
    
    return resultSRN;

}

void SRNtrace(vector<int> result_freq_seq, vector<int> finish_time, vector<int> service_time,vector<int> start_time ,vector<char> processes_name , int n, int maxtime){
    vector<int> freq_sequence = result_freq_seq;
    vector< vector<char> > status(n, vector<char>(maxtime, ' ')); // play board
    vector<int> finish = finish_time;
  
    for(int i = 0 ; i < status[0].size();i++){  //0 1 2 3 4 ....
        for(int x = 0 ; x < status.size();x++){ //A B C D E
            if(finish[x] > i && start_time[x] <= i) status[x][i] = '.'; //  finish > i >= start time
        }
    }
   for(int i = 0, k = start_time[0]; i < freq_sequence.size() && k < (freq_sequence.size()+start_time[0]) ; i++, k++){
        status[freq_sequence[i]][k] = '*';
    }

    cout << "SRT" <<"   ";
    for (int i = 0; i <= maxtime; i++)
        cout << i % 10 << " ";
    cout << "\n";
    cout << "------";
    for (int i = 0; i <= maxtime * 2; i++)
        cout << "-";
    cout << "-\n";
    for (int i = 0; i < status.size(); i++)
    {
        cout << processes_name[i] << "     |";
        for (int x = 0; x < status[i].size(); x++)
        {
            cout << status[i][x] << "|";
        }
        cout << " \n";
    }
    cout << "------";
    for (int i = 0; i <= maxtime * 2; i++)
        cout << "-";
    cout << "-\n";
    cout << endl;
}

void SRNstats(vector<int> turnaround,vector<int>normturn ,vector<int> finish_time, vector<int> service_time,vector<int> start_time ,vector<char> processes_name , int n, int maxtime){
float avgN,avgT;
int avgNorm=0,avgturn=0;
vector<int> ss= service_time;
vector< vector<char> > stats(n, vector<char>(maxtime,' '));
    cout << "SRT";
  cout << "\nProcess    |" <<"";
  for (int i = 0; i < stats.size(); i++)
    {cout <<std::setw(3)<<processes_name[i] <<"  |";
         }
          cout << "\nArrival    |";
  for (int i = 0; i < stats.size(); i++)
    {cout <<std::setw(3)<<start_time[i] <<"  |";
         }
 cout << "\nService    |" ;
  for (int i = 0; i < stats.size(); i++)
    {
        cout <<std::setw(3)<<ss[i] <<"  |";


         }cout << " Mean|";


    cout << "\nFinish     |" <<"";
  for (int i = 0; i < stats.size(); i++)
    {cout <<std::setw(3)<<finish_time[i] <<"  |";

         }cout << "-----|";
  cout << "\nTurnaround |" <<"";
  for (int i = 0; i < stats.size(); i++)
    {
       cout <<std::setw(3)<<turnaround[i] <<"  |";
         avgturn=avgturn+ turnaround[i];
      avgT=(float)avgturn/(float)n;
         }
         cout << fixed << setprecision(2)<<std::setw(5) << avgT<<"|";

cout << "\nNormTurn   |";
  for (int i = 0; i < stats.size(); i++)
    { vector<float>m(n); m[i] = (float)turnaround[i] / (float)ss[i];
avgNorm+=m[i];
        avgN=(float)avgNorm/(float)n;

     cout<<" "<<fixed<<std::setw(4)<<setprecision(2)<< m[i]<<"|";
             }
         cout << fixed << setprecision(2)<<std::setw(5) << avgN<<"|";

cout << "\n";
cout << endl;   

}

vector<int>* HRRN(vector<int> start_time, vector<int> service_time,int n, int maxtime){
    vector<int> proc_sequence;
    vector<int> finish_time(n) , turnaround(n) , wait_time(n) , normturn(n);
    vector<char> processes_name(n);
    vector<int>  ss = service_time;
    bool isDone[n];
    fill(isDone, isDone+n, false);
    map<int, int> finish_map;
    int jobDone = 0, curTime=start_time[0];
    float hrrval, hrrtemp;
    int p;
    int i,j,tem;
     for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {

            // sort by start__time
            if (start_time[i] > start_time[j]) {

                
                tem = start_time[i];
                start_time[i] = start_time[j];
                start_time[j] = tem;
            }
        }
    }
        do{
            hrrval = -1000;
            for (int id = 0; id < n; id++) {

            
            if (start_time[id] <= curTime && isDone[id]==false) {

                // Equation of HRR
                hrrtemp = (service_time[id] + (curTime - start_time[id])) / service_time[id];

                
                if (hrrval < hrrtemp) {

                   
                    hrrval = hrrtemp;

                    
                    p = id;

                }
            }
        }

        curTime += service_time[p];
        proc_sequence.push_back(p);
        finish_time[p] = curTime;
        finish_map[p]=finish_time[p];
        isDone[p] = true;
        jobDone++;

    } while(jobDone!=n);

      for (int i = 0; i < n; i++)
    {
        finish_time[i] = finish_map[i];
        turnaround[i] = finish_time[i] - start_time[i];
        wait_time[i] = turnaround[i] - service_time[i];
        normturn[i] = (float)turnaround[i] / (float)ss[i];
    }

    static vector<int> resultHRRN[5];
    resultHRRN[0] = finish_time;
    resultHRRN[1] = turnaround;
    resultHRRN[2] = wait_time;
    resultHRRN[3] = normturn;
    resultHRRN[4] = proc_sequence;
    
    return resultHRRN;
}


void HRRNtrace(vector<int> result_proc_seq, vector<int> finish_time, vector<int> service_time,vector<int> start_time ,vector<char> processes_name , int n, int maxtime){
   
    vector<int> proc_sequence = result_proc_seq;
    vector<int> freq_sequence;
    vector< vector<char> > status(n, vector<char>(maxtime, ' ')); // Result Board
    vector<int>  temp  = service_time;
    vector<int> finish = finish_time;
    for(int i = 0 ; i < proc_sequence.size();i++){
        for(int x = 0 ; x < temp[proc_sequence[i]] ; x++) {
        freq_sequence.push_back(proc_sequence[i]);
        }
    }
    for(int i = 0 ; i < status[0].size();i++){  //0 1 2 3 4 ....
        for(int x = 0 ; x < status.size();x++){ //A B C D E
            if(finish[x] > i && start_time[x] <= i) status[x][i] = '.'; //  finish > i >= start time
        }
    }
     for(int i = 0, k = start_time[0]; i < freq_sequence.size() && k < (freq_sequence.size()+start_time[0]) ; i++, k++){
        status[freq_sequence[i]][k] = '*';
    }

    cout << "HRRN" <<"  ";
    for (int i = 0; i <= maxtime; i++)
        cout << i % 10 << " ";
    cout << "\n";
    cout << "------";
    for (int i = 0; i <= maxtime * 2; i++)
        cout << "-";
    cout << "-\n";
    for (int i = 0; i < status.size(); i++)
    {
        cout << processes_name[i] << "     |";
        for (int x = 0; x < status[i].size(); x++)
        {
            cout << status[i][x] << "|";
        }
        cout << " \n";
    }
    cout << "------";
    for (int i = 0; i <= maxtime * 2; i++)
        cout << "-";
    cout << "-\n";
    cout << endl;

}

void HRRNstats(vector<int> turnaround,vector<int>normturn ,vector<int> finish_time, vector<int> service_time,vector<int> start_time ,vector<char> processes_name , int n, int maxtime){
float avgN,avgT;
int avgNorm=0,avgturn=0;
vector<int> ss= service_time;
vector< vector<char> > stats(n, vector<char>(maxtime,' '));
    cout << "HRRN";
  cout << "\nProcess    |" <<"";
  for (int i = 0; i < stats.size(); i++)
    {cout <<std::setw(3)<<processes_name[i] <<"  |";
         }
          cout << "\nArrival    |";
  for (int i = 0; i < stats.size(); i++)
    {cout <<std::setw(3)<<start_time[i] <<"  |";
         }
 cout << "\nService    |" ;
  for (int i = 0; i < stats.size(); i++)
    {
        cout <<std::setw(3)<<ss[i] <<"  |";


         }cout << " Mean|";


    cout << "\nFinish     |" <<"";
  for (int i = 0; i < stats.size(); i++)
    {cout <<std::setw(3)<<finish_time[i] <<"  |";

         }cout << "-----|";
  cout << "\nTurnaround |" <<"";
  for (int i = 0; i < stats.size(); i++)
    {
       cout <<std::setw(3)<<turnaround[i] <<"  |";
         avgturn=avgturn+ turnaround[i];
      avgT=(float)avgturn/(float)n;
         }
         cout << fixed << setprecision(2)<<std::setw(5) << avgT<<"|";

cout << "\nNormTurn   |";
  for (int i = 0; i < stats.size(); i++)
    { vector<float>m(n); m[i] = (float)turnaround[i] / (float)ss[i];
avgNorm+=m[i];
        avgN=(float)avgNorm/(float)n;

     cout<<" "<<fixed<<std::setw(4)<<setprecision(2)<< m[i]<<"|";
             }
         cout << fixed << setprecision(2)<<std::setw(5) << avgN<<"|";

cout << "\n";
cout << endl;   

}

vector<int>* RR(vector<int> start_time, vector<int> service_time,int n, int maxtime, int inp_Qtm){
    vector<int> finish_time(n) , turnaround(n) , wait_time(n) , normturn(n);
    vector<char> processes_name(n);
    vector<int> proc_sequence;
    vector<int>  ss = service_time; //?
    bool inQueue[n+1];
    fill(inQueue, inQueue+n+1, false);
    map<int, int> id_compl; //?
    int jobDone = 0,curTime=start_time[0];
    queue<int> ready_queue;
    do {
        for (int i = 0; i < n; ++i) {
            if(!inQueue[i] && start_time[i]==curTime) {//
                ready_queue.push(i);
                inQueue[i]=true;
            }
        }
        if(!ready_queue.empty()) {
            proc_sequence.push_back(ready_queue.front()); //realy excute
            int  p = ready_queue.front();
            ready_queue.pop();
            int calcQtm = min(inp_Qtm, service_time[p]);
           // int b=service_time[p]; //?
            service_time[p] = service_time[p]-calcQtm;
            for (int i = curTime+1; i <= curTime+calcQtm; ++i) //?
            {
                for (int j = 0; j < n; ++j)
                {
                    if(!inQueue[j] && start_time[j]==i) {
                        ready_queue.push(j);
                        inQueue[j]=true;
                    }
                }
            }
            curTime += calcQtm; //?
            if( service_time[p]==0) {
                jobDone++;
                finish_time[p] = curTime;
                id_compl[p]=finish_time[p];
            } else {
                ready_queue.push(p);
            }
        } else {
            curTime++;
        }
    } while(jobDone!=n);


    for (int i = 0; i < n; ++i)
    {
        finish_time[i] = id_compl[i];
        turnaround[i] = finish_time[i] - start_time[i];
        wait_time[i] = turnaround[i] - service_time[i];
        normturn[i] = (float)turnaround[i] / (float)ss[i];
    }

    static vector<int> resultRR[5];
    resultRR[0] = finish_time;
    resultRR[1] = turnaround;
    resultRR[2] = wait_time;
    resultRR[3] = normturn;
    resultRR[4] = proc_sequence;
    
    return resultRR;
    
}

void RRtrace(vector<int> result_proc_seq, vector<int> finish_time, vector<int> service_time,vector<int> start_time ,vector<char> processes_name , int n, int maxtime, int inp_Qtm){
    vector< vector<char> > status(n, vector<char>(maxtime, ' ')); //playboard
    vector<int> proc_sequence = result_proc_seq;
    vector<int>  temp  = service_time;
    vector<int> finish = finish_time;
    vector<int> freq_sequence;
    for(int i = 0 ; i < proc_sequence.size();i++){
        if(temp[proc_sequence[i]] > inp_Qtm){
            for(int x = 0 ; x < inp_Qtm ; x++) freq_sequence.push_back(proc_sequence[i]);
            temp[proc_sequence[i]] = temp[proc_sequence[i]] - inp_Qtm;
        }else if(temp[proc_sequence[i]] <= inp_Qtm){
            for(int x = 0 ; x < temp[proc_sequence[i]] ; x++) freq_sequence.push_back(proc_sequence[i]);
            temp[proc_sequence[i]] = 0;
        }
    }
    for(int i = 0 ; i < status[0].size();i++){  //0 1 2 3 4 ....
        for(int x = 0 ; x < status.size();x++){ //A B C D E
            if(finish[x] > i && start_time[x] <= i) status[x][i] = '.'; //  finish > i >= start time
        }
    }
     for(int i = 0, k = start_time[0]; i < freq_sequence.size() && k < (freq_sequence.size()+start_time[0]) ; i++, k++){
        status[freq_sequence[i]][k] = '*';
    }

    cout << "RR-" <<inp_Qtm<<"  ";
    for (int i = 0; i <= maxtime; i++)
        cout << i % 10 << " ";
    cout << "\n";
    cout << "------";
    for (int i = 0; i <= maxtime * 2; i++)
        cout << "-";
    cout << "-\n";
    for (int i = 0; i < status.size(); i++)
    {
        cout << processes_name[i] << "     |";
        for (int x = 0; x < status[i].size(); x++)
        {
            cout << status[i][x] << "|";
        }
        cout << " \n";
    }
    cout << "------";
    for (int i = 0; i <= maxtime * 2; i++)
        cout << "-";
    cout << "-\n";
    cout << endl;


}

void RRstats(vector<int> turnaround,vector<int>normturn ,vector<int> finish_time, vector<int> service_time,vector<int> start_time ,vector<char> processes_name , int n, int maxtime,int inp_Qtm){
float avgN,avgT;
int avgNorm=0,avgturn=0;
vector<int> ss= service_time;
vector< vector<char> > stats(n, vector<char>(maxtime,' '));
    cout << "RR-" <<inp_Qtm;
  cout << "\nProcess    |" <<"";
  for (int i = 0; i < stats.size(); i++)
    {cout <<std::setw(3)<<processes_name[i] <<"  |";
         }
          cout << "\nArrival    |";
  for (int i = 0; i < stats.size(); i++)
    {cout <<std::setw(3)<<start_time[i] <<"  |";
         }
 cout << "\nService    |" ;
  for (int i = 0; i < stats.size(); i++)
    {
        cout <<std::setw(3)<<ss[i] <<"  |";


         }cout << " Mean|";


    cout << "\nFinish     |" <<"";
  for (int i = 0; i < stats.size(); i++)
    {cout <<std::setw(3)<<finish_time[i] <<"  |";

         }cout << "-----|";
  cout << "\nTurnaround |" <<"";
  for (int i = 0; i < stats.size(); i++)
    {
       cout <<std::setw(3)<<turnaround[i] <<"  |";
         avgturn=avgturn+ turnaround[i];
      avgT=(float)avgturn/(float)n;
         }
         cout << fixed << setprecision(2)<<std::setw(5) << avgT<<"|";

cout << "\nNormTurn   |";
  for (int i = 0; i < stats.size(); i++)
    { vector<float>m(n); m[i] = (float)turnaround[i] / (float)ss[i];
avgNorm+=m[i];
        avgN=(float)avgNorm/(float)n;

     cout<<" "<<fixed<<std::setw(4)<<setprecision(2)<< m[i]<<"|";
             }
         cout << fixed << setprecision(2)<<std::setw(5) << avgN<<"|";

cout << "\n";
cout << endl;   

}

vector<int>* SPN(vector<int> start_time, vector<int> service_time,int n, int maxtime){
    vector<int> finish_time(n) , turnaround(n) , wait_time(n) , normturn(n);
    vector<char> processes_name(n);
    vector<int>  ss = service_time;
    vector<int>  proc_sequence;
    bool isDone[n];
    fill(isDone, isDone+n, false);
    map<int, int> finish_map;

 

    int jobDone = 0,curTime=start_time[0],minRemSer;
     int p;

    do{
        minRemSer = 1000;
         for (int i = 0; i < n; i++) {
            if(isDone[i]==false && start_time[i]<=curTime) {
                if(service_time[i] < minRemSer){
                    minRemSer = service_time[i];
                     p = i;
            } if(service_time[i] == minRemSer){
                if(start_time[i] <= start_time[p]){
                    minRemSer = service_time[i];
                    p = i;
                }
            }
        }
    
    } 

        curTime += service_time[p];
        proc_sequence.push_back(p);
        finish_time[p] = curTime;
        finish_map[p]=finish_time[p];
        isDone[p] = true;
        jobDone++;

    } while(jobDone!=n);

      for (int i = 0; i < n; i++)
    {
        finish_time[i] = finish_map[i];
        turnaround[i] = finish_time[i] - start_time[i];
        wait_time[i] = turnaround[i] - service_time[i];
        normturn[i] = (float)turnaround[i] / (float)ss[i];

    }

    static vector<int> resultSPN[5];
    resultSPN[0] = finish_time;
    resultSPN[1] = turnaround;
    resultSPN[2] = wait_time;
    resultSPN[3] = normturn;
    resultSPN[4] = proc_sequence;
    
    return resultSPN;


}
    //////////////////////////////////////////////////


void SPNtrace(vector<int> result_proc_seq, vector<int> finish_time, vector<int> service_time,vector<int> start_time ,vector<char> processes_name , int n, int maxtime){

    vector< vector<char> > status(n, vector<char>(maxtime, ' ')); // Result Board
    vector<int>  temp  = service_time;
    vector<int> finish = finish_time;
    vector<int> proc_sequence = result_proc_seq;
    vector<int> freq_sequence;
    for(int i = 0 ; i < proc_sequence.size();i++){
        for(int x = 0 ; x < temp[proc_sequence[i]] ; x++) {
        freq_sequence.push_back(proc_sequence[i]);
        }
    }
    for(int i = 0 ; i < status[0].size();i++){  //0 1 2 3 4 ....
        for(int x = 0 ; x < status.size();x++){ //A B C D E
            if(finish[x] > i && start_time[x] <= i) status[x][i] = '.'; //  finish > i >= start time
        }
    }
     for(int i = 0, k = start_time[0]; i < freq_sequence.size() && k < (freq_sequence.size()+start_time[0]) ; i++, k++){
        status[freq_sequence[i]][k] = '*';
    }

  cout << "SPN" <<"   ";
    for (int i = 0; i <= maxtime; i++)
        cout << i % 10 << " ";
    cout << "\n";
    cout << "------";
    for (int i = 0; i <= maxtime * 2; i++)
        cout << "-";
    cout << "-\n";
    for (int i = 0; i < status.size(); i++)
    {
        cout << processes_name[i] << "     |";
        for (int x = 0; x < status[i].size(); x++)
        {
            cout << status[i][x] << "|";
        }
        cout << " \n";
    }
    cout << "------";
    for (int i = 0; i <= maxtime * 2; i++)
        cout << "-";
    cout << "-\n";
    cout << endl;
}

    ////////////////////////////////////////////////////////

void SPNstats(vector<int> turnaround,vector<int>normturn ,vector<int> finish_time, vector<int> service_time,vector<int> start_time ,vector<char> processes_name , int n, int maxtime){
  float avgN,avgT;
    int avgNorm=0,avgturn=0;
    vector<int> ss = service_time;
    vector< vector<char> > stats(n, vector<char>(maxtime,' '));
    cout << "SPN";
    cout << "\nProcess    |" <<"";
  for (int i = 0; i < stats.size(); i++)
    {cout <<std::setw(3)<<processes_name[i] <<"  |";
         }
          cout << "\nArrival    |";
  for (int i = 0; i < stats.size(); i++)
    {cout <<std::setw(3)<<start_time[i] <<"  |";
         }
 cout << "\nService    |" ;
  for (int i = 0; i < stats.size(); i++)
    {
        cout <<std::setw(3)<<ss[i] <<"  |";


         }cout << " Mean|";


    cout << "\nFinish     |" <<"";
  for (int i = 0; i < stats.size(); i++)
    {cout <<std::setw(3)<<finish_time[i] <<"  |";

         }cout << "-----|";
  cout << "\nTurnaround |" <<"";
  for (int i = 0; i < stats.size(); i++)
    {
       cout <<std::setw(3)<<turnaround[i] <<"  |";
         avgturn=avgturn+ turnaround[i];
      avgT=(float)avgturn/(float)n;
         }
         cout << fixed << setprecision(2)<<std::setw(5) << avgT<<"|";

cout << "\nNormTurn   |";
  for (int i = 0; i < stats.size(); i++)
    { vector<float>m(n); m[i] = (float)turnaround[i] / (float)ss[i];
avgNorm+=m[i];
        avgN=(float)avgNorm/(float)n;

     cout<<" "<<fixed<<std::setw(4)<<setprecision(2)<< m[i]<<"|";
             }
         cout << fixed << setprecision(2)<<std::setw(5) << avgN<<"|";

cout << "\n";
cout << endl;     

}

vector<int>* FB2i(vector<int> start_time, vector<int> service_time,int n, int maxtime){
    vector<int> finish_time(n) , turnaround(n) , normturn(n);
    vector<char> processes_name(n);
    vector<int>  ss = service_time;
    vector<int> proc_sequence;
    int curtimer = start_time[0];
    int pros = 0;
    vector<queue<int>> v(n);
    v[0].push(0);proc_sequence.push_back(0);service_time[0]--;
    pros++;curtimer++;
    finish_time[0]=curtimer;
    if(start_time[1] > 1) {
        v[0].pop();
        v[0].push(0);
    }


  while (true)
    {
      int loc = 0;
      int flag = 0;
      for (int i = 0; i < n; i++)
	{
	  if (!v[i].empty ())
	    {
	      flag = 1;
	      break;
	    }
	}
      if (flag == 0)
	break;
      if (start_time[pros] <= curtimer)
	{
	  v[0].push (pros);
	  pros++;
	}
      loc = 0;
      while (loc < n)
	{
	  int q = pow (2, loc);
	  if (v[loc].empty ())
	    {
	      loc++;
	      continue;
	    }
	  if (service_time[v[loc].front ()] < q)
	    {
	      q = service_time[v[loc].front ()];
	      for (int i = 0; i < q; i++)
		{
		  
		  proc_sequence.push_back (v[loc].front ());
		  service_time[v[loc].front ()]--;
		  curtimer++;
		  if( service_time[v[loc].front ()]==0){
		      finish_time[v[loc].front ()]=curtimer;
		     
		  }
		} 

	    }
	  else
	    {
	      for (int i = 0; i < q; i++)
		{
		  proc_sequence.push_back (v[loc].front ());
		  service_time[v[loc].front ()]--;

		  curtimer++;
		}
	    }
	  if (service_time[v[loc].front ()] > 0)
	    {
	      if (loc + 1 < n)
		{
		  v[loc + 1].push (v[loc].front ());
		}
	      else
		{
		  v[loc].push (v[loc].front ());
		}
	    }
	  v[loc].pop ();
	  break;

	}
    }
      for (int i = 0; i < n; ++i)
    {
      
        turnaround[i] = finish_time[i] - start_time[i];
        normturn[i] = (float)turnaround[i] / (float)ss[i];
    }

    static vector<int> resultFB2i[4];
    resultFB2i[0] = finish_time;
    resultFB2i[1] = turnaround;
    resultFB2i[2] = proc_sequence;
    resultFB2i[3] = normturn;
  
    
    return resultFB2i;

}

//////////////////////////////////////////////////////////////////////////////////
void FB2itrace(vector<int> result_proc_seq, vector<int> finish_time, vector<int> service_time,vector<int> start_time ,vector<char> processes_name , int n, int maxtime){
    vector < int >finish = finish_time;
    vector<int> proc_sequence = result_proc_seq;
    vector < vector < char >>status (n, vector < char >(maxtime, ' '));	//playboard
  //vector < int >freq_sequence;

  for (int i = 0; i < status[0].size (); i++)
    {				//0 1 2 3 4 ....
      for (int x = 0; x < status.size (); x++)
	{			//A B C D E
	  if (finish_time[x] > i && start_time[x] <= i)
	    status[x][i] = '.';	//  finish > i >= start time
	}
    }

     for(int i = 0, k = start_time[0]; i < proc_sequence.size() && k < (proc_sequence.size()+start_time[0]) ; i++, k++){
        status[proc_sequence[i]][k] = '*';
    }
  //for (int i = 0; i < proc_sequence.size (); i++)
   // {
   //   status[proc_sequence[i]][i] = '*';
   // }

  cout << "FB-2i" << " ";
  for (int i = 0; i <= maxtime; i++)
    cout << i % 10 << " ";
  cout << "\n";
  cout << "------";
  for (int i = 0; i <= maxtime * 2; i++)
    cout << "-";
  cout << "-\n";
  for (int i = 0; i < status.size (); i++)
    {
      cout << processes_name[i] << "     |";
      for (int x = 0; x < status[i].size (); x++)
	{
	  cout << status[i][x] << "|";
	}
      cout << " \n";
    }
  cout << "------";
  for (int i = 0; i <= maxtime * 2; i++)
    cout << "-";
  cout << "-\n";
  cout << endl;
}

/////////////////////////////////////////////////////////
void FB2istats(vector<int> turnaround,vector<int>normturn ,vector<int> finish_time, vector<int> service_time,vector<int> start_time ,vector<char> processes_name , int n, int maxtime){
float avgN,avgT;
int avgNorm=0,avgturn=0;
vector<int> ss= service_time;
vector< vector<char> > stats(n, vector<char>(maxtime,' '));
    cout << "FB-2i";
  cout << "\nProcess    |" <<"";
  for (int i = 0; i < stats.size(); i++)
    {cout <<std::setw(3)<<processes_name[i] <<"  |";
         }
          cout << "\nArrival    |";
  for (int i = 0; i < stats.size(); i++)
    {cout <<std::setw(3)<<start_time[i] <<"  |";
         }
 cout << "\nService    |" ;
  for (int i = 0; i < stats.size(); i++)
    {
        cout <<std::setw(3)<<ss[i] <<"  |";


         }cout << " Mean|";


    cout << "\nFinish     |" <<"";
  for (int i = 0; i < stats.size(); i++)
    {cout <<std::setw(3)<<finish_time[i] <<"  |";

         }cout << "-----|";
  cout << "\nTurnaround |" <<"";
  for (int i = 0; i < stats.size(); i++)
    {
       cout <<std::setw(3)<<turnaround[i] <<"  |";
         avgturn=avgturn+ turnaround[i];
      avgT=(float)avgturn/(float)n;
         }
         cout << fixed << setprecision(2)<<std::setw(5) << avgT<<"|";

cout << "\nNormTurn   |";
  for (int i = 0; i < stats.size(); i++)
    { vector<float>m(n); m[i] = (float)turnaround[i] / (float)ss[i];
avgNorm+=m[i];
        avgN=(float)avgNorm/(float)n;

     cout<<" "<<fixed<<std::setw(4)<<setprecision(2)<< m[i]<<"|";
             }
         cout << fixed << setprecision(2)<<std::setw(5) << avgN<<"|";

cout << "\n";
cout << endl;   

}




//move processes to diff queues
//process takes too much time move to lower priority queue



vector<int>* FB(vector<int> start_time, vector<int> service_time,int n, int maxtime){

vector < int >proc_sequence;
map<int, int> comp;
vector < int >finish_time (n), wait_time (n), flag (n + 1), normturn (n), turnaround (n);
vector < char >processes_name (n);   
vector<int>  ss = service_time;
int curTime = start_time[0];
int pros = 0;
vector<queue<int>> v(n);

    v[0].push(0);
    proc_sequence.push_back(0);service_time[0]--;
    pros++;curTime++;
    finish_time[0]=curTime;

    if(start_time[1] > 1) {
        v[0].pop();
        v[0].push(0);
    }



  while (true)
    {
      int loc = 0;
      int flag = 0;
      for (int i = 0; i < n; i++)
	{
	  if (!v[i].empty ())
	    {
	      flag = 1;
	      break;
	    }
	}
      if (flag == 0)
	break;
      if (start_time[pros] <= curTime)
	{
	  v[0].push (pros);
	  pros++;
	}
      loc = 0;
      while (loc < n)
	{
	  int q = pow (2, 0);
	  if (v[loc].empty ())
	    {
	      loc++;
	      continue;
	    }
	  if (service_time[v[loc].front ()] <= 1)
	    {
	      q = service_time[v[loc].front ()];
	      for (int i = 0; i < q; i++)
		{
		
		  proc_sequence.push_back (v[loc].front ());
		  service_time[v[loc].front ()]--;
		  curTime++;
		  if( service_time[v[loc].front ()]==0){
		      finish_time[v[loc].front ()]=curTime;
		     
		  }
		} 

	    }
	  else
	    {
	      for (int i = 0; i < q; i++)
		{
		  proc_sequence.push_back (v[loc].front ());
		  service_time[v[loc].front ()]--;

		  curTime++;
		}
	    }
	  if (service_time[v[loc].front ()] > 0)
	    {
	      if (loc + 1 < n)
		{
		  v[loc + 1].push (v[loc].front ());
		}
	      else
		{
		  v[loc].push (v[loc].front ());
		}
	    }
	  v[loc].pop ();
	  break;

	}
    }
      for (int i = 0; i < n; ++i)
    {
      
        turnaround[i] = finish_time[i] - start_time[i];
        normturn[i] = (float)turnaround[i] / (float)ss[i];
    }

    static vector<int> resultFB[4];
    resultFB[0] = finish_time;
    resultFB[1] = turnaround;
    resultFB[2] = normturn;
    resultFB[3] = proc_sequence;
    
    return resultFB;

   
}



//////////////////////////////////////////////////////////

void FBtrace(vector<int> result_proc_seq, vector<int> finish_time, vector<int> service_time,vector<int> start_time ,vector<char> processes_name , int n, int maxtime){
  vector < int >finish = finish_time;
  vector <int> proc_sequence = result_proc_seq;
  vector < vector < char >>status (n, vector < char >(maxtime, ' '));	//playboard

  for (int i = 0; i < status[0].size (); i++)
    {				//0 1 2 3 4 ....
      for (int x = 0; x < status.size (); x++)
	{			//A B C D E
	  if (finish_time[x] > i && start_time[x] <= i)
	    status[x][i] = '.';	//  finish > i >= start time
	}
    }

 for(int i = 0, k = start_time[0]; i < proc_sequence.size() && k < (proc_sequence.size()+start_time[0]) ; i++, k++){
        status[proc_sequence[i]][k] = '*';
    }
 // for (int i = 0; i < proc_sequence.size (); i++)
  //  {
  //    status[proc_sequence[i]][i] = '*';
  //  }

  cout << "FB-1" << "  ";
  for (int i = 0; i <= maxtime; i++)
    cout << i % 10 << " ";
  cout << "\n";
  cout << "------";
  for (int i = 0; i <= maxtime * 2; i++)
    cout << "-";
  cout << "-\n";
  for (int i = 0; i < status.size (); i++)
    {
      cout << processes_name[i] << "     |";
      for (int x = 0; x < status[i].size (); x++)
	{
	  cout << status[i][x] << "|";
	}
      cout << " \n";
    }
  cout << "------";
  for (int i = 0; i <= maxtime * 2; i++)
    cout << "-";
  cout << "-\n";
  cout << endl;

}

////////////////////////////////////////////////////////
void FBstats(vector<int> turnaround,vector<int>normturn ,vector<int> finish_time, vector<int> service_time,vector<int> start_time ,vector<char> processes_name , int n, int maxtime){
    vector< vector<char> > stats(n, vector<char>(maxtime,' '));
    float avgNorm=0.0,avgturn=0.0;
    float avgN,avgT;
    vector<int>ss = service_time;
    cout << "FB-1";
  cout << "\nProcess    |" <<"";
  for (int i = 0; i < stats.size(); i++)
    {cout <<std::setw(3)<<processes_name[i] <<"  |";
         }
          cout << "\nArrival    |";
  for (int i = 0; i < stats.size(); i++)
    {cout <<std::setw(3)<<start_time[i] <<"  |";
         }
 cout << "\nService    |" ;
  for (int i = 0; i < stats.size(); i++)
    {
        cout <<std::setw(3)<<ss[i] <<"  |";


         }cout << " Mean|";


    cout << "\nFinish     |" <<"";
  for (int i = 0; i < stats.size(); i++)
    {cout <<std::setw(3)<<finish_time[i] <<"  |";

         }cout << "-----|";
  cout << "\nTurnaround |" <<"";
  for (int i = 0; i < stats.size(); i++)
    {
       cout <<std::setw(3)<<turnaround[i] <<"  |";
         avgturn=avgturn+ turnaround[i];
      avgT=(float)avgturn/(float)n;
         }
         cout << fixed << setprecision(2)<<std::setw(5) << avgT<<"|";

cout << "\nNormTurn   |";
  for (int i = 0; i < stats.size(); i++)
    { vector<float>m(n); m[i] = (float)turnaround[i] / (float)ss[i];
avgNorm+=m[i];
        avgN=(float)avgNorm/(float)n;

     cout<<" "<<fixed<<std::setw(4)<<setprecision(2)<< m[i]<<"|";
             }
         cout << fixed << setprecision(2)<<std::setw(5) << avgN<<"|";

cout << "\n";
cout << endl;

}


