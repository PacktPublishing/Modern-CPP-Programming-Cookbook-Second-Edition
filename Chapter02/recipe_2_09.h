#pragma once

#include <string>
#include <regex>

namespace recipe_2_09
{
   using namespace std::string_literals;

   template <typename CharT>
   using tstring = std::basic_string<CharT, std::char_traits<CharT>, std::allocator<CharT>>;

   template <typename CharT>
   bool is_valid_format(tstring<CharT> const & pattern, tstring<CharT> const & text)
   {
      auto rx = std::basic_regex<CharT>{ pattern, std::regex_constants::icase };
      return std::regex_match(text, rx);
   }

   bool is_valid_email_format(std::string const & email)
   {
      auto rx = std::regex{ R"(^[A-Z0-9._%+-]+@[A-Z0-9.-]+\.[A-Z]{2,}$)"s, std::regex_constants::icase };
      return std::regex_match(email, rx);
   }

   bool is_valid_email_format_w(std::wstring const & text)
   {
      return is_valid_format(LR"(^[A-Z0-9._%+-]+@[A-Z0-9.-]+\.[A-Z]{2,}$)"s, text);
   }

   std::tuple<bool, std::string, std::string, std::string> is_valid_email_format_with_result(std::string const & email)
   {
      auto rx = std::regex{ R"(^([A-Z0-9._%+-]+)@([A-Z0-9.-]+)\.([A-Z]{2,})$)"s, std::regex_constants::icase };
      auto result = std::smatch{};
      auto success = std::regex_match(email, result, rx);

      return std::make_tuple(
         success,
         success ? result[1].str() : ""s,
         success ? result[2].str() : ""s,
         success ? result[3].str() : ""s);
   }

   void execute()
   {
      auto ltest = [](std::string const & email)
      {
         std::cout << std::setw(30) << std::left
            << email << " : "
            << (is_valid_email_format(email) ? "valid" : "invalid")
            << '\n';
      };

      auto ltest2 = [](auto const & email)
      {
         std::wcout << std::setw(30) << std::left
            << email << L" : "
            << (is_valid_email_format_w(email) ? L"valid" : L"invalid")
            << '\n';
      };

      auto ltest3 = [](std::string const & email)
      {
         auto[valid, localpart, hostname, dnslabel] =
            is_valid_email_format_with_result(email);

         std::cout << std::setw(30) << std::left
            << email << " : "
            << std::setw(10) << (valid ? "valid" : "invalid")
            << '\n' << "   local=" << localpart << ";domain=" << hostname << ";dns=" << dnslabel
            << '\n';
      };

      std::cout << "-- ltest\n";
      ltest("JOHN.DOE@DOMAIN.COM"s);
      ltest("JOHNDOE@DOMAIL.CO.UK"s);
      ltest("JOHNDOE@DOMAIL.INFO"s);
      ltest("J.O.H.N_D.O.E@DOMAIN.INFO"s);
      ltest("ROOT@LOCALHOST"s);
      ltest("john.doe@domain.com"s);

      std::cout << "-- ltest2\n";
      ltest2(L"JOHN.DOE@DOMAIN.COM"s);
      ltest2(L"JOHNDOE@DOMAIL.CO.UK"s);
      ltest2(L"JOHNDOE@DOMAIL.INFO"s);
      ltest2(L"J.O.H.N_D.O.E@DOMAIN.INFO"s);
      ltest2(L"ROOT@LOCALHOST"s);
      ltest2(L"john.doe@domain.com"s);

      std::cout << "-- ltes3\n";
      ltest3("JOHN.DOE@DOMAIN.COM"s);
      ltest3("JOHNDOE@DOMAIL.CO.UK"s);
      ltest3("JOHNDOE@DOMAIL.INFO"s);
      ltest3("J.O.H.N_D.O.E@DOMAIN.INFO"s);
      ltest3("ROOT@LOCALHOST"s);
      ltest3("john.doe@domain.com"s);
   }
}