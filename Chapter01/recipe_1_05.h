#pragma once

namespace recipe_1_05
{
   // size = 1, alignment = 1
   struct foo1
   {
      char a;
   };

   // size = 2, alignment = 1
   struct foo2
   {
      char a;
      char b;
   };

   // size = 8, alignment = 4
   struct foo3
   {
      char a;
      int  b;
   };

   struct foo3_
   {
      char a;        // 1 byte
      char _pad0[3]; // 3 bytes padding to put b on a 4-byte boundary
      int  b;        // 4 bytes
   };

   struct foo4
   {
      int a;
      char b;
      float c;
      double d;
      bool e;
   };

   struct foo4_
   {
      int a;         // 4 bytes
      char b;        // 1 byte
      char _pad0[3]; // 3 bytes padding to put c on a 8-byte boundary 
      float c;       // 4 bytes
      char _pad1[4]; // 4 bytes padding to put d on a 8-byte boundary
      double d;      // 8 bytes
      bool e;        // 1 byte
      char _pad2[7]; // 7 bytes padding to make sizeof struct multiple of 8
   };



   void execute()
   {
      {
         struct alignas(4) foo
         {
            char a;
            char b;
         };

         struct foo_
         {
            char a;
            char b;
            char _pad0[2];
         };
      }

      {
         struct alignas(4) foo
         {
            alignas(2) char a;
            alignas(8) int  b;
         };

         struct foo_
         {
            char a;
            char _pad0[7];
            int b;
            char _pad1[4];
         };

         {
            alignas(8)   int a;
            alignas(256) long b[4];

            printf("%p\n", &a); // eg. 0000006C0D9EF908
            printf("%p\n", &b); // eg. 0000006C0D9EFA00
         }
      }
   }
}