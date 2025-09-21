
#include <stdio.h>

#define alpha 0.01
#define beta 0.9
#define epoch 100

double gradient(double x){
  return 2*x;
}

void func(double initValue_x, double initValue_v)
{
  printf("\n#############################################################################\n");
  printf("#    oldValue(x)    oldValue(v)     gradient   newValue(v)    newValue(x)   #\n");
  printf("#############################################################################\n");

  double oldValue_x  = initValue_x;
  double oldValue_v = initValue_v;
  double gradient_val = gradient(oldValue_x);
  
  double newValue_v = beta * oldValue_v + (1 - beta) * gradient_val;
  double newValue_x = oldValue_x - alpha * newValue_v;
  
  
  for(int i = 1; i <= epoch; i++)
  {
    printf("#      %lf       %lf      %lf      %lf      %lf    #\n", oldValue_x, oldValue_v, gradient_val, newValue_v, newValue_x);

    oldValue_x  = newValue_x;
    oldValue_v = newValue_v;
    gradient_val = gradient(oldValue_x);

    newValue_v = beta * oldValue_v + (1 - beta) * gradient_val;
    newValue_x = oldValue_x - alpha * newValue_v;
  }
  printf("\n#############################################################################\n");
}

int main()
{
  double value_x;
  double value_v;

  printf("Enter Initial value of x: ");
  scanf("%lf", &value_x);

  printf("Enter Initial value of v: ");
  scanf("%lf", &value_v);

  printf("Gradient Descent with Momentum of function x^2 with initial values of x = %lf and v = %lf", value_x, value_v);
  func(value_x, value_v);
  
  return 0;
}
