// mosLibraries.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
//#include "include/rapidjson/document.h"

#include "structs.h"

std::vector<BookDetail> Library;

int main(int argc, char* argv[])
{
    long user_id = 0;
    long max_user_id = 999999999;
    switch (argc) {
    case 2:
        user_id = (long)(std::atof(argv[1]) / RAND_MAX * max_user_id + 1);
        break;
    default:
        std::srand(time(0));
        user_id = std::rand();
    }
    
    User cur_user;
    std::map<int, BookDetail> recommend = cur_user.getRecommendations(5);

    std::string output_json = "{\"recommendations:\" [";
    std::map<int, BookDetail>::reverse_iterator iter_chosenBook = recommend.rbegin();
    for (; iter_chosenBook != recommend.rend(); iter_chosenBook++) {
        if (iter_chosenBook != recommend.rbegin()) {
            output_json = output_json + ", ";
        }
        output_json = output_json + "{"
                     + "\"id\": " + std::to_string(iter_chosenBook->second.id) + ", "
                     + "\"title\": " + iter_chosenBook->second.title + ", "
                     + "\"author\": " + iter_chosenBook->second.author 
                     + "}";
    }
    output_json = output_json + "]";

    std::cout << output_json;

    return recommend.size();
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
