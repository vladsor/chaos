
int main (void)
{
    int i = 0;
    
    try
    {
      i++;
      if (i==1)
      {
      throw 0x0ABC;
      }
    }
    catch (...)
    {
    }
    
    return 0;
}
