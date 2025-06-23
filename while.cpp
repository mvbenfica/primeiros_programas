#include <iostream>

using namespace std;

int main()
{
  int ind = 1;
  int controle = 0;
  int num;
  int menor;
  while (ind <= 5){
    scanf("%d", &num );
    controle++;
    if (controle == 1 && num % 2 == 0)
        menor=num;
    else
        if (num < menor)
          menor=num;
    ind++;
  }
  return 0;
}


