#include <iostream>
#include <fstream>
using namespace std;
class Polynomial;

class Term {
  friend Polynomial;

private:
  float coef;
  int exp;
};

class Polynomial {
public:
  Polynomial(int d);

  Polynomial Add(Polynomial poly);

  Polynomial Mult(Polynomial poly);

  float Eval(float f);
  void print() {
    for (int i = degree; i >= 0; i--) std::cout << i << "=" << coef[i] << "\n";
  }
private:
  int degree;
  int *coef;
};

Polynomial::Polynomial(int d) {
  degree = d;
  coef = new int[degree + 1];
  for (int i = degree; i >= 0; i--) std::cin >> coef[i];
}
Polynomial Polynomial::Add(Polynomial a) {
  int deg = std::max(a.degree,this->degree);
  Polynomial ret(deg);
  for (int i = deg; i >= 0; i--) ret[i] = coef[i] + a.coef[i];
  return ret;
}
int main() {
  int greatestPower1, greatestPower2;
    int coefficient1[51], coefficient2[51];
    Polynomial ans;

    cin>>greatestPower1;
    for(int i = greatestPower1 ; i >= 0; i--)
    {
        cin>>coefficient1[i];
    }
    cin>>greatestPower2;
    for(int i = greatestPower2 ; i >= 0 ; i--)
    {
        cin>>coefficient2[i];
    }
    Polynomial a(greatestPower1, coefficient1), b(greatestPower2, coefficient2) ;
}