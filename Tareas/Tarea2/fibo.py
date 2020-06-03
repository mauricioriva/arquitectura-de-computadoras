import time

def fibo(n):
    fn = f1 = f2 = 1
    for x in range(2, n):
        fn = f1 + f2
        f2, f1 = f1, fn
    return fn

def main():
    start_time = 0
    num = [4000000]
    for x in num:
        start_time = time.time()
        n = fibo(int(x))
        s = time.time() - start_time
        print("Tardó \t%s\t segundos en calcular fibo(%s)" %(s, x))
        if (s > 1000):
            return
        num = num*10

main()
