module geometry:details;

import std.core;

std::pair<int, int> split(const char* ptr, std::size_t size)
{
  int x = 0, y = 0;
  while (*ptr != ',' && *ptr != ' ') 
    x = x * 10 + (*ptr++ - '0');
  while (*ptr == ',' || *ptr == ' ') ptr++;
  while (*ptr != 0) 
    y = y * 10 + (*ptr++ - '0');
  return { x, y };    
}