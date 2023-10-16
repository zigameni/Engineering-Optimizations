#include <cstdio>   // for printf
#include <iostream> // for cout
#include <time.h> // To calculate time
using std::cout;
using std::endl;

bool opt_func(double a, double b, double c, double d){
    return ((a + b + c + d) == 777 && (a * b * c * d) == 777000000);
}

int main(){
    time_t startTime;
    time(&startTime);

    unsigned long int count = 0; // Counting the number of calls
    int sum = 777; // 7.77*100, faster to work with ints
    int a, b, c, d;
    for (a = 1; a < 777; a++){
        for (b = 1; b < 777-a; b++){
            // if((a+b)>sum)break;
            for (c = 1; c < 777-b; c++){
                // if((a+b+c)>sum)break;
                for (d = 1; d < 777-c; d++){
                    count++;
                    if (opt_func(a, b, c, d)){

                        time_t endTime;
                        time(&endTime);

                        printf("Solution found:\n");
                        printf("%.2f, %.2f, %.2f, %.2f\n", a / 100.0, b / 100.0, c / 100.0, d / 100.0);

                        cout<<"Number of calls: "<<count<<endl;

                        cout<<"Time of execution: "<<endTime - startTime<<" seconds"<<endl;

                        return 0;
                    }
                }
            }
        }
    }

    time_t endTime;
    time(&endTime);

    cout << "\nNo soulution fund" << endl;

    cout<<"Number of calls: "<<count<<endl;

    cout<<"Time of execution: "<<endTime - startTime<<" seconds"<<endl;

    return 0;
}