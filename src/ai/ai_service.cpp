#include <iostream>
#include "../include/ai/ai_service.h"

AIService::AIService(string base_prompt) {
    this->base_prompt = base_prompt;
    openai::start();
    AIService::restartChat();
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

void AIService::restartChat() {
    this-> history = vector<string>();
    history.push_back(base_prompt);
    string history_string = historyToString();

    auto chat = openai::chat();
    chat.create(R"(
    {
        "model": "gpt-3.5-turbo",
        "messages":)" + history_string + R"(,
        "max_tokens": 1000,
        "temperature": 0
    }
    )"_json);
}

string AIService::chat(string prompt) {
    this->history.push_back(prompt);
    string history_string = historyToString();

    auto chat = openai::chat();
    chat.create(R"(
    {
        "model": "gpt-3.5-turbo",
        "messages":)" + history_string + R"(,
        "max_tokens": 1000,
        "temperature": 0
    }
    )"_json);

    string response = chat.dump(2);
    return response;
}

string AIService::singlePrompt(string prompt) {
    auto chat = openai::chat().create(R"(
    {
        "model": "gpt-3.5-turbo",
        "messages":[)" + createMessage(prompt) + R"(],
        "max_tokens": 20,
        "temperature": 0
    }
    )"_json);

    string response = chat.dump(2);
    return response;
}

// import openai_secret_manager

// assert "openai" in openai_secret_manager.get_services()
// secrets = openai_secret_manager.get_secret("openai")

// openai.api_key = secrets["api_key"]

// conversation_history = []

// def ask_chatgpt(prompt):
//     global conversation_history
//     conversation_history.append(f'User: {prompt}')
//     prompt = ''.join(conversation_history)
//     response = openai.Completion.create(
//         engine="davinci",
//         prompt=prompt,
//         temperature=0.7,
//         max_tokens=150,
//         top_p=1,
//         frequency_penalty=0,
//         presence_penalty=0
//     )
//     chatgpt_response = response['choices'][0]['text']
//     conversation_history.append(f'ChatGPT: {chatgpt_response}')
//     return chatgpt_response

// print(ask_chatgpt('Hello!'))
// print(ask_chatgpt('How are you?'))
// ```

// In this example, we maintain a `conversation_history` list that stores the previous interactions between the user and ChatGPT. Each time we call the `ask_chatgpt` function, we append the user's prompt to the `conversation_history` list and concatenate all previous interactions to form a new prompt that includes the context of the conversation. This new prompt is then passed to the ChatGPT API to generate a response that takes into account the previous interactions. The ChatGPT response is also appended to the `conversation_history` list before being returned to the user.

// Is this what you were looking for?

