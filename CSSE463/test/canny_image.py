# -*- coding: utf-8 -*-

import cv2
import numpy as np
import sys

cv2.namedWindow('edge')
img = cv2.imread(sys.argv[1])
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
thrs1 = 300
thrs2 = 100

edge = cv2.Canny(gray, thrs1, thrs2, apertureSize=5)
edge = cv2.Canny(gray, thrs1, thrs2)
cv2.imshow('original', img)
cv2.imshow('gray', gray)
cv2.imshow('edge', edge)

cv2.waitKey(0)
cv2.destroyAllWindows()
