#ifndef AI_SERVICE
#define AI_SERVICE

#include <string>
#include <vector>
#include "../../third_party/openai/openai.hpp"

using namespace std;
using Json = nlohmann::json;

class CouldNotRetrieveApiKey{};

class AIService {
    private:
        string base_prompt;
        vector<string> history;

        string api_key;
        string model;
        string max_tokens;
        string temperature;
        
        string extractApiKey();
        string createMessage(string prompt);
        string historyToString();

        Json createApiRequest(string message);
        string extractMessage(Json response);
    
    public:
        /**
         * Construtor para a classe AIService.
         * 
         * @param base_prompt O prompt base para iniciar o chat.
         */
        AIService(string base_prompt);

        /**
         * Reinicia o chat com o prompt base.
         * 
         */
        void restartChat();

        /**
         * Continua o chat com o prompt fornecido.
         * 
         * @param prompt O prompt para continuar o chat.
         * @return A resposta do modelo de IA.
         */
        string chat(string prompt);

        /**
         * Envia um único prompt para o modelo de IA e retorna a resposta.
         * 
         * @param prompt O prompt para enviar ao modelo de IA.
         * @return A resposta do modelo de IA.
         */
        string singlePrompt(string prompt);
    };        
#endif