
#include <stdio.h>

#define lr 0.01
#define MAX_ITER 100
#define FUNC x*x

double gradient(double x){
  return 2*x;
}

void GD(double initValue)
{
  printf("\n##################################################\n");
  printf("#    OldValue  #    Gradient    #     NewValue   #\n");
  printf("##################################################\n");

  double oldValue = initValue;
  double gradient_val = gradient(oldValue);
  double newValue = oldValue - lr * gradient_val;

  for(int i = 0; i < MAX_ITER; i++)
  {
    printf("#    %lf  #    %lf    #    %lf    #\n", oldValue, gradient_val, newValue);
    
    oldValue = newValue;
    gradient_val  = gradient(newValue);
    newValue = oldValue - lr * gradient_val;
  }
  printf("##################################################\n");
}
int main()
{
  double value;
  printf("Enter a value: ");
  scanf("%lf", &value);
  
  printf("Gradient Descent on the function x^2 with starting value %lf\n", value);
  GD(value);

  return 0;
}
