int f(int x, int y)
{
  while(y < x){
    y = y + 1;
    if(y+5 < x){
      continue;
      return 4;
    }
    x -= 1;
  }
  return x;
}
