#ifndef AI_SERVICE
#define AI_SERVICE

#include <string>
#include <curl/curl.h>
// #include "openai.hpp"
using namespace std;

class AIService {
    private:
        string initial_prompt;
    
    public:
        string promptGPT(string prompt);
};
#endif