# -*- coding: utf-8 -*-

from turtle import *
import time
import turtle as t


def gotopos(x, y):
    up()
    goto(x, y)
    down()
    ht()


def author():
    pensize(2)
    gotopos(610, -315)
    lt(-90)
    fd(80)
    pensize(1)
    lt(-270)


def apply_rules(path, rules):
    L = [_ for _ in path]
    for i in range(len(L)):
        symbol = L[i]
        if symbol == 'F':
            L[i] = rules[symbol]
        if symbol == 'X':
            L[i] = rules[symbol]
    path = ''.join(L)
    return path


def draw_path(path):
    posList, angleList = [], []
    for symbol in path:
        if symbol == 'F':
            t.forward(length)
        elif symbol == '+':
            t.left(angle)
        elif symbol == '-':
            t.rt(angle)
        elif symbol == '[':
            posList.append(t.pos())
            angleList.append(t.heading())
        elif symbol == 'a':
            t.pensize(3)
            t.color("#867b68")
        elif symbol == 'b':
            t.pensize(2)
            t.color("#867b68")
        elif symbol == 'c':
            t.pensize(2)
            t.color("#867b68")
        elif symbol == ']':
            t.up()
            t.home()
            t.goto(posList.pop())
            t.left(angleList.pop())
            t.down()


def writez(x, y, str_, size=56, font="华文行楷"):
    gotopos(x, y)
    write(str_, font=(font, size))


setup(1280, 800)
speed(5)
bgcolor("#9c917f")
color("#afa697")
begin_fill()
gotopos(0, -400)
circle(400)
end_fill()
author()
color("#7d776d")
s = "愿天化作比翼鸟"
s2 = "在地愿为连理枝"
for i in range(len(s)):
    writez(560, 350 - i * 50, s[i], 36)
for i in range(len(s2)):
    writez(460, 350 - i * 50, s2[i], 36)
color("#888475")
writez(-50, 100, "昕")
writez(-50, 40, "和")
writez(-160, 0, "子", 96)
writez(-50, 0, "刘", 176)
writez(33, -30, "润", 62)
writez(-18, -95, "喆", 78)
writez(-213, -210, "杨", 196)

gotopos(249, -26)
color("#867b68")
speed(0)
gotopos(-650, -100)
length = 6
path = 'F'
angle = 27
rules = {
    'F': 'aFF[b-F++F][c+F--F]c++F--F',
    'X': 'aFF+[b+F]+[c-F]'
}

for _ in range(4):
    path = apply_rules(path, rules)
draw_path(path)
gotopos(570, -330)
done()