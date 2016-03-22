#! /usr/bin/env python
# -*- coding: utf-8 -*-

import cv2
import numpy as np
import sys 

src = cv2.imread(sys.argv[1])
dst = np.zeros(src.shape, dtype=np.uint8)
dst = cv2.cvtColor(src, cv2.COLOR_BGR2HSV)  #RGB->HSV
h, s, v = cv2.split(dst)

print dst.shape

ij_index = [-1, -1]
max_h = -1

mrgb = np.zeros((256, 256, 3), dtype=np.uint8)
Vsize = 256
Hsize = 360
max1 = 1.0
max2 = 1.0

def reScale(val, max_val, max_grade):
    return int(val * max_grade / max_val)

for i in range(Vsize):
    for j in range(Hsize):
        
        # H
        index1 = float(dst[i][j][0]) / float(255)
        # S
        index2 = float(dst[i][j][1]) / float(255)
        n = reScale(index1, max1, Hsize - 1)
        m = reScale(index2, max2, Vsize - 1)

        # print 'n: ' + str(n)
        # print 'm: ' + str(m)

        # the order in B, G, R
        # x axis -> S, y axis -> H
        mrgb[m][n][0] = int(src[i][j][0])
        mrgb[m][n][1] = int(src[i][j][1])
        mrgb[m][n][2] = int(src[i][j][2])

cv2.circle(mrgb, (200, 100), 5, (255, 0, 0), 1)
print((200.0 / (Hsize - 1)) * 255)
print((100.0 / (Vsize - 1)) * 255)

cv2.imshow('result', mrgb)
cv2.imwrite('output.jpg', mrgb)
cv2.waitKey(0)
