module vcore;
module vmem;

sub factorial(n) {
    if n <= 1 {
        return 1;
    }
    return n * factorial(n - 1);
}

log("Initial Memory:");
log(vmem.usage());

# high recursion depth
result = factorial(50); 

log("Factorial(50) Result:");
log(result);

log("Memory after recursion:");
log(vmem.usage());