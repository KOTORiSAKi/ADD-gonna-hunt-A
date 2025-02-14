#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <windows.h> 

using namespace std;

void FUNC_delay(int mili){this_thread::sleep_for(chrono::milliseconds(mili));}

void setColor(int textColor) { 
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
    SetConsoleTextAttribute(hConsole, textColor); 
} 

void UI_exit(){
    system("cls");//!clear
    for(int i = 8; i >= 0; --i){
        cout << "                                               \\ \n ____________________________________________/_/\n/\n";
        for(int j = 1; j <= i; j++){cout << endl;}
        cout << "\n\n\\____________________________________________"; setColor(4); cout << ".o@< "; setColor(2); cout << ".oA"; setColor(7);
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
    if(option.compare("lower") == 0){cout << "\n\n\\____________________________________________"; setColor(4); cout << ".o@< "; setColor(2); cout << ".oA"; setColor(7);}
}

void UI_loadingBar(){
    const int total_steps = 35;
    int current_step = 0;
    setColor(4);
    cout << "Loading...";
    while (current_step <= total_steps) {
        cout << "\rLoading[" << string(current_step, '>') << string(total_steps - current_step, ' ') << "]"; 
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(10));
        current_step++;
    }
    setColor(2);
    cout << "\r[";
    for (int i = 0; i < total_steps; i++) {
        cout << "#";
    }
    cout << "] 100\% loaded" << endl; 
    cout << "\nLoading complete!" << endl;
    this_thread::sleep_for(chrono::milliseconds(200));
    setColor(7);
}

//------------------
void startMenu();//*rendered start menu and require the chosen
void credits();//*to reveal credits aboutu this project
void choosingMode();//*to choose mode before start playing
void main_logic(short);//*easy mode logics
void render_map(short,bool,short);//*to render map
void bot_brain(short);//*processing of bot
void win_game(short);//*when player win the game
void loss_game();//*when player loss the game
//------------------

//------------------
class map{
    public:
    bool easy[8][8] = {{0,0,0,0,0,0,0,0},
                      {0,1,1,1,1,1,1,1},//1
                      {0,1,0,0,0,0,0,1},//2
                      {0,1,0,0,1,0,0,1},//3
                      {0,1,0,1,0,0,0,1},//4
                      {0,1,0,0,0,0,1,1},//5
                      {0,1,0,0,0,0,1,1},//6
                      {0,1,1,1,1,1,1,1}};//7

    bool medium[13][13] = {{0,0,0,0,0,0,0,0,0,0,0,0,0},
                          {0,1,1,1,1,1,1,1,1,1,1,1,1},//1
                          {0,1,0,0,0,0,0,0,0,0,0,0,1},//2
                          {0,1,0,1,1,1,0,1,1,1,0,0,1},//3
                          {0,1,0,1,1,0,0,0,0,0,0,0,1},//4
                          {0,1,0,1,0,0,1,0,0,1,1,0,1},//5
                          {0,1,0,0,0,0,1,1,0,1,0,0,1},//6
                          {0,1,0,1,1,0,1,0,0,0,0,1,1},//7
                          {0,1,0,1,0,0,0,0,1,1,0,0,1},//8
                          {0,1,0,1,0,1,0,0,0,0,0,0,1},//9
                          {0,1,0,0,0,1,1,0,0,1,1,0,1},//10
                          {0,1,0,0,1,1,1,1,0,0,0,0,1},//11
                          {0,1,1,1,1,1,1,1,1,1,1,1,1}};//12
                          
    bool hard[18][18] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},//1
                        {0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1},//2
                        {0,1,0,1,1,0,0,0,0,1,1,1,1,0,1,1,0,1},//3
                        {0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,1,0,1},//4
                        {0,1,0,1,1,0,0,0,0,0,1,1,0,1,0,1,0,1},//5
                        {0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},//6
                        {0,1,1,1,0,0,1,1,0,1,1,1,1,0,0,1,0,1},//7
                        {0,1,0,0,0,0,1,0,0,0,1,1,0,0,0,1,0,1},//8
                        {0,1,0,1,1,0,1,0,0,0,0,1,0,1,0,0,0,1},//9
                        {0,1,0,0,1,0,1,1,0,1,0,0,0,1,0,1,0,1},//10
                        {0,1,0,0,1,0,0,0,0,0,0,1,0,1,0,1,0,1},//11
                        {0,1,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,1},//12
                        {0,1,0,0,0,0,1,0,1,0,0,1,1,1,0,1,1,1},//13
                        {0,1,0,1,1,0,0,0,0,0,1,1,1,1,0,0,0,1},//14
                        {0,1,0,0,0,0,1,1,1,0,0,0,0,0,1,1,0,1},//15
                        {0,1,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,1},//16
                        {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};//17
    //-------------------------------------------------------------------
    void guider();
};
//------------------
char door = 219;
short address_ad[2];
short address_A[2];
short address_end[2];
bool debugger1;
bool not_first_time_played = 0;

//------------------
void map::guider(){
    not_first_time_played = 1;
    map A;
    short maxSpace[4] = {0,7,12,17};
    system("cls");//!clear
    UI_cover("upper");
    FUNC_delay(200);
    cout << "\n\t[A] is player.     [@] is bot." << endl;
    cout << "\t[@] will follow [A]. Don't let [@] hunt you." << endl;
    cout << "\t " << door << " is your way to survive from [@]" << endl << endl;
    cout << "\t# is a wall block. So you can not stand there." << endl;
    cout << "\t. is a space block. So you can stand there." << endl;
    setColor(4);
    cout << "\tWarning! Bot may turn two times with random rate that beyorn to lvl you chose." << endl;
    setColor(7);
    cout << endl << "\tControl by WASD" << endl
         << "\tW -> go up" << endl
         << "\tA -> go left" << endl
         << "\tS -> go down" << endl
         << "\tD -> go right" << endl;
    cout << "\n\n\tExample for easy map" << endl << endl;
    for(int y = 1; y <= maxSpace[1]; y++){
        cout << "\t";
        for(int x = 1; x <= maxSpace[1]; x++){
            if(address_A[0] == y && address_A[1] == x){setColor(2);cout << " [A]";setColor(7);}
            else if(address_ad[0] == y && address_ad[1] == x){setColor(4);cout << " [@]";setColor(7);}
            else if(address_end[0] == y && address_end[1] == x){setColor(6);cout << "  " << door << " ";setColor(7);}
            else if(A.easy[y][x] == 1){cout << "  # ";}
            else if(A.easy[y][x] == 0){setColor(8);cout << "  . ";setColor(7);}
        }if(debugger1 == 1){setColor(8);cout << "  " << y << endl << endl;setColor(7);}else{cout << endl << endl;}
    }
    FUNC_delay(200);
    UI_cover("lower");
    cout << "\n\n\tPress Enter.."; getchar();
    startMenu();
}
//------------------

