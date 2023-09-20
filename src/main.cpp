#include <stdio.h>
#include <curl/curl.h>
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>


std::string readBuffer, searchquery;
int cols, lines;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp){
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
//void libcurl(const char * domain) {
//    CURL * curl;
//    CURLcode res;
//    
//    curl = curl_easy_init();
//    
//    curl_easy_setopt(curl, CURLOPT_URL, domain);
//    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
//    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
//    res = curl_easy_perform(curl);
//    curl_easy_cleanup(curl);
//}

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

void parse() {;}

int main() {
    int spaces = cols/3;
    std::string bottombar;
    gwgh();
    for (int a=0; a<lines-3; a++) {
        std::cout<<"\n";
    }
    for (int b; b<2; b++) {
        for (int c; c<spaces; c++) {
            bottombar += " ";
        }
    }
    std::cout << "\033[1;42m [E] Exit   |   [S]Search: ";
    std::cin >> searchquery;
    std::cout<<"\033[0m";
    //libcurl("https://google.com");
    //std::cout << readBuffer;
    //std::cout << "\n \033[1;42mbold red text\033[0m\n";
    return 0;
}