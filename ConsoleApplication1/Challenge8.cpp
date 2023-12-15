#include "StdAfx.h"
#include "Challenge8.h"

namespace challenge8
{
    using Bid = int;
    using Points = long long;

    using NodeId = std::string;
    inline bool is_end_node(auto i_node)
    {
        return i_node[2] == 'Z';
        //return i_node % 36 == 35;
    }
    inline bool is_start_node(auto i_node)
    {
        return i_node[2] == 'A';
        //int x = 10;
        //return i_node % 36 == x;
    }

    inline auto parse_instruction(std::string_view i_source)
    {
        using T = int;
        auto t = fragment<3, std::string_view>(" =(,)", i_source);
        return t;
        //return std::make_tuple(ston<T>(std::get<0>(t), 36), ston<T>(std::get<1>(t), 36), ston<T>(std::get<2>(t), 36));
    }

    long long combo_lcm(const std::vector<std::vector<long long>>& nodeCycles, size_t i_index)
    {
        if (i_index == nodeCycles.size())
        {
            return 1;
        }
        else
        {
            long long result = std::numeric_limits<long long>::max();
            for (auto value : nodeCycles[i_index])
            {
                auto candidate = std::lcm(value, combo_lcm(nodeCycles, i_index + 1));
                if (candidate < result)
                {
                    result = candidate;
                }
            }
            return result;
        }
    }

	void Part2()
	{
        std::ifstream input("input8.txt");
        std::string directionsLine;
        std::getline(input, directionsLine);

        std::string entryLine;
        std::unordered_map<NodeId, std::pair<NodeId, NodeId>> route;
        std::vector<NodeId> startNodes;
        while (std::getline(input, entryLine))
        {
            if (entryLine.size() == 0)
            {
                continue;
            }
            auto [source, left, right] = parse_instruction(entryLine);
            route.emplace(source, std::make_pair(left, right));
            if (is_start_node(source))
            {
                startNodes.emplace_back(source);
            }
        }

        long long result = 0;
        std::vector<std::vector<long long>> nodeCycles;
        using State = std::pair<int, NodeId>;
        {
            for (size_t i = 0; i < startNodes.size(); ++i)
            {
                std::map<State, int> states;
                bool finished = false;
                int steps = 0;
                State currentState;
                currentState.first = 0;
                currentState.second = startNodes[i];
                std::vector<long long> cycles;
                while (states.find(currentState) == states.end())
                {
                    char instruction = directionsLine[currentState.first];
                    NodeId nextNode;
                    switch (instruction)
                    {
                    case 'L':
                        nextNode = route.at(currentState.second).first;
                        break;
                    case 'R':
                    default:
                        nextNode = route.at(currentState.second).second;
                        break;
                    }

                    steps++;
                    if (is_end_node(nextNode))
                    {
                        states.emplace(currentState, steps);
                        cycles.emplace_back(steps);
                    }

                    currentState.first = (currentState.first + 1) % directionsLine.size();
                    currentState.second = nextNode;
                }
                nodeCycles.emplace_back(cycles);
            }
        }

        result = combo_lcm(nodeCycles, 0);

        std::cout << result << std::endl;
	}


	void Part1()
	{
        std::ifstream input("input8_sample.txt");
        std::string directionsLine;
        std::getline(input, directionsLine);
        
        std::string entryLine;
        std::unordered_map<NodeId, std::pair<NodeId, NodeId>> route;
        while(std::getline(input, entryLine))
        {
            if (entryLine.size() == 0)
            {
                continue;
            }
            auto [source, left, right] = parse_instruction(entryLine);
            route.emplace(source, std::make_pair(left, right));
        }

        NodeId current = "AAA";
        const NodeId destination = "ZZZ";
        //NodeId current = ston<int>("AAA", 36);
        //const NodeId destination = ston<int>("ZZZ", 36);
        int instructionPos = 0;
        int result = 0;
        while (current != destination)
        {
            char instruction = directionsLine[instructionPos];
            switch (instruction)
            {
            case 'L':
                current = route.at(current).first;
                break;
            case 'R':
            default:
                current = route.at(current).second;
                break;
            }
            instructionPos = (instructionPos + 1) % directionsLine.size();
            result++;
        }
        //14681
        std::cout << result << std::endl;
	}
}