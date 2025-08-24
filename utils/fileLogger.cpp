#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>

using std::string,
std::ofstream,
std::ifstream,
std::ios,
std::cerr,
std::endl;

enum Level {
    INFO,
    WARNING,
    ERROR
};

class Logger{

    private:
        ofstream logFile;

        string levelString(Level level){
            switch (level){
                case INFO:
                    return "INFO";
                case WARNING:
                    return "WARNING";
                case ERROR:
                    return "ERROR";
                default:
                    return "INVALID LEVEL";
            }
        }

    public:
        Logger(const string& file){
            logFile.open(file, ios::app);
            if (!logFile.is_open()){
                cerr << "File can't open" << endl;

            }
        }

        ~Logger(){
            logFile.close();
        }

        void log(Level level, const string& logMessage){
            char timeStamp[20];
            time_t current = time(0);
            tm* timeInfo = localtime(&current);
            strftime(timeStamp, sizeof(timeStamp), "%d-%m-%Y %H:%M", timeInfo);
        }
};