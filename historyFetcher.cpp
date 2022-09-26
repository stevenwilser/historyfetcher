#include <iostream>
#include <fstream>
#include <cstdlib>
#include <bits/stdc++.h>
#include <time.h>

using namespace std;
bool isKeywordInLine(string line, string keyword);
void getKeywordHistoryAllData(char **argv);
string getTitle(string line, string browserFlag);
string getUrl(string line);
string getVisitCount(string line, string browserFlag);
string getFrecency(string line);
string getBulk(string line, int x);
string getLastVisitDate(string line, string browserFlag);
string convertTime(string unixEpochTime, string browserFlag);
string convertYear(int epochYear);
string convertMonth(int epochMonth);
string convertWeekday (int epochWday);

int main(int argc, char *argv[]) {
   
    if (argc != 12) {
        cout<<"usage: " << argv[0] << " <keyword> <input filename> <output filename> [<csv> <header> <url> <title> <visit count> <frecency> <last visit date> <browser>] => binary values" << endl;
        cout<<"example: " << argv[0] << " youtube history.txt output.txt 0 1 1 1 1 1 1 1" << endl;
        cout<<"Put 0 for keyword if not desired" << endl;

        exit(0);
    }

    ifstream inputFileStream;
    ofstream outputFileStream;
    string keywordHistory = "keywordHistory.txt";
    string inputFile, outputFile;
    string line, keyword, url, title, visitCount, frecency, lastVisitEpochDate, lastVisitDate, browserFlag;
    string csvFlag, urlFlag, titleFlag, visitCountFlag, frecencyFlag, lastVisitDateFlag, headerOnFlag;
    string outputLine;
    string delim;

    keyword = argv[1];      
    inputFile = argv[2];
    outputFile = argv[3];
    csvFlag = argv[4];
    headerOnFlag = argv[5];
    urlFlag = argv[6];
    titleFlag = argv[7];
    visitCountFlag = argv[8];
    frecencyFlag = argv[9];
    lastVisitDateFlag = argv[10];
    browserFlag = argv[11];

    if (csvFlag == "1") {
        delim = ",";
    } else { 
        delim = "|";
    }

    if (keyword != "0") {
        getKeywordHistoryAllData(argv);
        inputFileStream.open(keywordHistory);
        outputFileStream.open(outputFile.c_str());
    }

    if (keyword == "0") {
        inputFileStream.open(inputFile.c_str());
        outputFileStream.open(outputFile.c_str());
    }
    if (headerOnFlag == "1") {
        outputLine = "";
        if (urlFlag == "1") {
            outputLine = outputLine + "url" + delim;
        }
        if (titleFlag == "1") {
            outputLine = outputLine + "title" + delim;
        }
        if (visitCountFlag == "1") {
            outputLine = outputLine + "visit_count" + delim;
        }
        if (browserFlag == "0") {
            if (frecencyFlag == "1") {
                outputLine = outputLine + "frecency" + delim;
            }
        }
        if (lastVisitDateFlag == "1") {
            outputLine = outputLine + "last_visit_date" + delim; 
        }

        outputFileStream << outputLine << endl;
    }

    while (getline(inputFileStream, line)) {
        outputLine = "";
 
        if (urlFlag == "1") {
            url = getUrl(line);
            outputLine = outputLine + url + delim;        
        }

        if (titleFlag == "1") {
            title = getTitle(line, browserFlag);
            outputLine = outputLine + title + delim;
        }

        if (visitCountFlag == "1") {
            visitCount = getVisitCount(line, browserFlag);
            outputLine = outputLine + visitCount + delim;
        }

        if (browserFlag == "0") {
            if (frecencyFlag == "1") {
                frecency = getFrecency(line);
                outputLine = outputLine + frecency + delim;
            }
        }

        if (lastVisitDateFlag == "1") {
            lastVisitEpochDate = getLastVisitDate(line, browserFlag);
            lastVisitDate = convertTime(lastVisitEpochDate, browserFlag);
            outputLine = outputLine + lastVisitDate + delim;
        }

        outputFileStream << outputLine << endl;
    }

    outputFileStream.close();

    return 0;
}
string convertWeekday (int epochWday) {
    string strWday;

    switch(epochWday) {
        case 0: strWday ="Sunday";
            break;
        case 1: strWday ="Monday";
            break;
        case 2: strWday ="Tuesday";
            break;
        case 3: strWday ="Wednesday";
            break;
        case 4: strWday ="Thursday";
            break;
        case 5: strWday ="Friday";
            break;
        case 6: strWday ="Saturday";
            break;
    }

    return strWday; 
         
}

