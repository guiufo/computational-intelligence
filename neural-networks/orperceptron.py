#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
# Copyright © 2017 guiufo <guiufo@gmail.com>
# Distributed under terms of the MIT license.

"""
OR perceptron implementation
"""
from random import uniform

def step(X, t):
    if X > t:
        return 1
    return 0

def train(x1, x2, w1, w2, threshold, learningRate):
    X = (x1*w1)+(x2*w2)
    y = step(X, threshold)
    if not(y == int(x1 or x2)):
        wrong = True
        w1 = w1 + (learningRate * x1 * 1)
        w2 = w2 + (learningRate * x2 * 1)
    else:
        wrong = False
    return w1, w2, wrong

w1 = uniform(-1.0, 1.0)
w2 = uniform(-1.0, 1.0)
finished = False
epoch = 1

while not finished:
    threshold = 0
    learningRate = 0.2
    print "Epoch: " + str(epoch)
    epoch += 1

    for i in range(2):
        x1 = i
        for j in range(2):
            x2 = j
            w1, w2, wrong = train(x1, x2, w1, w2, threshold, learningRate)
            if wrong:
                error = True
            else:
                error = False

    if not error:
        print "weight1: " + str(w1)
        print "weight2: " + str(w2)
        finished = True
