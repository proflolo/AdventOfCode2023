#include "StdAfx.h"
#include "Challenge9.h"

namespace challenge9
{
    using Num = long long;

    constexpr Num pascal_raw(Num i_fila, Num i_columna)
    {
        if (i_columna > i_fila || i_columna < 0)
        {
            return 0;
        }

        if (i_fila == 0 && i_columna == 0)
        {
            return 1;
        }
        auto y = pascal_raw(i_fila - 1, i_columna);
        auto x = pascal_raw(i_fila - 1, i_columna - 1);
        return  x + y;
    }

    template<size_t N, size_t M>
    struct Cache {
        constexpr Cache() : arr() {
            for (auto i = 0; i != N; ++i)
            {
                for (auto j = 0; j != M; ++j)
                {
                    arr[i * M + j] = pascal_raw(i, j); 
                }
            }
        }

        inline constexpr bool Contains(auto i_fila, auto i_columna) const
        {
            return i_fila >= 0 && i_fila < N && i_columna < M && i_columna >= 0;
        }

        inline constexpr auto Get(auto i_fila, auto i_columna) const
        {
            return arr[i_fila * M + i_columna];
        }

        int arr[N * M];
    };

    constexpr Cache<10, 10> cache;
    
    inline constexpr Num pascal(const Num i_fila, const Num i_columna)
    {
        if (cache.Contains(i_fila, i_columna))
        {
            return cache.Get(i_fila, i_columna);
        }
        
        if (i_columna > i_fila || i_columna < 0)
        {
            return 0;
        }

        if (i_fila == 0 && i_columna == 0)
        {
            return 1;
        }

        return pascal(i_fila - 1, i_columna-1) + pascal(i_fila - 1, i_columna);
    }

	void Part2()
	{
        std::ifstream input("input9_sample.txt");

        std::string entryLine;
        Num result = 0;
        while (std::getline(input, entryLine))
        {
            std::vector<std::string_view> numbersStr = split(" ", entryLine);
            std::vector<Num> numbers;
            std::transform(numbersStr.rbegin(), numbersStr.rend(), std::back_inserter(numbers), [](const auto& x) { return ston<Num>(x); });
            bool finished = false;
            std::vector<Num> leftMost;
            
            while (!finished)
            {
                leftMost.emplace_back(numbers[numbers.size() -1]);
                finished = true;
                for (size_t i = 0; i < numbers.size() - 1; ++i)
                {
                    Num delta = numbers[i] - numbers[i + 1];
                    numbers[i] = delta;
                    finished = finished && numbers[i] == 0;
                }
                numbers.resize(numbers.size() - 1);
            }

            std::reverse(leftMost.begin(), leftMost.end());
            Num acum = 0;
            for (Num n : leftMost)
            {
                acum = n - acum;
            }
            result += acum;
        }
        //72799 --> too high
        //1019
        std::cout << result << std::endl;
	}

    

	void Part1()
	{
        std::ifstream input("input9.txt");
        
        std::string entryLine;
        Num result = 0;
        while (std::getline(input, entryLine))
        {
            std::vector<std::string_view> numbersStr = split(" ", entryLine);
            Num x2 = 0;
            {
                std::vector<Num> numbers;
                std::transform(numbersStr.begin(), numbersStr.end(), std::back_inserter(numbers), [](const auto& x) { return ston<Num>(x); });
                for (size_t i = 0; i < numbers.size(); ++i)
                {
                    Num p = pascal(numbers.size(), i);
                    if (i % 2 == 0)
                    {
                        x2 -= numbers[i] * p;
                    }
                    else
                    {
                        x2 += numbers[i] * p;
                    }
                }
            }

            std::vector<Num> numbers;
            std::transform(numbersStr.rbegin(), numbersStr.rend(), std::back_inserter(numbers), [](const auto& x) { return ston<Num>(x); });
            Num acum = numbers[0];
            bool finished = false;
            while (!finished)
            {
                auto copy = numbers;
                finished = true;
                for (size_t i = 0; i < numbers.size() - 1; ++i)
                {
                    Num delta = numbers[i] - numbers[i + 1];
                    if(i == 0)
                    { 
                        acum += delta;
                    }
                    numbers[i] = delta;
                    finished = finished && numbers[i] == 0;
                }
                numbers.resize(numbers.size() - 1);
            }
            result += acum;
            assert(std::abs(x2) == std::abs(acum));
        }
        std::cout << result << std::endl;
	}
}