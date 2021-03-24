int f()
{
  int i;
  int x = 20;
  for(i = 0; i < 10; i=i+1){
    if(i == 6){
      break;
    }
    x += i;
  }
  return x;
}
