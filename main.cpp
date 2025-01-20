#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>

using namespace std;

void UI_name(short clear){
    if(clear == 1){system("cls");}
    cout << "\n\t\t\\__________________/ \n\t\t/                  \\ \n\t\t|| @ gonna hunt A ||\n\t\t\\__________________/ \n\t\t/                  \\  .o@< .oA \n\n";
}
void UI_cover(string option){
    if(option.compare("upper") == 0){cout << "                                               \\ \n ____________________________________________/_/\n/\n\n";}
    if(option.compare("lower") == 0){cout << "\n\n\\____________________________________________.o@< .oA";}
}

void UI_loadingBar(){
    const int total_steps = 50;
    int current_step = 0;
    cout << "Loading...";
    while (current_step <= total_steps) {
        cout << "\rLoading[" << string(current_step, '>') << string(total_steps - current_step, ' ') << "]"; 
        cout.flush(); 

        this_thread::sleep_for(chrono::milliseconds(50)); // Adjust sleep duration for loading speed
        current_step++;
    }
    cout << "\r[";
    for (int i = 0; i < total_steps; i++) {
        cout << "#";
    }
    cout << "] 100\% loaded" << endl; 
    cout << "\nLoading complete!" << endl;
    this_thread::sleep_for(chrono::milliseconds(200));
}

int main(){
    UI_name(1);
    UI_loadingBar();
    UI_cover("upper");
    cout << "\tPress Enter..\n\n\n"; getchar();
    //----------------------
}