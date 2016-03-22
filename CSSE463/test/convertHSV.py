#! /usr/bin/env python
# -*- coding: utf-8 -*-

import cv2
import numpy as np
import sys 

src = cv2.imread(sys.argv[1])
hsv = np.zeros(src.shape, dtype=np.uint8)
hsv = cv2.cvtColor(src, cv2.COLOR_BGR2HSV)  #RGB->HSV
h, s, v = cv2.split(hsv)

# case: GREEN
h_th_low = 144
h_th_up = 150
s_th = 240
v_th = 147

if h_th_low > h_th_up:
    ret, h_img_1 = cv2.threshold(h, h_th_low, 255, cv2.THRESH_BINARY)
    ret, h_img_2 = cv2.threshold(h, h_th_up, 255, cv2.THRESH_BINARY_INV)
    img = cv2.bitwise_or(h_img_1, h_img_2)

else:
    ret, img = cv2.threshold(h, h_th_low, 255, cv2.THRESH_TOZERO)
    ret, img = cv2.threshold(img, h_th_up, 255, cv2.THRESH_TOZERO_INV)
    ret, img = cv2.threshold(img, 0, 255, cv2.THRESH_BINARY)

ret, s_img = cv2.threshold(s, s_th, 255, cv2.THRESH_BINARY)
ret, v_img = cv2.threshold(v, v_th, 255, cv2.THRESH_BINARY)

img = cv2.bitwise_and(img, s_img)
img = cv2.bitwise_and(img, v_img)

cv2.imwrite('output.jpg', img)



# print hsv.shape
# print h.shape

# threshold
# GREEN_MAX = np.array([141, 97, 82], np.uint8)
# GREEN_MIN = np.array([141, 30, 41], np.uint8)
#
# frame_thresed = cv2.inRange(hsv, GREEN_MIN, GREEN_MAX)
# cv2.imwrite('output.jpg', frame_thresed)

# cv2.imshow(frame_thresed)
# cv2.waitKey(0)
# cv2.destroyAllWindows()
