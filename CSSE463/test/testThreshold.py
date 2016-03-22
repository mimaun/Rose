#! /usr/bin/env python
# -*- coding: utf-8 -*-
import cv2
import numpy as np
import sys

# read image
src = cv2.imread(sys.argv[1], 1)

# convert from bgr to hsv
hsv = cv2.cvtColor(src, cv2.COLOR_BGR2HSV)  #BGR→HSVへ変換

# Now you take [H-10, 100,100] and [H+10, 255, 255] as lower bound and upper bound respectively. 
lower_blue = np.array([110, 50, 50])
upper_blue = np.array([60, 255, 255])

# Threshold to get blue
mask = cv2.inRange(hsv, lower_blue, upper_blue)

res = cv2.bitwise_and(src, src, mask=mask)

cv2.imshow('src', src)
cv2.imshow('mask', mask)
cv2.imshow('res', res)

cv2.waitKey(0)
cv2.destroyAllWindows(0)

