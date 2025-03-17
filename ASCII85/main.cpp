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

int main() {
    int choice;
    while (true) {
        printMenu();
        std::cin >> choice;
        std::cin.ignore(); // Игнорируем оставшийся символ новой строки

        switch (choice) {
            case 1: {
                // Кодирование
                std::string input;
                std::cout << "Введите строку для кодирования: ";
                std::getline(std::cin, input);


                std::vector<unsigned char> inputData(input.begin(), input.end());


                std::string encoded = ASCII85::encode(inputData);
                std::cout << "Закодированная строка: " << encoded << "\n";
                break;
            }
            case 2: {
                // Декодирование
                std::string input;
                std::cout << "Введите строку для декодирования: ";
                std::getline(std::cin, input);

                try {

                    std::vector<unsigned char> decodedData = ASCII85::decode(input);
                    std::string decoded(decodedData.begin(), decodedData.end());
                    std::cout << "Декодированная строка: " << decoded << "\n";
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Ошибка: " << e.what() << "\n";
                }
                break;
            }
            case 3: {

                std::cout << "Выход из программы.\n";
                return 0;
            }
            default: {
                std::cout << "Неверный выбор. Пожалуйста, выберите 1, 2 или 3.\n";
                break;
            }
        }
    }

    return 0;
}
