import sys
from subprocess import Popen, PIPE

CMD = './ksticks.filler'
FILE = 'seg_test.txt'


def main():
    sys.stderr.write("start!\n")
    p = Popen(CMD, stdin=PIPE, stdout=sys.stdout)
    with open(FILE, 'wt') as f:
        for line in sys.stdin:
            f.write(line)
            f.flush()
            p.stdin.write(line.encode())
            p.stdin.flush()
    p.stdin.close()


if __name__ == '__main__':
    main()
