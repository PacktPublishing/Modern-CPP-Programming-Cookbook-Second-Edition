#pragma once

#include <iostream>
#include <random>
#include <algorithm>
#include <array>

namespace recipe_2_04
{
   void monte_carlo_simulation()
   {
      std::array<int, std::mt19937::state_size> seed_data {};
      std::random_device rd;

      std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
      std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
      auto eng = std::mt19937{ seq };
      auto dist = std::uniform_real_distribution<>{ 0, 1 };

      auto const Simulations = 100;
      auto const Samples = 50000;

      for (auto j = 0; j<Simulations; j++)
      {
         auto hit = 0;
         auto x = 0.0;
         auto y = 0.0;

         for (auto i = 0; i<Samples; i++)
         {
            x = dist(eng);
            y = dist(eng);

            if (y <= std::sqrt(1 - std::pow(x, 2))) hit += 1;
         }

         std::cout << "" << 4.0 * hit / Samples << '\n';
      }
   }

   void execute()
   {
      monte_carlo_simulation();
   }
}