int main(){
    srand(time(0));
    //!---------------------
    UI_hello();
    FUNC_delay(1000);
    UI_name(1);
    FUNC_delay(200);
    UI_loadingBar();
    UI_cover("upper");
    cout << "\n\tPress Enter..\n\n\n"; getchar();
    system("color 07");
    //!----------------------
    startMenu();
}

void startMenu(){
    map A;
    string choice1;
    bool checker_1st_time = 0;
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
        if(choice1.compare("debugger1:activate") == 0){debugger1 = 1; checker_1st_time = 0;}
        if(choice1.compare("debugger1:deactivate") == 0){debugger1 = 0; checker_1st_time = 0;}
    }
    switch(choice1[0]){
        case '1': A.guider();
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
    short rate[4] = {0,10,25,30};
    bool checker_1st_time = 0;
    while(1){
        system("cls");//!clear
        if(checker_1st_time != 1){FUNC_delay(200);}
        UI_cover("upper");
        cout << "  CHOOSING MODE" << endl << endl; 
        cout << "\t1] Easy [" << rate[1] << "%]" << endl
             << "\t2] Medium [" << rate[2] << "%]" << endl
             << "\t3] Hard [" << rate[3] << "%]\n" << endl
             << "\t4] Back" << endl << endl
             << "\t\% is about how could it be two times bot may turn" << endl << endl;
        FUNC_delay(200);
        if(checker_1st_time == 1){checker_1st_time = 0; cout << "\t\t! [Only 1 - 4]" << endl;}
        cout << "\t\t=] "; cin >> choice1;
        if(choice1.compare("1") == 0 || choice1.compare("2") == 0 
        || choice1.compare("3") == 0 || choice1.compare("4") == 0){getchar(); break;}
        checker_1st_time = 1;
    }
    switch(choice1[0]){
        case '1':main_logic((short)1);
        break;
        case '2':main_logic((short)2);
        break;
        case '3':main_logic((short)3);
        break;
        case '4':startMenu();
        break;
    }
}

