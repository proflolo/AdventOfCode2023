#include "StdAfx.h"
#include "Challenge6.h"

namespace challenge6
{
    using Time = long long;
    using Distance = long long;
    struct Race
    {
        Time time;
        Distance recordDistance;
    };

	void Part2()
	{
       
        int result = 1;
        std::ifstream input("input6.txt");

        std::string timesLine;
        std::getline(input, timesLine);
        timesLine.erase(std::remove(timesLine.begin(), timesLine.end(), ' '), timesLine.end());
        std::string distancesLine;
        std::getline(input, distancesLine);
        distancesLine.erase(std::remove(distancesLine.begin(), distancesLine.end(), ' '), distancesLine.end());
        auto [x, timeStr] = divide(":", timesLine);
        auto [y, distanceStr] = divide(":", distancesLine);
        Time time = ston<Time>(timeStr);
        Distance recordDistance = ston<Distance>(distanceStr);

        int times = 0;
        for (Time x = 0; x < time; ++x)
        {
            Distance d = x * (time - x);
            if (d > recordDistance)
            {
                times++;
            }
        }
        double ac = sqrt(time * time - 4 * recordDistance);
        ;
        Time pushMin = (-time + Time(ceil(ac))) / -2;
        Time pushMax = (-time - Time(floor(ac))) / -2;
        //auto x2 = pushMax + pushMin;
        //result *= (pushMax - pushMin);
        result *= (times);

        
        std::cout << result << std::endl;
	}


	void Part1()
	{
        int result = 1;
        std::ifstream input("input6.txt");
        
        std::string timesLine;
        std::getline(input, timesLine);
        std::vector<std::string_view> times = split(" ", timesLine);
        std::string distancesLine;
        std::getline(input, distancesLine);
        std::vector<std::string_view> distances = split(" ", distancesLine);
        
        for (int i = 1; i < times.size(); ++i)
        {
            Race r{ston<Time>(times[i]), ston<Distance>(distances[i]) };
            int times = 0;
            for (Time x = 0; x < r.time; ++x)
            {
                Distance d = x * (r.time - x);
                if (d > r.recordDistance)
                {
                    times++;
                }
            }
            //Time pushMin = (-r.time + sqrtf(r.time * r.time - 4 * r.recordDistance)) / -2;
            //Time pushMax = (- r.time - sqrtf(r.time * r.time - 4 * r.recordDistance)) / -2;
            //result *= (pushMax - pushMin);
            result *= (times);

        }
        std::cout << result << std::endl;
    

	}
}