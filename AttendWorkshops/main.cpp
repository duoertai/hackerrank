#include <iostream>
using namespace std;


struct Workshop{
    int start_time;
    int duration;
    int end_time;
};

struct Available_Workshops{
    int n;
    Workshop* workshops;
} available_workshops;

Available_Workshops* initialize(int start_time[], int duration[], int n){
    Workshop* ws = new Workshop[n];

    for(int i = 0; i < n; i++){
        ws[i] = *(new Workshop);
        ws[i].start_time = start_time[i];
        ws[i].duration = duration[i];
        ws[i].end_time = start_time[i] + duration[i];
    }

    available_workshops = {n, ws};

    return &available_workshops;
}

int CalculateMaxWorkshops(Available_Workshops* ptr){
    extern bool cmp(Workshop a, Workshop b);
    sort(&(ptr->workshops[0]), &(ptr->workshops[ptr->n]), cmp);

    int res = 0;
    int prev_end = ptr->workshops[0].end_time;

    for(int i = 1; i < ptr->n; i++){
        if(ptr->workshops[i].start_time >= prev_end){
            res++;
            prev_end = ptr->workshops[i].end_time;
        }
        else{
            prev_end = min(prev_end, ptr->workshops[i].end_time);
        }
    }

    return res + 1;
}

bool cmp(Workshop a, Workshop b){
    return a.start_time < b.start_time;
}

int main(int argc, char *argv[]) {
    int n; // number of workshops
    cin >> n;
    // create arrays of unknown size n
    int* start_time = new int[n];
    int* duration = new int[n];

    for(int i=0; i < n; i++){
        cin >> start_time[i];
    }
    for(int i = 0; i < n; i++){
        cin >> duration[i];
    }

    Available_Workshops * ptr;
    ptr = initialize(start_time,duration, n);
    cout << CalculateMaxWorkshops(ptr) << endl;
    return 0;
}