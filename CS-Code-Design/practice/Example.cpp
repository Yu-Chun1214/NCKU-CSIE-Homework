#include "bignum.hpp"


int main(int argc, char * argv[]){
    Bignum n1(argv[1]);
    Bignum n2(argv[3]);
    Bignum n3 = n1 + n2;
    cout<<n3<<endl;
}