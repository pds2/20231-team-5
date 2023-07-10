// #include <cctype>
// #include<iostream>

// #include "../../../include/gperfil/service/viewperfil.h"

// ViewPerfil::ViewPerfil(PlayerService* player_service) : View(player_service) {} 

// void ViewPerfil::displayMenu(){
//   //std::cout << "Aqui foi 3" << std::endl;
//   vector<string> content{}; // Cria um vetor vazio de strings para armazenar o conteúdo
//   //std::cout << "Aqui foi 4" << std::endl;

//   addEmptyLines(content,1);
//   //std::cout << "Aqui foi 5" << std::endl;
//   addToNextLine(content,"Bem vindo ao GPPerfil. Digite a opção desejada!"); 
//   addEmptyLines(content,5);
//   addToNextLine(content,"MULTIPLAYER ------------------ M");
//   addEmptyLines(content,1);
//   addToNextLine(content,"REGRAS ----------------------- R");
//   addEmptyLines(content,1);
//   addToNextLine(content,"SAIR ------------------------- X");


//   bool loopAgain{true}; // Controla o loop do menu


//   while(loopAgain){
//     //std::cout << "Aqui foi 6" << std::endl;
//     char userChoice=getUserChoice(content,"GPTrivia"); // Obtém a escolha do usuário
//     //std::cout << "Aqui foi 7" << std::endl;

//     switch (userChoice)
//     {
//     case 'M':
//       loopAgain=displayMultiPlayer(); // Exibe o menu para o jogo multiplayer
//       break;
//     case 'R':
//       loopAgain=displayRules(); // Exibe as regras do jogo
//       break;
//     case 'X':
//       throw ExitGame(); // Lança uma exceção para sair do jogo
//     }
//   }

// }

// bool ViewPerfil::displayRules(){ 
//   vector<string> content=vector<string>(); // Cria um vetor vazio de strings para armazenar o conteúdo

//   addToNextLine(content,"1 - Fusce finibus tristique dui. Nullam est ligula, vestibulum iniaculis et, rutrum nec tortor. Lorem ipsum dolor sit amet, consectetur."); 
//   addEmptyLines(content,1); 
//   addToNextLine(content,"2 - Fusce finibus tristique dui. Nullam est ligula, vestibulum iniaculis et, rutrum nec tortor. Lorem ipsum dolor sit amet, consectetur."); 
//   addEmptyLines(content,1); 
//   addToNextLine(content,"3 - Fusce finibus tristique dui. Nullam est ligula, vestibulum iniaculis et, rutrum nec tortor. Lorem ipsum dolor sit amet, consectetur."); 
//   addEmptyLines(content,2); 
//   addToNextLine(content,"VOLTAR ----------------------- V"); 

//   while(true){ 
//     char userChoice=getUserChoice(content,"REGRAS"); // Obtém a escolha do usuário

//     if(userChoice=='V') return true; // Retorna true se o usuário escolher voltar
//   }
// }

// bool ViewPerfil::displayMultiPlayer(){ 
//   vector<string> content=vector<string>(); // Cria um vetor vazio de strings para armazenar o conteúdo

//   unsigned int numPlayers=getNumberOfPlayers(); // Obtém o número de jogadores
//   vector<string> usernamesList=getUsernamesList(content,numPlayers); // Obtém a lista de usernames dos jogadores

//   addEmptyLines(content,1); 
//   addToNextLine(content,"INICIAR ---------------------- I"); 
//   addEmptyLines(content,1); 
//   addToNextLine(content,"VOLTAR ----------------------- V"); 

//   while(true){ 
//     char userChoice=getUserChoice(content,"MULTIPLAYER"); // Obtém a escolha do usuário

//     switch(userChoice)
//     {
//       case 'I':
//         for(std::string x:usernamesList) player_service->addPlayer(x); // Adiciona os jogadores ao serviço de jogadores
//         return false; // Retorna false para indicar que o jogo deve começar
//       case 'V':
//         return true; // Retorna true para indicar que o usuário escolheu voltar
//     }
//   }
// }