void render_map(short lvl, bool losser, short clicking){
    map A;
    short maxSpace[4] = {0,7,12,17};
    switch(lvl){
        case 1:
        for(int y = 1; y <= maxSpace[lvl]; y++){
            for(int x = 1; x <= maxSpace[lvl]; x++){
                if(address_A[0] == y && address_A[1] == x && losser != 1){setColor(2);cout << " [A]";setColor(7);}
                else if(address_ad[0] == y && address_ad[1] == x){setColor(4);cout << " [@]";setColor(7);}
                else if(address_end[0] == y && address_end[1] == x){setColor(6);cout << "  " << door << " ";setColor(7);}
                else if(A.easy[y][x] == 1){cout << "  # ";}
                else if(A.easy[y][x] == 0){setColor(8);cout << "  . ";setColor(7);}
            }if(debugger1 == 1){setColor(8);cout << "  " << y << endl << endl;setColor(7);}else{cout << endl << endl;}
        }
        if(debugger1 == 1){
            for(int x = 1; x <= maxSpace[lvl]; x++){
                if(x < 10){setColor(8);cout << "  " << x << " ";setColor(7);}
                else{setColor(8);cout << "  " << x;setColor(7);}
            }
            cout << endl;
        }
        break;
        case 2:
        for(int y = 1; y <= maxSpace[lvl]; y++){
            for(int x = 1; x <= maxSpace[lvl]; x++){
                if(address_A[0] == y && address_A[1] == x && losser != 1){setColor(2);cout << " [A]";setColor(7);}
                else if(address_ad[0] == y && address_ad[1] == x){setColor(4);cout << " [@]";setColor(7);}
                else if(address_end[0] == y && address_end[1] == x && clicking >= 3){setColor(6);cout << "  " << door << " ";setColor(7);}
                else if(A.medium[y][x] == 1){cout << "  # ";}
                else if(A.medium[y][x] == 0){setColor(8);cout << "  . ";setColor(7);}
            }if(debugger1 == 1){setColor(8);cout << "  " << y << endl << endl;setColor(7);}else{cout << endl << endl;}
        }
        if(debugger1 == 1){
            for(int x = 1; x <= maxSpace[lvl]; x++){
                if(x < 10){setColor(8);cout << "  " << x << " ";setColor(7);}
                else{setColor(8);cout << "  " << x;setColor(7);}
            }
            cout << endl;
        }
        break;
        case 3:
        for(int y = 1; y <= maxSpace[lvl]; y++){
            for(int x = 1; x <= maxSpace[lvl]; x++){
                if(address_A[0] == y && address_A[1] == x && losser != 1){setColor(2);cout << " [A]";setColor(7);}
                else if(address_ad[0] == y && address_ad[1] == x){setColor(4);cout << " [@]";setColor(7);}
                else if(address_end[0] == y && address_end[1] == x && clicking >= 8){setColor(6);cout << "  " << door << " ";setColor(7);}
                else if(A.hard[y][x] == 1){cout << "  # ";}
                else if(A.hard[y][x] == 0){setColor(8);cout << "  . ";setColor(7);}
            }if(debugger1 == 1){setColor(8);cout << "  " << y << endl << endl;setColor(7);}else{cout << endl << endl;}
        }
        if(debugger1 == 1){
            for(int x = 1; x <= maxSpace[lvl]; x++){
                if(x < 10){setColor(8);cout << "  " << x << " ";setColor(7);}
                else{setColor(8);cout << "  " << x;setColor(7);}
            }
            cout << endl;
        }
        break;
    }
}
void bot_brain(short lvl){
    short rate[4] = {0,10,25,40};
    map A;
    short rate_turn, fifty_rate, time_turn = 1;
    rate_turn = rand()%101;
    if(rate_turn < rate[lvl]){time_turn = 2;}
    //--------------------------------------------
    switch(lvl){
        case 1:
        for(int i = 1; i <= time_turn; i++){
            if(address_A[0] < address_ad[0]){//?upper
                if(address_A[1] < address_ad[1]){//front
                    if(A.easy[address_ad[0]-1][address_ad[1]] == 1 && A.easy[address_ad[0]][address_ad[1]-1] == 1){
                        fifty_rate = rand()%101;
                        if(fifty_rate >= 50){address_ad[0]++;}
                        else if(fifty_rate < 50){address_ad[1]++;}
                    }
                    else if(A.easy[address_ad[0]-1][address_ad[1]] == 1){address_ad[1]--;}
                    else if(A.easy[address_ad[0]][address_ad[1]-1] == 1){address_ad[0]--;}
                    else{
                        fifty_rate = rand()%101;
                        if(fifty_rate >= 50){address_ad[0]--;}
                        else if(fifty_rate < 50){address_ad[1]--;}
                    }
                }
                else if(address_A[1] > address_ad[1]){//back
                    if(A.easy[address_ad[0]-1][address_ad[1]] == 1 && A.easy[address_ad[0]][address_ad[1]+1] == 1){
                        fifty_rate = rand()%101;
                        if(fifty_rate >= 50){address_ad[0]++;}
                        else if(fifty_rate < 50){address_ad[1]--;}
                    }
                    else if(A.easy[address_ad[0]-1][address_ad[1]] == 1){address_ad[1]++;}
                    else if(A.easy[address_ad[0]][address_ad[1]+1] == 1){address_ad[0]--;}
                    else{
                        fifty_rate = rand()%101;
                        if(fifty_rate >= 50){address_ad[0]--;}
                        else if(fifty_rate < 50){address_ad[1]++;}
                    }
                }
                else if(address_A[1] == address_ad[1]){//in line
                    if(A.easy[address_ad[0]][address_ad[1]-1] == 1 && A.easy[address_ad[0]-1][address_ad[1]] == 1 && A.easy[address_ad[0]][address_ad[1]+1] == 1){address_ad[0]++;}
                    else if(A.easy[address_ad[0]-1][address_ad[1]] == 1 && A.easy[address_ad[0]][address_ad[1]+1] == 1){address_ad[1]--;}
                    else if(A.easy[address_ad[0]-1][address_ad[1]] == 1 && A.easy[address_ad[0]][address_ad[1]-1] == 1){address_ad[1]++;}
                    else if(A.easy[address_ad[0]-1][address_ad[1]] == 1){
                        fifty_rate = rand()%101;
                        if(fifty_rate >= 50){address_ad[1]--;}
                        else if(fifty_rate < 50){address_ad[1]++;}
                    }
                    else{address_ad[0]--;}
                }
            }
            else if(address_A[0] > address_ad[0]){//?lower
                if(address_A[1] < address_ad[1]){//front
                    if(A.easy[address_ad[0]][address_ad[1]-1] == 1 && A.easy[address_ad[0]+1][address_ad[1]] == 1){
                        fifty_rate = rand()%101;
                        if(fifty_rate >= 50){address_ad[0]--;}
                        else if(fifty_rate < 50){address_ad[1]++;}
                    }
                    else if(A.easy[address_ad[0]][address_ad[1]-1] == 1){address_ad[0]++;}
                    else if(A.easy[address_ad[0]+1][address_ad[1]] == 1){address_ad[1]--;}
                    else{
                        fifty_rate = rand()%101;
                        if(fifty_rate >= 50){address_ad[0]++;}
                        else if(fifty_rate < 50){address_ad[1]--;}
                    }
                }
                else if(address_A[1] > address_ad[1]){//back
                    if(A.easy[address_ad[0]][address_ad[1]+1] == 1 && A.easy[address_ad[0]+1][address_ad[1]] == 1){
                        fifty_rate = rand()%101;
                        if(fifty_rate >= 50){address_ad[0]--;}
                        else if(fifty_rate < 50){address_ad[1]--;}
                    }
                    else if(A.easy[address_ad[0]+1][address_ad[1]] == 1){address_ad[1]++;}
                    else if(A.easy[address_ad[0]][address_ad[1]+1] == 1){address_ad[0]++;}
                    else{
                        fifty_rate = rand()%101;
                        if(fifty_rate >= 50){address_ad[0]++;}
                        else if(fifty_rate < 50){address_ad[1]++;}
                    }
                }
                else if(address_A[1] == address_ad[1]){//in line
                    if(A.easy[address_ad[0]][address_ad[1]+1] == 1 && A.easy[address_ad[0]+1][address_ad[1]] == 1 && A.easy[address_ad[0]][address_ad[1]-1] == 1){address_ad[0]--;}
                    else if(A.easy[address_ad[0]+1][address_ad[1]] == 1 && A.easy[address_ad[0]][address_ad[1]+1] == 1){address_ad[1]--;}
                    else if(A.easy[address_ad[0]+1][address_ad[1]] == 1 && A.easy[address_ad[0]][address_ad[1]-1] == 1){address_ad[1]++;}
                    else if(A.easy[address_ad[0]+1][address_ad[1]] == 1){
                        fifty_rate = rand()%101;
                        if(fifty_rate >= 50){address_ad[1]--;}
                        else if(fifty_rate < 50){address_ad[1]++;}
                    }
                    else{address_ad[0]++;}
                }
            }
            else if(address_A[0] == address_ad[0]){//?in line
                if(address_A[1] < address_ad[1]){//front
                    if(A.easy[address_ad[0]+1][address_ad[1]] == 1 && A.easy[address_ad[0]][address_ad[1]-1] == 1 && A.easy[address_ad[0]-1][address_ad[1]] == 1){address_ad[1]++;}
                    else if(A.easy[address_ad[0]][address_ad[1]-1] == 1 && A.easy[address_ad[0]+1][address_ad[1]] == 1){address_ad[0]--;}
                    else if(A.easy[address_ad[0]][address_ad[1]-1] == 1 && A.easy[address_ad[0]-1][address_ad[1]] == 1){address_ad[0]++;}
                    else if(A.easy[address_ad[0]][address_ad[1]-1] == 1){
                        fifty_rate = rand()%101;
                        if(fifty_rate >= 50){address_ad[0]++;}
                        else if(fifty_rate < 50){address_ad[0]--;}
                    }
                    else{address_ad[1]--;}
                }
                else if(address_A[1] > address_ad[1]){//back
                    if(A.easy[address_ad[0]+1][address_ad[1]] == 1 && A.easy[address_ad[0]][address_ad[1]+1] == 1 && A.easy[address_ad[0]-1][address_ad[1]] == 1){address_ad[1]--;}
                    else if(A.easy[address_ad[0]][address_ad[1]+1] == 1 && A.easy[address_ad[0]-1][address_ad[1]] == 1){address_ad[0]++;}
                    else if(A.easy[address_ad[0]][address_ad[1]+1] == 1 && A.easy[address_ad[0]+1][address_ad[1]] == 1){address_ad[0]--;}
                    else if(A.easy[address_ad[0]][address_ad[1]+1] == 1){
                        fifty_rate = rand()%101;
                        if(fifty_rate >= 50){address_ad[0]++;}
                        else if(fifty_rate < 50){address_ad[0]--;}
                    }
                    else{address_ad[1]++;}
                }
            }
        }
        break;
        //!----------------------------------------------------------------------
        case 2:
        for(int i = 1; i <= time_turn; i++){
            if(address_A[0] < address_ad[0]){//?upper
                if(address_A[1] < address_ad[1]){//front
                    if(A.medium[address_ad[0]-1][address_ad[1]] == 1 && A.medium[address_ad[0]][address_ad[1]-1] == 1){
                        fifty_rate = rand()%101;
                        if(fifty_rate >= 50){address_ad[0]++;}
                        else if(fifty_rate < 50){address_ad[1]++;}
                    }
                    else if(A.medium[address_ad[0]-1][address_ad[1]] == 1){address_ad[1]--;}
                    else if(A.medium[address_ad[0]][address_ad[1]-1] == 1){address_ad[0]--;}
                    else{
                        fifty_rate = rand()%101;
                        if(fifty_rate >= 50){address_ad[0]--;}
                        else if(fifty_rate < 50){address_ad[1]--;}
                    }
                }
                else if(address_A[1] > address_ad[1]){//back
                    if(A.medium[address_ad[0]-1][address_ad[1]] == 1 && A.medium[address_ad[0]][address_ad[1]+1] == 1){
                        fifty_rate = rand()%101;
                        if(fifty_rate >= 50){address_ad[0]++;}
                        else if(fifty_rate < 50){address_ad[1]--;}
                    }
                    else if(A.medium[address_ad[0]-1][address_ad[1]] == 1){address_ad[1]++;}
                    else if(A.medium[address_ad[0]][address_ad[1]+1] == 1){address_ad[0]--;}
                    else{
                        fifty_rate = rand()%101;
                        if(fifty_rate >= 50){address_ad[0]--;}
                        else if(fifty_rate < 50){address_ad[1]++;}
                    }
                }
                else if(address_A[1] == address_ad[1]){//in line
                    if(A.medium[address_ad[0]][address_ad[1]-1] == 1 && A.medium[address_ad[0]-1][address_ad[1]] == 1 && A.medium[address_ad[0]][address_ad[1]+1] == 1){address_ad[0]++;}
                    else if(A.medium[address_ad[0]-1][address_ad[1]] == 1 && A.medium[address_ad[0]][address_ad[1]+1] == 1){address_ad[1]--;}
                    else if(A.medium[address_ad[0]-1][address_ad[1]] == 1 && A.medium[address_ad[0]][address_ad[1]-1] == 1){address_ad[1]++;}
                    else if(A.medium[address_ad[0]-1][address_ad[1]] == 1){
                        fifty_rate = rand()%101;
                        if(fifty_rate >= 50){address_ad[1]--;}
                        else if(fifty_rate < 50){address_ad[1]++;}
                    }
                    else{address_ad[0]--;}
                }
            }
            else if(address_A[0] > address_ad[0]){//?lower
                if(address_A[1] < address_ad[1]){//front
                    if(A.medium[address_ad[0]][address_ad[1]-1] == 1 && A.medium[address_ad[0]+1][address_ad[1]] == 1){
                        fifty_rate = rand()%101;
                        if(fifty_rate >= 50){address_ad[0]--;}
                        else if(fifty_rate < 50){address_ad[1]++;}
                    }
                    else if(A.medium[address_ad[0]][address_ad[1]-1] == 1){address_ad[0]++;}
                    else if(A.medium[address_ad[0]+1][address_ad[1]] == 1){address_ad[1]--;}
                    else{
                        fifty_rate = rand()%101;
                        if(fifty_rate >= 50){address_ad[0]++;}
                        else if(fifty_rate < 50){address_ad[1]--;}
                    }
                }
                else if(address_A[1] > address_ad[1]){//back
                    if(A.medium[address_ad[0]][address_ad[1]+1] == 1 && A.medium[address_ad[0]+1][address_ad[1]] == 1){
                        fifty_rate = rand()%101;
                        if(fifty_rate >= 50){address_ad[0]--;}
                        else if(fifty_rate < 50){address_ad[1]--;}
                    }
                    else if(A.medium[address_ad[0]+1][address_ad[1]] == 1){address_ad[1]++;}
                    else if(A.medium[address_ad[0]][address_ad[1]+1] == 1){address_ad[0]++;}
                    else{
                        fifty_rate = rand()%101;
                        if(fifty_rate >= 50){address_ad[0]++;}
                        else if(fifty_rate < 50){address_ad[1]++;}
                    }
                }
                else if(address_A[1] == address_ad[1]){//in line
                    if(A.medium[address_ad[0]][address_ad[1]+1] == 1 && A.medium[address_ad[0]+1][address_ad[1]] == 1 && A.medium[address_ad[0]][address_ad[1]-1] == 1){address_ad[0]--;}
                    else if(A.medium[address_ad[0]+1][address_ad[1]] == 1 && A.medium[address_ad[0]][address_ad[1]+1] == 1){address_ad[1]--;}
                    else if(A.medium[address_ad[0]+1][address_ad[1]] == 1 && A.medium[address_ad[0]][address_ad[1]-1] == 1){address_ad[1]++;}
                    else if(A.medium[address_ad[0]+1][address_ad[1]] == 1){
                        fifty_rate = rand()%101;
                        if(fifty_rate >= 50){address_ad[1]--;}
                        else if(fifty_rate < 50){address_ad[1]++;}
                    }
                    else{address_ad[0]++;}
                }
            }
            else if(address_A[0] == address_ad[0]){//?in line
                if(address_A[1] < address_ad[1]){//front
                    if(A.medium[address_ad[0]+1][address_ad[1]] == 1 && A.medium[address_ad[0]][address_ad[1]-1] == 1 && A.medium[address_ad[0]-1][address_ad[1]] == 1){address_ad[1]++;}
                    else if(A.medium[address_ad[0]][address_ad[1]-1] == 1 && A.medium[address_ad[0]+1][address_ad[1]] == 1){address_ad[0]--;}
                    else if(A.medium[address_ad[0]][address_ad[1]-1] == 1 && A.medium[address_ad[0]-1][address_ad[1]] == 1){address_ad[0]++;}
                    else if(A.medium[address_ad[0]][address_ad[1]-1] == 1){
                        fifty_rate = rand()%101;
                        if(fifty_rate >= 50){address_ad[0]++;}
                        else if(fifty_rate < 50){address_ad[0]--;}
                    }
                    else{address_ad[1]--;}
                }
                else if(address_A[1] > address_ad[1]){//back
                    if(A.medium[address_ad[0]+1][address_ad[1]] == 1 && A.medium[address_ad[0]][address_ad[1]+1] == 1 && A.medium[address_ad[0]-1][address_ad[1]] == 1){address_ad[1]--;}
                    else if(A.medium[address_ad[0]][address_ad[1]+1] == 1 && A.medium[address_ad[0]-1][address_ad[1]] == 1){address_ad[0]++;}
                    else if(A.medium[address_ad[0]][address_ad[1]+1] == 1 && A.medium[address_ad[0]+1][address_ad[1]] == 1){address_ad[0]--;}
                    else if(A.medium[address_ad[0]][address_ad[1]+1] == 1){
                        fifty_rate = rand()%101;
                        if(fifty_rate >= 50){address_ad[0]++;}
                        else if(fifty_rate < 50){address_ad[0]--;}
                    }
                    else{address_ad[1]++;}
                }
            }
        }
        break;
        //!----------------------------------------------------------------------
        case 3:
        for(int i = 1; i <= time_turn; i++){
            if(address_A[0] < address_ad[0]){//?upper
                if(address_A[1] < address_ad[1]){//front
                    if(A.hard[address_ad[0]-1][address_ad[1]] == 1 && A.hard[address_ad[0]][address_ad[1]-1] == 1){
                        fifty_rate = rand()%101;
                        if(fifty_rate >= 50){address_ad[0]++;}
                        else if(fifty_rate < 50){address_ad[1]++;}
                    }
                    else if(A.hard[address_ad[0]-1][address_ad[1]] == 1){address_ad[1]--;}
                    else if(A.hard[address_ad[0]][address_ad[1]-1] == 1){address_ad[0]--;}
                    else{
                        fifty_rate = rand()%101;
                        if(fifty_rate >= 50){address_ad[0]--;}
                        else if(fifty_rate < 50){address_ad[1]--;}
                    }
                }
                else if(address_A[1] > address_ad[1]){//back
                    if(A.hard[address_ad[0]-1][address_ad[1]] == 1 && A.hard[address_ad[0]][address_ad[1]+1] == 1){
                        fifty_rate = rand()%101;
                        if(fifty_rate >= 50){address_ad[0]++;}
                        else if(fifty_rate < 50){address_ad[1]--;}
                    }
                    else if(A.hard[address_ad[0]-1][address_ad[1]] == 1){address_ad[1]++;}
                    else if(A.hard[address_ad[0]][address_ad[1]+1] == 1){address_ad[0]--;}
                    else{
                        fifty_rate = rand()%101;
                        if(fifty_rate >= 50){address_ad[0]--;}
                        else if(fifty_rate < 50){address_ad[1]++;}
                    }
                }
                else if(address_A[1] == address_ad[1]){//in line
                    if(A.hard[address_ad[0]][address_ad[1]-1] == 1 && A.hard[address_ad[0]-1][address_ad[1]] == 1 && A.hard[address_ad[0]][address_ad[1]+1] == 1){address_ad[0]++;}
                    else if(A.hard[address_ad[0]-1][address_ad[1]] == 1 && A.hard[address_ad[0]][address_ad[1]+1] == 1){address_ad[1]--;}
                    else if(A.hard[address_ad[0]-1][address_ad[1]] == 1 && A.hard[address_ad[0]][address_ad[1]-1] == 1){address_ad[1]++;}
                    else if(A.hard[address_ad[0]-1][address_ad[1]] == 1){
                        fifty_rate = rand()%101;
                        if(fifty_rate >= 50){address_ad[1]--;}
                        else if(fifty_rate < 50){address_ad[1]++;}
                    }
                    else{address_ad[0]--;}
                }
            }
            else if(address_A[0] > address_ad[0]){//?lower
                if(address_A[1] < address_ad[1]){//front
                    if(A.hard[address_ad[0]][address_ad[1]-1] == 1 && A.hard[address_ad[0]+1][address_ad[1]] == 1){
                        fifty_rate = rand()%101;
                        if(fifty_rate >= 50){address_ad[0]--;}
                        else if(fifty_rate < 50){address_ad[1]++;}
                    }
                    else if(A.hard[address_ad[0]][address_ad[1]-1] == 1){address_ad[0]++;}
                    else if(A.hard[address_ad[0]+1][address_ad[1]] == 1){address_ad[1]--;}
                    else{
                        fifty_rate = rand()%101;
                        if(fifty_rate >= 50){address_ad[0]++;}
                        else if(fifty_rate < 50){address_ad[1]--;}
                    }
                }
                else if(address_A[1] > address_ad[1]){//back
                    if(A.hard[address_ad[0]][address_ad[1]+1] == 1 && A.hard[address_ad[0]+1][address_ad[1]] == 1){
                        fifty_rate = rand()%101;
                        if(fifty_rate >= 50){address_ad[0]--;}
                        else if(fifty_rate < 50){address_ad[1]--;}
                    }
                    else if(A.hard[address_ad[0]+1][address_ad[1]] == 1){address_ad[1]++;}
                    else if(A.hard[address_ad[0]][address_ad[1]+1] == 1){address_ad[0]++;}
                    else{
                        fifty_rate = rand()%101;
                        if(fifty_rate >= 50){address_ad[0]++;}
                        else if(fifty_rate < 50){address_ad[1]++;}
                    }
                }
                else if(address_A[1] == address_ad[1]){//in line
                    if(A.easy[address_ad[0]][address_ad[1]+1] == 1 && A.hard[address_ad[0]+1][address_ad[1]] == 1 && A.hard[address_ad[0]][address_ad[1]-1] == 1){address_ad[0]--;}
                    else if(A.hard[address_ad[0]+1][address_ad[1]] == 1 && A.hard[address_ad[0]][address_ad[1]+1] == 1){address_ad[1]--;}
                    else if(A.hard[address_ad[0]+1][address_ad[1]] == 1 && A.hard[address_ad[0]][address_ad[1]-1] == 1){address_ad[1]++;}
                    else if(A.hard[address_ad[0]+1][address_ad[1]] == 1){
                        fifty_rate = rand()%101;
                        if(fifty_rate >= 50){address_ad[1]--;}
                        else if(fifty_rate < 50){address_ad[1]++;}
                    }
                    else{address_ad[0]++;}
                }
            }
            else if(address_A[0] == address_ad[0]){//?in line
                if(address_A[1] < address_ad[1]){//front
                    if(A.hard[address_ad[0]+1][address_ad[1]] == 1 && A.hard[address_ad[0]][address_ad[1]-1] == 1 && A.hard[address_ad[0]-1][address_ad[1]] == 1){address_ad[1]++;}
                    else if(A.hard[address_ad[0]][address_ad[1]-1] == 1 && A.hard[address_ad[0]+1][address_ad[1]] == 1){address_ad[0]--;}
                    else if(A.hard[address_ad[0]][address_ad[1]-1] == 1 && A.hard[address_ad[0]-1][address_ad[1]] == 1){address_ad[0]++;}
                    else if(A.hard[address_ad[0]][address_ad[1]-1] == 1){
                        fifty_rate = rand()%101;
                        if(fifty_rate >= 50){address_ad[0]++;}
                        else if(fifty_rate < 50){address_ad[0]--;}
                    }
                    else{address_ad[1]--;}
                }
                else if(address_A[1] > address_ad[1]){//back
                    if(A.hard[address_ad[0]+1][address_ad[1]] == 1 && A.hard[address_ad[0]][address_ad[1]+1] == 1 && A.hard[address_ad[0]-1][address_ad[1]] == 1){address_ad[1]--;}
                    else if(A.hard[address_ad[0]][address_ad[1]+1] == 1 && A.hard[address_ad[0]-1][address_ad[1]] == 1){address_ad[0]++;}
                    else if(A.hard[address_ad[0]][address_ad[1]+1] == 1 && A.hard[address_ad[0]+1][address_ad[1]] == 1){address_ad[0]--;}
                    else if(A.hard[address_ad[0]][address_ad[1]+1] == 1){
                        fifty_rate = rand()%101;
                        if(fifty_rate >= 50){address_ad[0]++;}
                        else if(fifty_rate < 50){address_ad[0]--;}
                    }
                    else{address_ad[1]++;}
                }
            }
        }
        break;
    }
}

