int f()
{
  int i = 5;
  int x = 4;
  while(i != 2){
    if(i == 3){
      break;
      return 2;
    }
    x *= i;
    --i;
  }
  return x;
}
