int global[5];

int f(int x)
{
  global[3] = x+1;
  return global[3];
}
