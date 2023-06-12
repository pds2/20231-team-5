#include <iostream>
#include <regex>
#include "../include/common/services/ai_service.h"

#include <fstream>
#include <string>

AIService::AIService(string base_prompt)
{
    this->base_prompt = base_prompt;
    this->history = vector<string>();

    this->api_key = this->extractApiKey();
    this->model = "text-davinci-003";
    this->max_tokens = "100";
    this->temperature = "0.7";
    this->nb_tries = 5;

    openai::start(this->api_key);
    this->restartChat();
}

string AIService::extractApiKey()
{
    std::ifstream api_key_file("api_key.txt");
    string api_key;
    if (api_key_file.is_open())
    {
        std::getline(api_key_file, api_key);
        api_key_file.close();
    }
    else
    {
        throw CouldNotRetrieveApiKeyException();
    }
    return api_key;
}

string AIService::clean(string str)
{
    size_t start = str.find_first_not_of(" ");
    if (start != string::npos)
    {
        str = str.substr(start);
    }
    else
    {
        str = "";
    }

    size_t end = str.find_last_not_of(" ");
    if (end != string::npos)
    {
        str = str.substr(0, end + 1);
    }
    else
    {
        str = "";
    }

    str = regex_replace(str, regex("\n"), "");
    return str;
}

string AIService::formatPrompt(string prompt)
{
    return "\"" + prompt + "\"";
}

string AIService::historyToString()
{
    string historyString = "";
    for (int i = 0; i < history.size(); i++)
    {
        string phrase = this->clean(history[i]);
        historyString += phrase;

        if (!phrase.empty() && i == history.size() - 1)
        {
            historyString += ".";
            continue;
        }

        if (!phrase.empty())
        {
            historyString += ". ";
        }
    }
    return this->formatPrompt(historyString);
}

Json AIService::createApiRequest(string message)
{
    string config_string = R"(
    {
        "model": ")" + this->model +
                           R"(",
        "prompt": )" + message +
                           R"(,
        "max_tokens": )" + this->max_tokens +
                           R"(,
        "temperature": )" + this->temperature +
                           R"(
    }
    )";
    Json api_request = Json::parse(config_string);
    return api_request;
}

Json AIService::sendApiRequest(Json api_request)
{
    for (int i = 0; i < this->nb_tries; i++)
    {
        try
        {
            Json response = openai::completion().create(api_request);
            return response;
        }
        catch (std::runtime_error &e)
        {
            // Tenta denovo
        }
    }
    throw ModelOverloadedException();
}

string AIService::extractMessage(Json response)
{
    string message = response.at("choices")[0].at("text");
    message = this->clean(message);
    return message;
}

void AIService::restartChat()
{
    this->history = vector<string>();
    history.push_back(base_prompt);
    string history_string = historyToString();
}

vector<string> AIService::getHistory()
{
    return this->history;
}

string AIService::getBasePrompt()
{
    return this->base_prompt;
}

void AIService::setTemperature(string temperature){
    this->temperature = temperature;
}

string AIService::chat(string prompt)
{
    this->history.push_back(prompt);
    string history_string = historyToString();

    Json api_request = this->createApiRequest(history_string);
    Json response = this->sendApiRequest(api_request);

    return this->extractMessage(response);
}

string AIService::singlePrompt(string prompt)
{
    Json api_request = this->createApiRequest(this->formatPrompt(prompt));
    Json response = this->sendApiRequest(api_request);

    return this->extractMessage(response);
}