import functools as ft
import time


def timeit(func=None, *, repeat=None):
    if func is None:
        return ft.partial(timeit, repeat=repeat)

    repeat = repeat if repeat else 10000

    @ft.wraps(func)
    def wrapped(*args, **kw):
        tstart = time.time()
        for _ in range(repeat):
            func(*args, **kw)
        elapsed_ms = (time.time() - tstart) * 1000
        print(f'"{func.__name__}" took {elapsed_ms:.3f} ms to execute\
              {f" {repeat} times" if repeat > 1 else ""}\n')
        return func(*args, **kw)
    return wrapped
