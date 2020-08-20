#pragma once

#ifdef HAS_USING_ENUMS
#include <string_view>
#endif

namespace recipe_1_06
{   
   /*
   enum Status { Unknown, Created, Connected };

   enum Codes 
   { 
      OK, 
      Failure, 
      // Unknown redefinition
   };
   */

   /*
   namespace Status
   {
      enum Status { Unknown, Created, Connected };
   }

   namespace Codes
   {
      enum Codes { OK, Failure, Unknown };
   }
   */

   enum class Status { Unknown, Created, Connected };

   enum class Codes { OK, Failure, Unknown };


   enum class Codes2 : unsigned int;

   void print_code(Codes2 const code) {}

   enum class Codes2 : unsigned int
   {
      OK = 0,
      Failure = 1,
      Unknown = 0xFFFF0000U
   };

#ifdef HAS_USING_ENUMS
   struct foo
   {
      enum class Status { Unknown, Created, Connected };

      using enum Status;
   };

   void process(Status const s)
   {
      switch (s)
      {
         using enum Status;
         case Unknown:   /*...*/ break;
         case Created:   /*...*/ break;
         case Connected: /*...*/ break;
      }
   }

   std::string_view to_string(Status const s)
   {
      switch (s)
      {
         using enum Status;
         case Unknown:   return "Unknown";
         case Created:   return "Created";
         case Connected: return "Connected";
      }
   }
#endif

   void execute()
   {
      Codes code = Codes::Unknown;

      Codes c1 = Codes::OK;					      // OK
      //int c2 = Codes::Failure;   				   // error
      int c3 = static_cast<int>(Codes::Failure);// OK

      {
#ifdef HAS_USING_ENUMS
         using Status::Unknown;
         Status s = Unknown;

         foo::Status s = foo::Created; // instead of foo::Status::Created
#endif
      }
   }
}