void main_logic(short lvl){
    system("cls");//!clear
    map A;
    //-------------------
    short fifty_rate;
    short maxSpace[4] = {0,7,12,17}; 
    //-------------------
    string choice1, choice2;
    short count, click_counting = 0, rate_turn = 0;
    bool checker;
    switch(lvl){
        case 1://?easy mode
        cout << "Generating..";
        reset_data1:
        count = 0;
        while(1){//random for A
            address_A[0] = rand()%maxSpace[lvl]+1;
            address_A[1] = rand()%maxSpace[lvl]+1;
            ++count;
            if(count >= 5){goto reset_data1;}
            if(A.easy[address_A[0]][address_A[1]] == 0){break;}
        }count = 0;
        while(1){//random for @
            address_ad[0] = rand()%maxSpace[lvl]+1;
            address_ad[1] = rand()%maxSpace[lvl]+1;
            ++count;
            if(count >= 5){goto reset_data1;}
            if(pow(address_ad[0] - address_A[0],2) == 1 || pow(address_ad[1] - address_A[1],2) == 1){continue;}
            else if(A.easy[address_ad[0]][address_ad[1]] == 0
                && address_ad[0] != address_A[0] && address_ad[1] != address_A[1]){break;}
        }count = 0;
        while(1){//random for the door
            address_end[0] = rand()%maxSpace[lvl]+1;
            address_end[1] = rand()%maxSpace[lvl]+1;
            ++count;
            if(count >= 5){goto reset_data1;}
            if(pow(address_end[0] - address_A[0],2) == 1 || pow(address_end[1] - address_A[1],2) == 1){continue;}
            else if(A.easy[address_end[0]][address_end[1]] == 0
               && address_end[0] != address_A[0] && address_end[1] != address_A[1]
               && address_end[0] != address_ad[0] && address_end[1] != address_ad[1]){break;}
        }count = 0;
        //!----------------------------------------------------------------------
        system("cls");//!clear
        UI_cover("upper");
        cout << endl << endl;
        while(1){
            error_usage1:
            render_map(lvl,0,0);
            cout << "W A S D to control [A]  |  press ESC to leave" << endl;
            UI_cover("lower");
            if(debugger1 == 1){setColor(8); cout << "\nAddress of A => [x] : " << address_A[1] << "[y] : " << address_A[0]
                                    << "\nAddress of @ => [x] : " << address_ad[1] << "[y] : " << address_ad[0]
                                    << "\nAddress of the door => [x] : " << address_end[1] << "[y] : " << address_end[0]; setColor(7);}
            char input; checker = 0;
            input = _getch();
            switch (input) {
                case 'w':
                case 'W':
                    system("cls");//!clear
                    if(A.easy[address_A[0]-1][address_A[1]] == 1){UI_cover("upper"); cout << "Unable to go up there!\n\n"; goto error_usage1;}
                    else{address_A[0] -= 1; click_counting++;}
                   break;
                case 'a':
                case 'A':
                    system("cls");//!clear
                    if(A.easy[address_A[0]][address_A[1]-1] == 1){UI_cover("upper"); cout << "Unable to go up there!\n\n"; goto error_usage1;}
                    else{address_A[1] -= 1; click_counting++;}
                    break;
                case 's':
                case 'S':
                    system("cls");//!clear
                    if(A.easy[address_A[0]+1][address_A[1]] == 1){UI_cover("upper"); cout << "Unable to go up there!\n\n"; goto error_usage1;}
                    else{address_A[0] += 1; click_counting++;}
                    break;
                case 'd':
                case 'D':
                    system("cls");//!clear
                    if(A.easy[address_A[0]][address_A[1]+1] == 1){UI_cover("upper"); cout << "Unable to go up there!\n\n"; goto error_usage1;}
                    else{address_A[1] += 1; click_counting++;}
                    break;
                case 27://escape
                    system("cls");//!clear
                    while(1){
                        cout << "Really want to leave? (y/n) : "; getline(cin,choice2);
                        if(choice2.compare("y") == 0 || choice2.compare("n") == 0){break;}
                        system("cls");//!clear
                    }
                    switch(choice2[0]){
                        case 'y': startMenu();
                        case 'n': system("cls"); UI_cover("upper"); cout << "Welcome back!\n"; goto error_usage1;
                    }
                default:
                    system("cls");//!clear
                    UI_cover("upper");
                    cout << "Unable key!\n";
                    goto error_usage1;
            }
            if(address_A[0] == address_ad[0] && address_A[1] == address_ad[1]){//!If ad hunt A
                you_dead1:
                system("cls");//!clear
                UI_cover("upper");
                cout << endl << endl;
                render_map(lvl,1,0);
                UI_cover("lower");
                FUNC_delay(500);
                loss_game();
            }
            if(address_A[0] == address_end[0] && address_A[1] == address_end[1]){
                UI_cover("upper");
                cout << endl << endl;
                render_map(lvl,0,0);
                UI_cover("lower");
                FUNC_delay(500);
                win_game(click_counting);
            }
            //*BOT part--------------------
            bot_brain(lvl);
            //*----------------------------
            if(address_A[0] == address_ad[0] && address_A[1] == address_ad[1]){goto you_dead1;}
            UI_cover("upper");
            cout << "\n\n";
        }
        break;
        //!----------------------------------------------------------------------
        case 2:
        cout << "Generating..";
        reset_data2:
        count = 0;
        while(1){//random for A
            address_A[0] = rand()%maxSpace[lvl]+1;
            address_A[1] = rand()%maxSpace[lvl]+1;
            ++count;
            if(count >= 5){goto reset_data2;}
            if(A.medium[address_A[0]][address_A[1]] == 0){break;}
        }count = 0;
        while(1){//random for @
            address_ad[0] = rand()%maxSpace[lvl]+1;
            address_ad[1] = rand()%maxSpace[lvl]+1;
            ++count;
            if(count >= 5){goto reset_data2;}
            if((pow(address_ad[0] - address_A[0],2) <= pow(4,2) || pow(address_ad[1] - address_A[1],2) <= pow(4,2)) 
            && (pow(address_ad[0] - address_A[0],2) != 0 || pow(address_ad[1] - address_A[1],2) != 0)){continue;}
            if(A.medium[address_ad[0]][address_ad[1]] == 0
                && address_ad[0] != address_A[0] && address_ad[1] != address_A[1]){break;}
        }count = 0;
        while(1){//random for the door
            address_end[0] = rand()%maxSpace[lvl]+1;
            address_end[1] = rand()%maxSpace[lvl]+1;
            ++count;
            if(count >= 5){goto reset_data2;}
            if((pow(address_A[0]-address_end[0],2) < pow(5,2) && pow(address_A[1]-address_end[1],2) < pow(5,2))
                || (pow(address_ad[0]-address_end[0],2) < pow(5,2) && pow(address_ad[1]-address_end[1],2) < pow(5,2))){continue;}
            if(pow(address_end[0] - address_A[0],2) == 1 || pow(address_end[1] - address_A[1],2) == 1){continue;}
            else if(A.medium[address_end[0]][address_end[1]] == 0
               && address_end[0] != address_A[0] && address_end[1] != address_A[1]
               && address_end[0] != address_ad[0] && address_end[1] != address_ad[1]){break;}
        }count = 0;
        //--------------------
        system("cls");//!clear
        UI_cover("upper");
        if(click_counting < 3){setColor(6);cout << "\nThe door will be appeared in " << 3-click_counting << " turns left\n";setColor(7);}
        else{cout << "\n\n";}
        while(1){
            error_usage2:
            render_map(lvl,0,click_counting);
            cout << "W A S D to control [A]  |  press ESC to leave" << endl;
            UI_cover("lower");
            if(debugger1 == 1){setColor(8); cout << "\nAddress of A => [x] : " << address_A[1] << "[y] : " << address_A[0]
                                    << "\nAddress of @ => [x] : " << address_ad[1] << "[y] : " << address_ad[0]
                                    << "\nAddress of the door => [x] : " << address_end[1] << "[y] : " << address_end[0]; setColor(7);}
            char input; checker = 0;
            input = _getch();
            switch (input) {
                case 'w':
                case 'W':
                    system("cls");//!clear
                    if(A.medium[address_A[0]-1][address_A[1]] == 1){UI_cover("upper"); cout << "Unable to go up there!\n\n"; goto error_usage2;}
                    else{address_A[0] -= 1; click_counting++;}
                   break;
                case 'a':
                case 'A':
                    system("cls");//!clear
                    if(A.medium[address_A[0]][address_A[1]-1] == 1){UI_cover("upper"); cout << "Unable to go up there!\n\n"; goto error_usage2;}
                    else{address_A[1] -= 1; click_counting++;}
                    break;
                case 's':
                case 'S':
                    system("cls");//!clear
                    if(A.medium[address_A[0]+1][address_A[1]] == 1){UI_cover("upper"); cout << "Unable to go up there!\n\n"; goto error_usage2;}
                    else{address_A[0] += 1; click_counting++;}
                    break;
                case 'd':
                case 'D':
                    system("cls");//!clear
                    if(A.medium[address_A[0]][address_A[1]+1] == 1){UI_cover("upper"); cout << "Unable to go up there!\n\n"; goto error_usage2;}
                    else{address_A[1] += 1; click_counting++;}
                    break;
                case 27://escape
                    system("cls");//!clear
                    while(1){
                        cout << "Really want to leave? (y/n) : "; getline(cin,choice2);
                        if(choice2.compare("y") == 0 || choice2.compare("n") == 0){break;}
                        system("cls");//!clear
                    }
                    switch(choice2[0]){
                        case 'y': startMenu();
                        case 'n': system("cls"); UI_cover("upper"); cout << "Welcome back!\n"; goto error_usage2;
                    }
                default:
                    system("cls");//!clear
                    UI_cover("upper");
                    cout << "Unable key!\n";
                    goto error_usage2;
            }
            if(address_A[0] == address_ad[0] && address_A[1] == address_ad[1]){//!If ad hunt A
                you_dead2:
                system("cls");//!clear
                UI_cover("upper");
                cout << endl << endl;
                render_map(lvl,1,click_counting);
                UI_cover("lower");
                FUNC_delay(500);
                loss_game();
            }
            if(address_A[0] == address_end[0] && address_A[1] == address_end[1]){
                UI_cover("upper");
                cout << endl << endl;
                render_map(lvl,0,click_counting);
                UI_cover("lower");
                FUNC_delay(500);
                win_game(click_counting);
            }
            //*BOT part--------------------
            bot_brain(lvl);
            //*----------------------------
            if(address_A[0] == address_ad[0] && address_A[1] == address_ad[1]){goto you_dead2;}
            UI_cover("upper");
            if(click_counting < 3){setColor(6);cout << "\nThe door will be appeared in " << 3-click_counting << " turns left\n";setColor(7);}
            else{cout << "\n\n";}
        }
        break;
        //!----------------------------------------------------------------------
        case 3:
        cout << "Generating..";
        reset_data3:
        count = 0;
        while(1){//random for A
            address_A[0] = rand()%maxSpace[lvl]+1;
            address_A[1] = rand()%maxSpace[lvl]+1;
            ++count;
            if(count >= 5){goto reset_data3;}
            if(A.hard[address_A[0]][address_A[1]] == 0){break;}
        }count = 0;
        while(1){//random for @
            address_ad[0] = rand()%maxSpace[lvl]+1;
            address_ad[1] = rand()%maxSpace[lvl]+1;
            ++count;
            if(count >= 5){goto reset_data3;}
            if((pow(address_ad[0] - address_A[0],2) <= pow(7,2) || pow(address_ad[1] - address_A[1],2) <= pow(7,2)) 
            && (pow(address_ad[0] - address_A[0],2) != 0 || pow(address_ad[1] - address_A[1],2) != 0)){continue;}
            else if(A.hard[address_ad[0]][address_ad[1]] == 0
                && address_ad[0] != address_A[0] && address_ad[1] != address_A[1]){break;}
        }count = 0;
        while(1){//random for the door
            address_end[0] = rand()%maxSpace[lvl]+1;
            address_end[1] = rand()%maxSpace[lvl]+1;
            ++count;
            if(count >= 5){goto reset_data3;}
            if((pow(address_A[0]-address_end[0],2) < pow(8,2) && pow(address_A[1]-address_end[1],2) < pow(8,2))
                || (pow(address_ad[0]-address_end[0],2) < pow(8,2) && pow(address_ad[1]-address_end[1],2) < pow(8,2))){continue;}
            if(pow(address_end[0] - address_A[0],2) == 1 || pow(address_end[1] - address_A[1],2) == 1){continue;}
            else if(A.hard[address_end[0]][address_end[1]] == 0
               && address_end[0] != address_A[0] && address_end[1] != address_A[1]
               && address_end[0] != address_ad[0] && address_end[1] != address_ad[1]){break;}
        }count = 0;
        //--------------------
        system("cls");//!clear
        UI_cover("upper");
        if(click_counting < 8){setColor(6);cout << "\nThe door will be appeared in " << 8-click_counting << " turns left\n";setColor(7);}
        else{cout << "\n\n";}
        while(1){
            error_usage3:
            render_map(lvl,0,click_counting);
            cout << "W A S D to control [A]  |  press ESC to leave" << endl;
            UI_cover("lower");
            if(debugger1 == 1){setColor(8); cout << "\nAddress of A => [x] : " << address_A[1] << "[y] : " << address_A[0]
                                    << "\nAddress of @ => [x] : " << address_ad[1] << "[y] : " << address_ad[0]
                                    << "\nAddress of the door => [x] : " << address_end[1] << "[y] : " << address_end[0]; setColor(7);}
            char input; checker = 0;
            input = _getch();
            switch (input) {
                case 'w':
                case 'W':
                    system("cls");//!clear
                    if(A.hard[address_A[0]-1][address_A[1]] == 1){UI_cover("upper"); cout << "Unable to go up there!\n\n"; goto error_usage3;}
                    else{address_A[0] -= 1; click_counting++;}
                   break;
                case 'a':
                case 'A':
                    system("cls");//!clear
                    if(A.hard[address_A[0]][address_A[1]-1] == 1){UI_cover("upper"); cout << "Unable to go up there!\n\n"; goto error_usage3;}
                    else{address_A[1] -= 1; click_counting++;}
                    break;
                case 's':
                case 'S':
                    system("cls");//!clear
                    if(A.hard[address_A[0]+1][address_A[1]] == 1){UI_cover("upper"); cout << "Unable to go up there!\n\n"; goto error_usage3;}
                    else{address_A[0] += 1; click_counting++;}
                    break;
                case 'd':
                case 'D':
                    system("cls");//!clear
                    if(A.hard[address_A[0]][address_A[1]+1] == 1){UI_cover("upper"); cout << "Unable to go up there!\n\n"; goto error_usage3;}
                    else{address_A[1] += 1; click_counting++;}
                    break;
                case 27://escape
                    system("cls");//!clear
                    while(1){
                        cout << "Really want to leave? (y/n) : "; getline(cin,choice2);
                        if(choice2.compare("y") == 0 || choice2.compare("n") == 0){break;}
                        system("cls");//!clear
                    }
                    switch(choice2[0]){
                        case 'y': startMenu();
                        case 'n': system("cls"); UI_cover("upper"); cout << "Welcome back!\n"; goto error_usage3;
                    }
                default:
                    system("cls");//!clear
                    UI_cover("upper");
                    cout << "Unable key!\n";
                    goto error_usage3;
            }
            if(address_A[0] == address_ad[0] && address_A[1] == address_ad[1]){//!If ad hunt A
                you_dead3:
                system("cls");//!clear
                UI_cover("upper");
                cout << endl << endl;
                render_map(lvl,1,click_counting);
                UI_cover("lower");
                FUNC_delay(500);
                loss_game();
            }
            if(address_A[0] == address_end[0] && address_A[1] == address_end[1]){
                UI_cover("upper");
                cout << endl << endl;
                render_map(lvl,0,click_counting);
                UI_cover("lower");
                FUNC_delay(500);
                win_game(click_counting);
            }
            //*BOT part--------------------
            bot_brain(lvl);
            //*----------------------------
            if(address_A[0] == address_ad[0] && address_A[1] == address_ad[1]){goto you_dead3;}
            UI_cover("upper");
            if(click_counting < 8){setColor(6);cout << "\nThe door will be appeared in " << 8-click_counting << " turns left\n";setColor(7);}
            else{cout << "\n\n";}
        }
        break;
    }
}

