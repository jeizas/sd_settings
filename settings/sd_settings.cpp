//
//  sd_settings.cpp
//  hello-world
//
//  Created by jeizas on 2016/12/6.
//  Copyright © 2016年 jeizas. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sys/uio.h>
#include <sys/stat.h>

using namespace std;

int copyFile(char *filename, char *newfile);
int addContentToFile(string filename, string str);

int main() {
    string confDir = "../SD_WLAN/CONFIG";
    char imgDefultDir[] = "./FA000001.JPG";
    char imgSdDir[] = "../DCIM/100__TSB/FA000001.JPG.jpg";
    string copyState = (copyFile(imgDefultDir, imgSdDir) == 1) ? "success" : "failure";
    cout << "copy .... " << copyState << endl;
    
    string wifiMsg = "\nAPPSSID=alltuu14181\nAPPNETWORKKEY=12345678\n";
    string addState = addContentToFile(confDir, wifiMsg) == 1 ? "success" : "failure";
    cout << "add wifi massage .... " << addState << endl;
    return 0;
}

//copy file
int copyFile(char *filename, char *newfile) {
    ifstream in ;
    ofstream out;
    
    in.open(filename);
    if(in.fail()) {
        cout << "origin file open fail!" << endl;
        in.close();
        out.close();
        return 0;
    }
    chmod(newfile, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
    out.open(newfile);
    out << in.rdbuf();
    out.close();
    in.close();
        
    return 1;
}

//add string to file
int addContentToFile(string filename, string str) {
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
