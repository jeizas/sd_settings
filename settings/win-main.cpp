#include <iostream>
#include <fstream>
#include <io.h>
#include <string>
#include <sys/types.h>   
#include <sys/stat.h>
#include <stdlib.h>
#include <windows.h>
#include <sstream>
#include <ctime>

using namespace std;

int copyFile(char *filename, char *newfile);
int addContentToFile(char *filename, string str);

int main() {
    char confDir[] = "../SD_WLAN/CONFIG";
    char imgDefultDir[] = "FA000001.JPG";
    char imgSdDir[] = "../DCIM/100__TSB/FA000001.JPG";
    string copyState = (copyFile(imgDefultDir, imgSdDir) == 1) ? "success" : "failure";
    cout << "copy default image .... " << copyState << endl;
    
	srand(time(0));
	int num = 0;
	num = (rand() % 90000) + 100000;
	string str;
	stringstream strStream;
	strStream << num;
	str = strStream.str();
    string wifiMsg = "APPSSID=alltuu" + str + "\nAPPNETWORKKEY=12345678";
    string addState = addContentToFile(confDir, wifiMsg) == 1 ? "success" : "failure";
    cout << "add wifi massage :\n"<< wifiMsg << " .... " << addState << endl;
	system("pause");
	
	return 0;
}

//copy file
int copyFile(char *filename, char *newfile) {
    ifstream in ;
    ofstream out;
    
    in.open(filename, ios::binary);
    if(in.fail()) {
        cout << "origin file open fail!" << endl;
        in.close();
        out.close();
        return 0;
    }
    //chmod(newfile, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
	SetFileAttributes(newfile, FILE_ATTRIBUTE_NORMAL);
	out.open(newfile, ios::binary);
    out << in.rdbuf() << endl;
    out.close();
    in.close();
        
    return 1;
}

//add string to file
int addContentToFile(char *filename, string str) {
    ofstream out;
    out.open(filename, ios::app);
    if(out.fail()){
        cout << "config file open fail!" << endl;
        out.close();
        return 0;
    }
    out << str << endl;
    return 1;
}