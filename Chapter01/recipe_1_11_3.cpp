template <int const& Size>
class test {};

static int Size1 = 10;

namespace
{
   int Size2 = 10;
}

//test<Size1> t1; // error, Size1 has internal linkage
test<Size2> t2;
