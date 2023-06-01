#ifndef AI_SERVICE
#define AI_SERVICE

#include <string>
#include <vector>
#include "../../third_party/openai/openai.hpp"

using namespace std;
using Json = nlohmann::json;

/**
 * @brief Exceção lançada quando a chave de API para o serviço OpenAI não pôde ser recuperada.
 */
class CouldNotRetrieveApiKeyException : exception {
    public:
        virtual const char* what() const throw() {
            return "Não foi possível recuperar a chave de API!";
        }
};

/**
 * @brief Exceção lançada quando o modelo OpenAI está sobrecarregado e não pode processar mais solicitações.
 */

class ModelOverloadedException : exception {
    public:
        virtual const char* what() const throw() {
            return "O modelo utilizado está sobrecarregado!";
        }
};

/**
 * @brief A classe AIService é responsável por fornecer serviços de inteligência artificial para fins genéricos. 
 * Ela utiliza a biblioteca OpenAI para gerar respostas para os prompts fornecidos pelo usuário.
 */
class AIService {
    private:
        string base_prompt;
        vector<string> history;

        string api_key;
        string model;
        string max_tokens;
        string temperature;
        unsigned int nb_tries;
        
        string clean(string str);

        string extractApiKey();
        string formatPrompt(string prompt);
        string historyToString();

        Json createApiRequest(string message);
        Json sendApiRequest(Json api_request);
        string extractMessage(Json response);
    
    public:
        /**
         * @brief Constrói um novo objeto AIService.
         * @param base_prompt O prompt inicial para o serviço de IA.
         */
        AIService(string base_prompt);

        /**
         * @brief Reinicia o histórico de conversação do serviço de IA.
         */
        void restartChat();

        /**
         * @brief Obtém uma resposta do serviço de IA considerando a conversa toda.
         * @param prompt O prompt para o serviço de IA.
         * @return A resposta do serviço de IA.
         */
        string chat(string prompt);

        /**
         * @brief Obtém uma resposta do serviço de IA.
         * @param prompt O prompt para o serviço de IA.
         * @return A resposta do serviço de IA.
         */
        string singlePrompt(string prompt);
    };        
#endif