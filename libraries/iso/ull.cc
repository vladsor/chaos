#include <system/system.h>

class Ull 
{
  public:
    void Run (void);
};

void Ull::Run (void)
{
  /* foo */
  system_call_debug_print_simple ("Foo!");
}

int main (void)
{
  Ull *ull;
  
  ull = new Ull;
  ull->Run ();
  delete ull;
  return 1;
}
