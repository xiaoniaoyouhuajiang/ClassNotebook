from pysnooper_click_able import snoop


def f1(x):
    if x == 1:
        a = 2
    else:
        a = 3


def f2(x):
    if x == 7:
        b = 8
        for i in range(1000):
            b += i
    else:
        b = 9


@snoop(depth=9)
def f3(x, test=True):
    if test:
        f1(x)
    else:
        f2(x)


f3(5, False)