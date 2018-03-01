#include <stdio.h>
#include <stdlib.h>

int rArray[100];
int rLen;
int qArray[100];

int linearCombination(int gcd); 
int euclidean(int a, int b);

int main(int argc, char* argv[]) {

    // a cannot equals to b, a must be greater than b to avoid repeating the last linear combo
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);

    // positive int only for now
    if(a < 0 || b < 0) return 0;

    int gcd = euclidean(a, b);
    
    if(gcd == 0) {
     
        return 0;
    }

    if(gcd == a || gcd == b) {
    
        return 0;
    }

    linearCombination(gcd);   
    return 0;
}

int linearCombination(int gcd) {
    
    printf("\n------------- linear combination -----------\n\n");
    // since rArray[rLen - 3] = 0, gcd =  rArray[rLen - 4] 
    int s = 1;
    int k = rLen - 4;
    int t = qArray[k--];

    int i = rLen - 2;
    int m = i - 2, n = i - 1;
    while(m>=0 && n>=0){

        printf("%d =%d(%d)-%d(%d)\n",gcd, s, rArray[m], t, rArray[n]);
        n -= 2;
        s = s + qArray[k--] * t;
       if(n>0) {
            printf("%d =%d(%d)-%d(%d)\n",gcd, s, rArray[m], t, rArray[n]);
            m -= 2;
            t = t + qArray[k--] * s;
       }
    } 
    printf("\n-------------------- end -------------------\n");
    return 0;
}

int euclidean(int a, int b) {
    int abAreSpecialValues = 0; 
    if(a == 0 && b == 0) abAreSpecialValues = 1;

    int _a = a;
    int _b = b;
    int gcd = 0; 

    if(a < b) {
        int temp = a;
        a = b;
        b = temp;
    }
    // now a >= b;
    if(b == 0) {
        gcd = a;
        abAreSpecialValues = 1;
    } else if(a == 0 || a % b == 0) {

        gcd = b;
        abAreSpecialValues = 1;
        
    }
    printf("-------------------- gcd -------------------\n\n");

    if( !abAreSpecialValues ) {
        int r = a % b;
        int q = a / b;

        printf("%d = %d (%d) + %d\n",a,q,b,r);

        int i = 0;
        qArray[i++] = q;
        rArray[0] = a;
        rArray[1] = b;
        rArray[2] = r;

        while(r != 0) {
            a = b;     
            b = r;
            if(b % r == 0) {
                gcd = r;
            }
            r = a % b;
            q = a / b; 
            qArray[i] = q;
            rArray[i + 2] = r;
            i++;       
            printf("%d = %d (%d) + %d\n",a,q,b,r);
        }
        rLen = 2 + i; // length = last index + 1 = i - 1 + 1 = i; 
    }
    printf("\ngcd(%d , %d) = %d\n", _a, _b, gcd);
    return gcd;
}
