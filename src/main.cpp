#include <iostream>
#include <vector>
#include <string>
#include "ASCII_85.h"

void printMenu() {
    std::cout << "--- Меню ---\n";
    std::cout << "1. Кодировать строку в ASCII85\n";
    std::cout << "2. Декодировать строку из ASCII85\n";
    std::cout << "3. Выйти\n";
    std::cout << "Выберите опцию (1-3): ";
}

int main(int argc, char* argv[]) {
   
    if (argc == 2) {
        int mode = std::stoi(argv[1]);
        std::string input;
        std::getline(std::cin, input); 

        try {
            if (mode == 1) {  
                std::vector<unsigned char> inputData(input.begin(), input.end());
                std::cout << ASCII85::encode(inputData);
                return 0;
            } 
            else if (mode == 2) {  
                std::vector<unsigned char> decoded = ASCII85::decode(input);
                std::string result(decoded.begin(), decoded.end());
                std::cout << result;
                return 0;
            }
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            return 1;
        }
    }


    int choice;
    while (true) {
        printMenu();
        std::cin >> choice;
        std::cin.ignore(); 

        switch (choice) {
            case 1: {
                std::string input;
                std::cout << "Введите строку для кодирования: ";
                std::getline(std::cin, input);

                std::vector<unsigned char> inputData(input.begin(), input.end());
                std::string encoded = ASCII85::encode(inputData);
                std::cout << "Закодированная строка: " << encoded << "\n";
                break;
            }

            case 2: {
                std::string input;
                std::cout << "Введите строку для декодирования: ";
                std::getline(std::cin, input);

                std::vector<unsigned char> decodedData = ASCII85::decode(input);
                if (!decodedData.empty() && decodedData[0] == 0 && decodedData.size() == 1) {
                    std::cout << "Обнаружены недопустимые символы в строке!" << std::endl;
                } else {
                    std::string decoded(decodedData.begin(), decodedData.end());
                    std::cout << "Декодированная строка: " << decoded << "\n";
                }
                break;
}
            case 3:
                return 0;
            default:
                std::cout << "Неверный выбор. Пожалуйста, выберите 1, 2 или 3.\n";
        }
    }
}