void win_game(short clicked){
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
    cout << "                                      " << endl;
    setColor(6); cout << "               YOU WON!               " << endl; setColor(7);
    cout << "                                      " << endl;
    cout << "                                      " << endl;
    if(clicked <= 9){cout << "  You moved " << clicked << " times to win this game  " << endl;}
    else{cout << "  You moved " << clicked << " times to win this game " << endl;}
    cout << "                                      " << endl;
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
    //---------------------
    string choice1;
    while(1){
        system("cls");//!clear
        cout << "Want to play again? (y/n) : "; getline(cin,choice1);
        if(choice1.compare("y") == 0 || choice1.compare("n") == 0){break;}
    }
    switch(choice1[0]){
        case 'y':choosingMode();
        break;
        case 'n':startMenu();
        break;
    }
    startMenu();
}

void loss_game(){
    system("color 07");
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
    cout << "                                      " << endl;
    setColor(4); cout << "              YOU LOSSED!               " << endl; setColor(7);
    cout << "                                      " << endl;
    cout << "                                      " << endl;
    cout << "         You may try it again         " << endl;
    cout << "                                      " << endl;
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
    //-----------------------------
    string choice1;
    if(not_first_time_played == 0){
        not_first_time_played = 1;
        map A;
        while(1){
            system("cls");//!clear
            cout << "You may have to watch out for gameplay guider. \nWant to see it now? (y/n) : "; getline(cin,choice1);
            if(choice1.compare("y") == 0 || choice1.compare("n") == 0){break;}
        }
        switch(choice1[0]){
            case 'y':A.guider();
            break;
            case 'n':break;
        }
    }
    while(1){
        system("cls");//!clear
        cout << "Want to play again? (y/n) : "; getline(cin,choice1);
        if(choice1.compare("y") == 0 || choice1.compare("n") == 0){break;}
    }
    switch(choice1[0]){
        case 'y':choosingMode();
        break;
        case 'n':startMenu();
        break;
    }
    startMenu();
}