// char ViewPerfil::getUserChoice(const vector<string>& content, const string header){
//   std::cout << "Aqui foi 7" << std::endl;
//   setHeader(header); 
//   std::cout << "Aqui foi 8" << std::endl;
//   setContent(content);
//   std::cout << "Aqui foi 9" << std::endl;

//   string userChoice{};
//   while(true){
//     std::cout << "Aqui foi 10" << std::endl;
//     userChoice=display("Sua escolha: "); // Exibe a mensagem "Sua escolha: " e obtém a entrada do usuário
//     std::cout << "Aqui foi 11" << std::endl;
//     if(userChoice.size()==1) break; // Verifica se foi inserido apenas um caractere
//   }

//   return toupper(userChoice[0]); // Converte o caractere para maiúsculo e retorna
// }

// string ViewPerfil::getUserAnswer(const vector<string>& content, const string header){ 
//   setHeader(header); 
//   setContent(content);

//   string userAnswer{};
//   while(true){
//     userAnswer=display("Sua resposta: "); // Exibe a mensagem "Sua resposta: " e obtém a resposta do usuário
//     if(!userAnswer.empty()) break; // Verifica se a resposta não está vazia
//   }

//   return userAnswer;
// }

// unsigned int ViewPerfil::getNumberOfPlayers(){ 
//   vector<string> content{};

//   addEmptyLines(content,1);
//   addToNextLine(content,"Digite o número de jogadores: (máximo 4):");

//   unsigned int numPlayers{};
//   while(true){
//     try{
//       string numString=getUserAnswer(content,"MULTIPLAYER"); // Obtém a entrada do usuário
//       numPlayers=std::stoi(numString); // Tenta converter a entrada para um número inteiro
//       if(numPlayers>4||numPlayers<=1) throw InvalidNumber(); // Lança uma exceção se o número estiver fora do intervalo válido
//       break;
//     }catch(const std::exception& e){
//       // Caso ocorra uma exceção, continua solicitando um número válido
//     }
//   }

//   return numPlayers; 
// }

// vector<string> ViewPerfil::getUsernamesList(vector<string>& content, int numPlayers) {
//   addEmptyLines(content, 1);
//   addToNextLine(content, "Adicione os usernames dos jogadores (máximo 15 caracteres).");
//   addEmptyLines(content, 2);

//   vector<string> usernamesList{}; // Armazena nomes de usuários de jogadores
//   usernamesList.reserve(numPlayers);

//   // Loop para obter o nome de usuário de cada jogador
//   for (int i = 1; i <= numPlayers; i++) {
//     string numString = to_string(i);
//     addToNextLine(content, numString + "º jogador: ");

//     string username{};
//     while (true) {
//       try {
//         username = getUserAnswer(content, "MULTIPLAYER"); // Obtém a resposta do usuário
//         if (username.size() > 15) throw InvalidNameException(); // Lança uma exceção se o nome de usuário exceder o limite de caracteres
//         break;
//       } catch (const std::exception& e) {
//         // Continua solicitando um nome de usuário válido caso ocorra uma exceção
//       }
//     }

//     addToCurrentLine(content, username);
//     addEmptyLines(content, 1);

//     usernamesList.push_back(move(username)); // Adciona o nome de usuário na lista de usuários de jogadores
//   }

//   return usernamesList;
// }

// void ViewPerfil::addEmptyLines(vector<string>& content, unsigned int numberOfLines){
//   while(numberOfLines>0){
//     content.push_back("");
//     numberOfLines--;
//   }
// }

// void ViewPerfil::addToNextLine(vector<string>& content, const string newContent){
//   content.push_back(newContent);
// }

// void ViewPerfil::addToCurrentLine(vector<string>& content, const string newContent){
//   unsigned int index=content.size()-1;
//   content[index]+=newContent;
// }