#include <iostream>
#include "../include/common/services/ai_service.h"

#include <fstream>
#include <string>

AIService::AIService(string base_prompt) {
    this->base_prompt = base_prompt;
    this->history = vector<string>();

    this->api_key = AIService::extractApiKey();
    this->model = "gpt-3.5-turbo";
    // this-> model = "text-davinci-003";
    this->max_tokens = "100";
    this->temperature = "0";

    openai::start(this->api_key);
    AIService::restartChat();
}

string AIService::extractApiKey(){
    std::ifstream api_key_file("api_key.txt");
    string api_key;
    if (api_key_file.is_open()) {
        std::getline(api_key_file, api_key);
        api_key_file.close();
    } else {
        throw CouldNotRetrieveApiKey();
    }
    return api_key;
}

string AIService::createMessage(string prompt) {
    return "{\"role\":\"user\", \"content\":\"" + prompt + "\"}";
}

string AIService::historyToString() {
    string historyString = "[";
    for (int i = 0; i < history.size(); i++) {
        historyString += createMessage(history[i]);
        if (i != history.size() - 1) {
            historyString += ",";
        }
    }
    historyString += "]";
    return historyString;
}

Json AIService::createApiRequest(string message) {
    string config_string = R"(
    {
        "model": ")" + this->model + R"(",
        "messages": )" + message + R"(,
        "max_tokens": )" + this->max_tokens + R"(,
        "temperature": )" + this->temperature + R"(
    }
    )";
    Json api_request = Json::parse(config_string);
    return api_request;
}

string AIService::extractMessage(Json response){
    string message = response.at("choices")[0].at("message").at("content");
    return message;
}

void AIService::restartChat() {
    this-> history = vector<string>();
    history.push_back(base_prompt);
    string history_string = historyToString();

    Json api_request = AIService::createApiRequest(history_string);
    Json response = openai::chat().create(api_request);
}

string AIService::chat(string prompt) {
    this->history.push_back(prompt);
    string history_string = historyToString();
    
    Json api_request = AIService::createApiRequest(history_string);
    Json response = openai::chat().create(api_request);

    return AIService::extractMessage(response);
}

string AIService::singlePrompt(string prompt) {
    Json api_request = AIService::createApiRequest(AIService::createMessage(prompt));
    Json response = openai::chat().create(api_request);

    return AIService::extractMessage(response);
}