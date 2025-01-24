#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <string>

using namespace std;

void FUNC_delay(int mili){this_thread::sleep_for(chrono::milliseconds(mili));}

void UI_exit(){
    system("cls");//!clear
    for(int i = 8; i >= 0; --i){
        cout << "                                               \\ \n ____________________________________________/_/\n/\n";
        for(int j = 1; j <= i; j++){cout << endl;}
        cout << "\\____________________________________________.o@< .oA";
        this_thread::sleep_for(chrono::milliseconds(50));
        if(i != 0){system("cls");}
        else if(i == 0){this_thread::sleep_for(chrono::milliseconds(200)); system("cls");}
    }
    exit(0);
}

void UI_hello(){
    system("cls");//!clear
    cout << ("H   H    EEEEE   L       L        OOOOO\n");
    cout << ("H   H    E       L       L       O     O\n");
    cout << ("H   H    E       L       L       O     O\n");
    cout << ("HHHHH    EEEEE   L       L       O     O\n");
    cout << ("H   H    E       L       L       O     O\n");
    cout << ("H   H    E       L       L       O     O\n");
    cout << ("H   H    EEEEE   LLLLL   LLLLL    OOOOO\n\n");
}

void UI_name(short clear){
    if(clear == 1){system("cls");}
    cout << "\n\t\t\\__________________/ \n\t\t/                  \\ \n\t\t|| @ gonna hunt A ||\n\t\t\\__________________/ \n\t\t/                  \\  .o@< .oA \n\n";
}

void UI_cover(string option){
    if(option.compare("upper") == 0){cout << "                                               \\ \n ____________________________________________/_/\n/\n";}
    if(option.compare("lower") == 0){cout << "\n\n\\____________________________________________.o@< .oA";}
}

void UI_loadingBar(){
    const int total_steps = 35;
    int current_step = 0;
    cout << "Loading...";
    while (current_step <= total_steps) {
        cout << "\rLoading[" << string(current_step, '>') << string(total_steps - current_step, ' ') << "]"; 
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(10));
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

//------------------
void startMenu();//*rendered start menu and require the chosen
void credits();//*to reveal credits aboutu this project
void choosingMode();//*to choose mode before start playing
//------------------

//------------------
class map{
    public:
    int easy_map[36] = {1,1,1,1,1,1,
                        1,0,0,0,0,1,
                        1,0,1,1,0,1,
                        1,0,1,0,0,1,
                        1,0,0,0,0,1,
                        1,1,1,1,1,1};
    //todo: learn more about class and arraying for mapping
};
//------------------

int main(){
    UI_hello();
    FUNC_delay(1000);
    UI_name(1);
    FUNC_delay(200);
    UI_loadingBar();
    UI_cover("upper");
    cout << "\n\tPress Enter..\n\n\n"; getchar();
    //----------------------
    startMenu();
}

void startMenu(){
    string choice1;
    int checker_1st_time = 0;
    while(1){
        system("cls");//!clear
        UI_cover("upper");
        cout << "  START MENU" << endl << endl;
        if(checker_1st_time != 1){FUNC_delay(200);}
        cout << "\t1] Guider gameplay" << endl
             << "\t2] Start match" << endl
             << "\t3] Credits" << endl
             << "\t4] Leave" << endl << endl;
        FUNC_delay(200);
        if(checker_1st_time == 1){checker_1st_time = 0; cout << "\t\t! [Only 1 - 4]" << endl;}
        cout << "\t\t=] "; cin >> choice1;
        if(choice1.compare("1") == 0 || choice1.compare("2") == 0 
        || choice1.compare("3") == 0 || choice1.compare("4") == 0){getchar(); break;}
        checker_1st_time = 1;
    }
    switch(choice1[0]){
        case '1':startMenu();
        break;
        case '2':choosingMode();
        break;
        case '3':credits();
        break;
        case '4':UI_exit();
        break;
    }
}

void credits(){
    system("cls");//!clear
    cout << "\n\n\n/====================================\\" << endl;
    cout << "\\====================================/" << endl;
    FUNC_delay(200);
    system("cls");//!clear
    cout << "\n/====================================\\" << endl;
    cout << "\n\n\n\\====================================/" << endl;
    FUNC_delay(200);
    system("cls");//!clear
    cout << "/====================================\\" << endl;
    cout << " Credits about this project           " << endl;
    cout << " named \"@ gonna hunt A\"               " << endl;
    cout << " ------------------------------------ " << endl;
    cout << " Owner : Saki (Kitartist Riabroi)     " << endl;
    cout << " Discord ID : @kotorisaki             " << endl;
    cout << " Github : KOTORiSAKi                  " << endl;
    cout << "\\====================================/" << endl;
    FUNC_delay(100);
    cout << endl << endl << "Press Enter.."; getchar();
    system("cls");//!clear
    cout << "\n/====================================\\" << endl;
    cout << "\n\n\n\\====================================/" << endl;
    FUNC_delay(200);
        system("cls");//!clear
    cout << "\n\n\n/====================================\\" << endl;
    cout << "\\====================================/" << endl;
    FUNC_delay(400);
    startMenu();
}

void choosingMode(){
    string choice1;
    int checker_1st_time = 0;
    while(1){
        system("cls");//!clear
        if(checker_1st_time != 1){FUNC_delay(200);}
        UI_cover("upper");
        cout << "  CHOOSING MODE" << endl << endl; 
        cout << "\t1] Easy" << endl
             << "\t2] Medium" << endl
             << "\t3] Hard\n" << endl
             << "\t4] Back" << endl;
        FUNC_delay(200);
        if(checker_1st_time == 1){checker_1st_time = 0; cout << "\t\t! [Only 1 - 4]" << endl;}
        cout << "\t\t=] "; cin >> choice1;
        if(choice1.compare("1") == 0 || choice1.compare("2") == 0 
        || choice1.compare("3") == 0 || choice1.compare("4") == 0){getchar(); break;}
        checker_1st_time = 1;
    }
    switch(choice1[0]){
        case '1':choosingMode();
        break;
        case '2':choosingMode();
        break;
        case '3':choosingMode();
        break;
        case '4':startMenu();
        break;
    }
}