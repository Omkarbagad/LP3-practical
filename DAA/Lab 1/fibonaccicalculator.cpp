#include <iostream>
#include <vector>

class FibonacciCalculator {
public:
    static int fibonacci(int n) {
        if (n <= 1) return n;
        return fibonacci(n - 1) + fibonacci(n - 2);
    }

    static int fibonacciIteration(int n) {
        std::vector<int> fib(n + 1);
        fib[0] = 0;
        fib[1] = 1;
        for (int i = 2; i <= n; i++) {
            fib[i] = fib[i - 1] + fib[i - 2];
        }
        return fib[n];
    }

    static int stepCountRecursion(int n) {
        if (n <= 1) return 1;
        return stepCountRecursion(n - 1) + stepCountRecursion(n - 2);
    }

    static int stepCountIteration(int n) {
        int count = 0;
        std::vector<int> fib(n + 1);
        fib[0] = 0;
        fib[1] = 1;
        for (int i = 2; i <= n; i++) {
            fib[i] = fib[i - 1] + fib[i - 2];
            count++;
        }
        return count;
    }
};

int main() {
    int n;
    std::cout << "Enter the number of Fibonacci numbers to calculate: ";
    std::cin >> n;

    int stepsRecursion = FibonacciCalculator::stepCountRecursion(n);
    int stepsIteration = FibonacciCalculator::stepCountIteration(n);
    
    std::cout << "Fibonacci Recursion: " << FibonacciCalculator::fibonacci(n) << std::endl;
    std::cout << "Fibonacci Recursion Steps: " << stepsRecursion << std::endl;
    std::cout << "Fibonacci Iteration: " << FibonacciCalculator::fibonacciIteration(n) << std::endl;
    std::cout << "Fibonacci Iteration Steps: " << stepsIteration << std::endl;

    return 0;
}
