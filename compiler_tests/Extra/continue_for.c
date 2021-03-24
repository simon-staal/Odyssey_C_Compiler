int f(int x)
{
  int i;
  for(i = 32; i > 0; i = i/2){
    x -= 1;
    if(i == 8 || i == 16){
      continue;
      return 2;
    }
    x += i+1;
  }
  return x;
}
