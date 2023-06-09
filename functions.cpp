double relu(double x){
    if(x > 0.5) return (x-0.5);
    else return 0.0;
}

double relu_d(double x){
    if(x > 0.5) return 1.0;
    else return 0.0;
}
