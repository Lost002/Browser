#include <stdio.h>
#include <curl/curl.h>
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>


std::string readBuffer;
const char * searchquery;
std::string bottombar = "\033[42;37m [E] Exit   |   [D] Down    |   [U] Up  |   [1,2,3,ect...] Select   |   \033[1mSearch:\033[0m ";
int cols, lines;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp){
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void libcurl(const char * domain) {
    CURL * curl;
    CURLcode res;
    
    curl = curl_easy_init();
    
    curl_easy_setopt(curl, CURLOPT_URL, domain);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
}

void gwgh() {
    #ifdef TIOCGSIZE
        struct ttysize ts;
        ioctl(STDIN_FILENO, TIOCGSIZE, &ts);
        cols = ts.ts_cols;
        lines = ts.ts_lines;
    #elif defined(TIOCGWINSZ)
        struct winsize ts;
        ioctl(STDIN_FILENO, TIOCGWINSZ, &ts);
        cols = ts.ws_col;
        lines = ts.ws_row;
    #endif
}

void init_screen() {
    if (cols>=80 && lines>=15) {
        std::cout<<"\033[1;42m ";
        for (int a=0; a<cols-1; a++) {
            std::cout << " ";
        } for (int b=0; b<lines-2; b++) {
            std::cout<<"\033[0m\n";
        } std::cout<<"\033[46m"; for (int c=0; c<cols-1; c++) {
            std::cout<< " ";
        }
        std::cout<<"\033[0m\n";
        std::cout << "\033[42;37m [E] Exit   |   \033[1mSearch:\033[0m ";
    } else {
        std::cout << "\033[1;31mTerminal is too small to display, please resize!\nTerminating...\033[0m\n ";
        abort();        
    }
}
void searchscreen() {
    std::string lines;
    int numberoflines = 0;
    //while (getline(readBuffer, lines)) {
    //    numberoflines++;
    //    std::cout<<"\033[1;42m ";
    //    for (int a=0; a<cols-1; a++) {
    //        std::cout << " ";
    //    }
        std::cout << "\033[0m\n";
        std::cout<<lines<<"\n";
        std::cout<<bottombar;
    }
//}

void write(std::string data) {
    std::ofstream datafile();
}

int main() {
    bool searched = false;
    std::string choice;
    gwgh();
    while (true) {
        init_screen();
        std::cin >> choice;
        searchquery = choice.c_str();
        //if (searched==false) {
        //    init_screen();
        //    std::cin >> choice;
        //    searched=true;
        //    searchquery = choice.c_str();
        //} else {
        //    searchscreen();
        //    std::cin >> choice;
        //}
        std::system("clear");
        libcurl(searchquery);

        //std::cout << readBuffer;
    }
    return 0;
}