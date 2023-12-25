#include "StdAfx.h"
#include "Challenge15.h"

namespace challenge15
{
  
	void Part1()
	{
        std::ifstream input("input15.txt");
        std::string line;

        long long result = 0;

        
        while (std::getline(input, line))
        {
            uint64 hash = 0;
            for (uint64 c : line)
            {
                if (c == ',')
                {
                    result += hash;
                    hash = 0;
                }
                else
                {
                    hash += c;
                    hash *= 17;
                    hash = hash % 256;
                }
            }
            result += hash;
        }
        
        std::cout << result << std::endl;
	}

    uint64 Hash(const std::string_view& i_str)
    {
        uint64 hash = 0;
        for (uint64 c : i_str)
        {
            
                hash += c;
                hash *= 17;
                hash = hash % 256;
            
        }
        return hash;
    }

    using Lens = std::pair<std::string_view, uint64>;
    using Box = std::vector<Lens>;
   
    void Part2()
    {
        std::ifstream input("input15.txt");
        std::string line;

        long long result = 0;

        std::getline(input, line);
        std::vector<std::string_view> orders = split(",", line);
        std::array<Box, 256> boxes;
        for (std::string_view order : orders)
        {
            auto [label, lens] = divide("-=", order);
            uint64 boxId = Hash(label);
            Box& box = boxes[boxId];
            auto it = std::find_if(box.begin(), box.end(), [label](const Lens& i_lens) {  return i_lens.first == label; });
            if (lens.size() > 0) //=
            {
                uint64 lensNumber = stoi(lens);
                if (it == box.end())
                {
                    box.emplace_back(std::make_pair(label, lensNumber));
                }
                else
                {
                    it->second = lensNumber;
                }
            }
            else //-
            {
                if (it != box.end())
                {
                    box.erase(it);
                }
            }
        }
        
        uint64 boxId = 0;
        for (const Box& box : boxes)
        {
            uint64 slotId = 0;
            for (auto it = box.begin(); it != box.end(); ++it)
            {
                uint64 focusPower = (boxId + 1)* (slotId + 1)* it->second;
                slotId++;
                result += focusPower;
            }
            boxId++;
        }

        std::cout << result << std::endl;
    }
}