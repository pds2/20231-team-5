/**
 * @file quizcard.h
 * @brief Declaração da classe QuizCard.
 */

#ifndef QUIZCARD_H
#define QUIZCARD_H

#include <string>
using std::string;

/**
 * @brief Classe que representa um cartão.
 */

class QuizCard{

  public:
    /**
     * @brief Construtor padrão da classe QuizCard.
     */
    QuizCard() = default;

    /**
     * @brief Construtor da classe QuizCard.
     * @param question A pergunta do cartão.
     * @param answer A resposta do cartão.
     */
    QuizCard(const string question, const string answer);
    
    /**
     * @brief Destrutor padrão da classe QuizCard.
     */
    ~QuizCard() = default;

    /**
     * @brief Obtém a resposta do cartão.
     * @return A resposta do cartão.
     */
    string getAnswer() const;

    /**
     * @brief Obtém a pergunta do cartão.
     * @return A pergunta do cartão.
     */
    string getQuestion() const;

  private:
    string question;
    string answer;

};

#endif