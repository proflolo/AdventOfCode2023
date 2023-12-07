#include "StdAfx.h"
#include "Challenge7.h"

namespace challenge7
{
    using Bid = int;
    using Points = long long;

	void Part2()
	{
        int result = 0;
        std::ifstream input("input7.txt");
        std::string line;
        std::vector<std::pair<Points, Bid>> hands;
        while (std::getline(input, line))
        {
            auto [hand, bidStr] = divide(" ", line);
            Bid bid = ston<Bid>(bidStr);
            std::unordered_map<char, int> numCards;
            for (char c : hand)
            {
                auto it = numCards.find(c);
                if (it == numCards.end()) { numCards.emplace(c, 1); }
                else { it->second++; }
            }
            std::vector<int> counts;
            int jokers = numCards['J'];
            for (auto kv : numCards)
            {
                if (kv.first != 'J')
                {
                    counts.emplace_back(kv.second);
                }
            }
            std::sort(counts.rbegin(), counts.rend());
            Points high = 0;
            int p1 = jokers;
            if (counts.size() > 0)
            {
                p1 += counts[0];
            }
            if (p1 == 5)
            {
                high = 7;
            }
            else
            {
                int p2 = counts[1];
                switch (p1)
                {
                case 4:
                    high = 6;
                    break;
                case 3:
                    if (p2 == 2) { high = 5; }
                    else { high = 4; }
                    break;
                case 2:
                    if (p2 == 2) { high = 3; }
                    else { high = 2; }
                    break;
                default:
                    high = 1;
                    break;
                }
            }
            static const long long k_base = 100;
            Points low = 0;
            for (char c : hand)
            {
                low *= k_base;
                switch (c)
                {
                case 'A': low += 14; break;
                case 'K': low += 13; break;
                case 'Q': low += 12; break;
                case 'J': low += 0;  break;
                case 'T': low += 10;  break;
                default: low += c - '0';
                }
            }
            Points finalScore = high * k_base * k_base * k_base * k_base * k_base + low;
            hands.emplace_back(finalScore, bid);

        }

        std::sort(hands.begin(), hands.end(), [](const auto& l, const auto& r) { return l.first > r.first; });
        for (size_t i = 0; i < hands.size(); ++i)
        {
            result += hands[i].second * (hands.size() - i);
        }
        std::cout << result << std::endl;
	}

    
	void Part1()
	{
        int result = 0;
        std::ifstream input("input7.txt");
        std::string line;
        std::vector<std::pair<Points, Bid>> hands;
        while (std::getline(input, line))
        {
            auto [hand, bidStr] = divide(" ", line);
            Bid bid = ston<Bid>(bidStr);
            std::unordered_map<char, int> numCards;
            for (char c : hand)
            {
                auto it = numCards.find(c);
                if (it == numCards.end()) { numCards.emplace(c, 1); }
                else { it->second++; }
            }
            std::vector<int> counts;
            for (auto kv : numCards)
            {
                counts.emplace_back(kv.second);
            }
            std::sort(counts.rbegin(), counts.rend());
            Points high = 0;
            int p1 = counts[0];
            if (p1 == 5)
            {
                high = 7;
            }
            else
            {
                int p2 = counts[1];
                switch (p1)
                {
                case 4:
                    high = 6;
                    break;
                case 3:
                    if (p2 == 2) { high = 5; }
                    else { high = 4; }
                    break;
                case 2:
                    if (p2 == 2) { high = 3; }
                    else { high = 2; }
                    break;
                default:
                    high = 1;
                    break;
                }
            }
            static const long long k_base = 100;
            Points low = 0;
            for (char c : hand)
            {
                low *= k_base;
                switch (c)
                {
                case 'A': low += 14; break;
                case 'K': low += 13; break;
                case 'Q': low += 12; break;
                case 'J': low += 11;  break;
                case 'T': low += 10;  break;
                default: low += c - '0';
                }
            }
            Points finalScore = high * k_base * k_base * k_base * k_base * k_base + low;
            hands.emplace_back(finalScore, bid);

        }

        std::sort(hands.begin(), hands.end(), [](const auto& l, const auto& r) { return l.first > r.first; });
        for (size_t i = 0; i < hands.size(); ++i)
        {
            result += hands[i].second * (hands.size() - i);
        }
        std::cout << result << std::endl;
	}
}