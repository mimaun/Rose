#! /usr/bin/env python
# -*- coding: utf-8 -*-
import cv2
import numpy as np
import sys

# read image
src = cv2.imread(sys.argv[1], 1)

# make matrix for output
dst = np.zeros(src.shape, dtype=np.uint8)

# convert from rgb to hsv
dst = cv2.cvtColor(src, cv2.COLOR_BGR2HSV)  #BGR→HSVへ変換

# print dst.shape

ij_index = [-1, -1] 
max_h = -1
# loop for each pixels
for i in range (dst.shape[0]):
    for j in range (dst.shape[1]):

        # find red pixel
        # if (dst[i,j][0] > 130 and dst[i,j][0] < 160 and dst[i,j][1] > 200 and dst[i,j][2] > 110 and dst[i,j][2] < 160):
        if (dst[i,j][0] < 160 and dst[i,j][1] > 200 and dst[i,j][2] > 110 and dst[i,j][2] < 160):
            max_h = dst[i,j][0]
            # BGR
            # Green pixel -> white
            cv2.circle(src,(j, i),5,(255,255,255),1)

        # Other color -> black
        else:
            cv2.circle(src,(j, i),5,(0,0,0),1)

print max_h

cv2.imshow('result',src)
cv2.imwrite("output.png", src); 
cv2.waitKey(0)
cv2.destroyAllWindows()

