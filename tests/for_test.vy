z = through it::1..30 -> filter {
    it % 2 == 0;
};

log(z);