string convertMonth(int epochMonth) {

    int month = epochMonth + 1;
    if (month < 10) {
        string strMonth = to_string(month);
        strMonth = "0" + strMonth;
        return strMonth;
    }
    else {
        string strMonth = to_string(month);
        return strMonth;
    }
}

string convertYear(int epochYear) {

    int readableYear = epochYear + 1900;
    return to_string(readableYear);

}

string convertTime(string unixEpochTime, string browserFlag) {

    struct tm* timeInfo;
    string time = unixEpochTime;
    long timeInt = atol(time.c_str());
    timeInt = timeInt/1000000;
    if (browserFlag == "1") {
        timeInt = timeInt - 11644473600;
    }
    time_t timeT = (time_t)timeInt;
    timeInfo = gmtime(&timeT);
    string year = convertYear(timeInfo->tm_year);
    string month = convertMonth(timeInfo->tm_mon);
    string day = to_string(timeInfo->tm_mday);
    if (timeInfo->tm_mday < 10) {
        day = "0" + day;
    }
    string hour = to_string(timeInfo->tm_hour);
    if (timeInfo->tm_hour < 10) {
        hour = "0" + hour;
    }
    string min = to_string(timeInfo->tm_min);
    if (timeInfo->tm_min < 10) {
        min = "0" + min;
    }
    string sec = to_string(timeInfo->tm_sec);
    if (timeInfo->tm_sec < 10) {
        sec = "0" + sec;
    }
    string wday = convertWeekday(timeInfo->tm_wday);
    string convertedTime = year +"-"+ month +"-"+day +" "+ hour +":"+ min +":"+sec +" "+"GMT"+" "+ wday;

    return convertedTime;
} 

string getLastVisitDate(string line, string browserFlag) {

    if (browserFlag == "0") {
        return getBulk(line, 7);
    }
    else {
        return getBulk(line, 1);
    }
}

string getFrecency(string line) {
    return getBulk(line, 8);
}

string getVisitCount(string line, string browserFlag) {
    if (browserFlag == "0") {
        return getBulk(line, 10);
    }
    else {
        return getBulk(line, 3);
    }
}

string getBulk(string line, int x) {

    string charDelim = "|";
    size_t firstDelim;

    size_t lastDelim = line.rfind(charDelim);

    for (int i=0; i<x; i++) {
        firstDelim = line.rfind(charDelim, lastDelim-1);
        lastDelim = firstDelim;
    }
    size_t otherDelim = line.find_first_of(charDelim, lastDelim+1);
    int length = otherDelim - firstDelim;
    string target = line.substr(firstDelim+1, length-1);
    return target;
}

string getTitle(string line, string browserFlag) {
    int a;
    if (browserFlag == "0") {
        a = 12;
    }
    else {
        a = 3;
    }

    string title;
    string charDelim = "|";
    size_t otherDelim;

    size_t firstDelim = line.find_first_of(charDelim);
    size_t secondDelim = line.find_first_of(charDelim, firstDelim+1);
    size_t lastDelim = line.rfind(charDelim);

    for (int i=0; i<a; i++) {
        otherDelim = line.rfind(charDelim, lastDelim-1);    
        lastDelim = otherDelim;
    }

        int length = lastDelim - secondDelim;
        title = line.substr(secondDelim+1, length-1);
        return title;
}

string getUrl(string line) {
    string charDelim = "|";
    size_t firstDelim = line.find_first_of(charDelim);
    size_t secondDelim = line.find_first_of(charDelim ,firstDelim+1);
    int length = secondDelim - firstDelim;
    string url = line.substr(firstDelim+1,length-1);
    return url;
}

void getKeywordHistoryAllData(char **argv) {

    ifstream keywordInputFileStream;
    ofstream keywordOutputFileStream;

    string line;
    string keyword = argv[1];
    string inputFile = argv[2];
    string outputFile = "keywordHistory.txt";

    keywordInputFileStream.open(inputFile.c_str());
    keywordOutputFileStream.open(outputFile.c_str());

    while (!keywordInputFileStream.eof()) {
        getline(keywordInputFileStream, line);
        if (isKeywordInLine(line, keyword)==1) {
            keywordOutputFileStream << line << endl;
        }
    }

    keywordOutputFileStream.close();
}

bool isKeywordInLine(string line, string keyword) {

    if (line.find(keyword)==-1) {
        return false;
    }   
    else {
        return true;
    }   
}
