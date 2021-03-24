int f()
{
  int i;
  int x = 20;
  for(i = 0; i < 10; i++){
    if(i == 6){
      break;
    }
    x += i;
  }
  return x;
}
