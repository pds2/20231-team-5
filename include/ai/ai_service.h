#ifndef AI_SERVICE
#define AI_SERVICE

#include <string>
#include <vector>
#include "openai.hpp"
using namespace std;

class AIService {
    private:
        string base_prompt;
        vector<string> history;
        
        string createMessage(string prompt);
        string historyToString();
    
    public:
        /**
         * Construtor para a classe AIService.
         * 
         * @param base_prompt O prompt inicial para iniciar o chat.
         */
        AIService(string base_prompt);

        /**
         * Reinicia o chat com um novo prompt inicial.
         * 
         * @param base_prompt O novo prompt inicial para iniciar o chat.
         */
        void restartChat(string base_prompt);

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