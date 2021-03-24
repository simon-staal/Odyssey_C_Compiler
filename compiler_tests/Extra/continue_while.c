int f(int x, int y)
{
  while(y < x){
    ++y;
    if(y+5 < x){
      continue;
      return 4;
    }
    --x;
  }
  return x;
}
