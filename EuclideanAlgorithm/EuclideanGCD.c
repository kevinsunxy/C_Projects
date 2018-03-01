#include <stdio.h>
#include <stdlib.h>

int qArray[1025];
int backTrack(int x, int y);
void linearCombo(int a, int b, int gcd);
int euclidean(int a, int b);

int main(int argc, char* argv[]) {

    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    int gcd =  euclidean(a, b);
    printf("gcd(%d, %d) = %d\n", a, b, gcd);
    linearCombo(a, b, gcd); 
    
    return 0;
}
// fastest gcd
int gcd(int a, int b) {
    int r = a % b;
    int temp = 0;

    while(b % r != 0) {
        temp = b;
        b = r;
        r = temp % b;
    }
    return r;
}

// create array of quotient at the same time for linear combo or inverse;
int euclidean(int a, int b) {
    int r = a % b;
    int q = a / b;
    int gcd = 0;   
    int i = 1;
    qArray[i++] = q;
    while(r != 0) {
        a = b;
        b = r;

        if(b % r ==0 ) {
            gcd = r;
        }

        r = a % b;
        q = a / b;
        qArray[i++] = q;

    }

    qArray[0] = i -2;
    return gcd;
}

// need array of quatients to do the computation
void linearCombo(int a, int b, int gcd) {
  
    int nbSteps = qArray[0];
    int s_1 = 1;
    int s_2 = 0 - qArray[2]; // s_2 = -q_2

    int s_n =  nbSteps >= 3 ? backTrack(s_1, s_2) : (nbSteps == 1 ? s_1 : s_2) ;

    int t_1 = 0 - qArray[1]; // t_1 = -q
    int t_2 = 1 - (qArray[2] * t_1); // t_2 = 1 - q_2(t_1) 

    int t_n =  nbSteps >= 3 ? backTrack(t_1, t_2) : (nbSteps == 1 ? t_1 : t_2) ;
/*
    int s_n, t_n;
    switch (nbSteps) {
    
        case 1:
            s_n = s_1;
            t_n = t_1;
            break;
        case 2:    
            s_n = s_2;
            t_n = t_2;
            break;
        default:
            s_n = backTrack(s_1, s_2);    
            t_n = backTrack(t_1, t_2);    
            break;
    }
*/
    printf("%d = %d(%d) + %d(%d)\n", gcd, s_n, a, t_n, b);
}

int backTrack(int x, int y) {
    int nbSteps = qArray[0];
    int z;
    for(int i = 3; i < nbSteps + 3; i++) {
        z = x - qArray[i] * y;
        x = y;
        y = z;
    }
 
    return z;   
}
