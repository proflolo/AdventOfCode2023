// ConsoleApplication1.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <regex>
#include <charconv>
#include <assert.h>

void Challenge1_1()
{
    std::ifstream input("input1_2.txt");
    std::string line;
    int total = 0;
    while (std::getline(input, line))
    {
        auto firstPos = line.find_first_of("0123456789", 0);
        auto lastPos = line.find_last_of("0123456789");
        auto c1 = line[firstPos] - '0';
        auto c2 = line[lastPos] - '0';
        int sum = c1 * 10 + c2;
        total += sum;
    }

    std::cout << total << std::endl;
}


int string_to_number(const std::string& i_in)
{
    if (i_in == "1") { return 1; }
    else if (i_in == "2") { return 2; }
    else if (i_in == "3") { return 3; }
    else if (i_in == "4") { return 4; }
    else if (i_in == "5") { return 5; }
    else if (i_in == "6") { return 6; }
    else if (i_in == "7") { return 7; }
    else if (i_in == "8") { return 8; }
    else if (i_in == "9") { return 9; }
    else if (i_in == "one") { return 1; }
    else if (i_in == "two") { return 2; }
    else if (i_in == "three") { return 3; }
    else if (i_in == "four") { return 4; }
    else if (i_in == "five") { return 5; }
    else if (i_in == "six") { return 6; }
    else if (i_in == "seven") { return 7; }
    else if (i_in == "eight") { return 8; }
    else if (i_in == "nine") { return 9; }
    return 0;
}

void Challenge1_2()
{
    std::ifstream input("input1_2.txt");
    std::string line;
    int total = 0;
    std::regex r("1|2|3|4|5|6|7|8|9|0|one|two|three|four|five|six|seven|eight|nine");
    while (std::getline(input, line))
    {
        std::smatch m; // <-- need a match object
        std::string copy = line;
        std::string firstMatch;
        std::string lastMatch;
        while (regex_search(copy, m, r))  // <-- use it here to get the match
        {
            std::string match = copy.substr(m.position(), m.length());
            if (firstMatch.length() == 0)
            {
                firstMatch = match;
            }
            lastMatch = match;
            copy = copy.substr(m.position() + 1); // <-- just break the match
        }
        int value = string_to_number(firstMatch) * 10 + string_to_number(lastMatch);
        total += value;
    }
    std::cout << total << std::endl;
}


std::pair<std::string_view, std::string_view> divide(const std::string& i_chars, const std::string_view& i_str)
{
    auto pos = i_str.find_first_of(i_chars);
    if (pos == std::string_view::npos)
    {
        return { i_str, std::string_view() };
    }
    return { std::string_view(&i_str[0], pos), std::string_view(&i_str[pos] + 1, i_str.size() - (pos+1)) };
}

std::vector<std::string_view> split(const std::string& i_chars, const std::string_view& i_str)
{
    std::vector<std::string_view> result;
    std::string_view remaining(&i_str[0], i_str.size());
    auto pos = remaining.find_first_of(i_chars);
    while (pos != std::string::npos && pos < i_str.size())
    {
        std::string_view chunk(&remaining[0], pos );
        result.emplace_back(chunk);
        remaining = remaining.substr(pos+1);
        pos = remaining.find_first_of(i_chars);
    }
    result.emplace_back(remaining);
    return result;
}

std::string_view trim_left(const std::string_view& data, std::string_view trimChars)
{
    std::string_view sv{data};
    sv.remove_prefix(std::min(sv.find_first_not_of(trimChars), sv.size()));
    return sv;
}

std::string_view trim_left(const std::string_view& data)
{
    return trim_left(data, " ");
}

int stoi(std::string_view i_str)
{
    int result = 0;
    std::from_chars(i_str.data(), i_str.data() + i_str.size(), result);
    return result;
}

void Challenge2_2()
{
    int result = 0;
    std::ifstream input("input2.txt");
    std::string line;
    while (std::getline(input, line))
    {
        auto [gameStr, handfulStr] = divide(":", line);
        auto [x, gameIdStr] = divide(" ", gameStr);
        int gameId = stoi(gameIdStr);

        int maxRed = 0;
        int maxGreen = 0;
        int maxBlue = 0;
        for (const std::string_view& handful : split(";", handfulStr))
        {
            for (const std::string_view& colorDraw : split(",", handful))
            {
                auto [numberStr, colorStr] = divide(" ", trim_left(colorDraw));
                int num = stoi(numberStr);
                if (colorStr == "red") { maxRed = std::max(maxRed, num); }
                else if (colorStr == "blue") { maxBlue = std::max(maxBlue, num); }
                else if (colorStr == "green") { maxGreen = std::max(maxGreen, num); }
                else { assert(false); }
            }
        }
        result += maxRed * maxGreen * maxBlue;
        
    }

    std::cout << result << std::endl;
}

void Challenge2_1()
{
    int result = 0;
    std::ifstream input("input2.txt");
    std::string line;
    while (std::getline(input, line))
    {
        auto [gameStr, handfulStr] = divide(":", line);
        auto [x, gameIdStr] = divide(" ", gameStr);
        int gameId = stoi(gameIdStr);
        
        bool valid = true;
        for (const std::string_view& handful : split(";", handfulStr))
        {
            for (const std::string_view& colorDraw : split(",", handful))
            {
                auto [numberStr, colorStr] = divide(" ", trim_left(colorDraw));
                int num = stoi(numberStr);
                if (colorStr == "red") { valid = valid && (num <= 12); }
                else if (colorStr == "blue")  { valid = valid && (num <= 14); }
                else if (colorStr == "green") { valid = valid && (num <= 13); }
                else { assert(false); }
            }
        }
        if (valid)
        {
            result += gameId;
        }
    }

    std::cout << result << std::endl;
}

int main(int argc, char** argv)
{
    
    Challenge2_2();
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
