import cv2
import numpy as np 
import sys
import pytesseract
from PIL import Image
from matplotlib import pyplot as plt



filename = 'traff4.jpg';

img = cv2.imread(filename);
gray = cv2.cvtColor(img, cv2.COLOR_RGB2GRAY)
gray = cv2.bilateralFilter(gray, 9, 19,50 )
cv2.imshow('gray',gray)


edges = cv2.Canny(gray, 170, 200);
cv2.imshow('edge', edges);

im2, cnts, hie = cv2.findContours(edges.copy(), cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
cnts = sorted(cnts, key = cv2.contourArea, reverse = True)[:10]
screenCnt = None

for c in cnts:
	# approximate the contour
	peri = cv2.arcLength(c, True)
	approx = cv2.approxPolyDP(c, 0.02 * peri, True)
	
	if len(approx) == 4:
		screenCnt = approx
		break


cv2.drawContours(img, [screenCnt], -1, (0, 255, 0), 3)
cv2.imshow("traffic", img)


cv2.waitKey(0)
cv2.destroyAllWindows()
