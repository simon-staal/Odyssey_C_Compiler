int f(int x)
{
  int i;
  for(i = 32; i > 0; i /= 2){
    x--;
    if(i == 8 || i == 16){
      continue;
      return 2;
    }
    x += i+1;
  }
  return x;
}
