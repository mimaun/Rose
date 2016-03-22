#! /usr/bin/env python
# -*- coding; utf-8 -*-

import numpy as np
import cv2
from PIL import Image
import pytesseract
import sys
from matplotlib import pyplot as plt
import math

def get_angle(p0, p1=np.array([0,0]), p2=None):
    ''' compute angle (in degrees) for p0p1p2 corner
    Inputs:
        p0,p1,p2 - points in the form of [x,y]
    '''
    if p2 is None:
        p2 = p1 + np.array([1, 0])
    v0 = np.array(p0) - np.array(p1)
    v1 = np.array(p2) - np.array(p1)

    angle = np.math.atan2(np.linalg.det([v0,v1]),np.dot(v0,v1))
    return np.degrees(angle)

if __name__ == '__main__':
    #### Initial Tesseract
    filename = 'traff3.jpg'
    src = cv2.imread(filename, cv2.IMREAD_COLOR) 
    gray = cv2.cvtColor(src, cv2.COLOR_RGB2GRAY)
    gray = cv2.bilateralFilter(gray, 9, 19,50 )
    # cv2.imshow('gray',gray) 
    edges = cv2.Canny(gray, 170, 200);
    # cv2.imshow('edge', edges);

    dst = cv2.cvtColor(src, cv2.COLOR_RGB2HSV) 


    lower_green = np.array([30, 170, 67])
    upper_green = np.array([50, 255, 160])
    green_mask = cv2.inRange(dst, lower_green, upper_green)
    res = cv2.bitwise_and(src, src, mask= green_mask)
    kernel = np.ones((5,5),np.uint8)
    morph = cv2.dilate(green_mask, kernel, iterations = 1)
    kernel = np.ones((3,3),np.uint8)
    morph = cv2.erode(morph, kernel, iterations = 1)

    cnts, hie = cv2.findContours(edges.copy(), cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    cnts = sorted(cnts, key = cv2.contourArea, reverse = True)[:10]
    screenCnt = None 
    cv2.drawContours(morph, cnts, -1, (0,0,255),3)
    cv2.imshow('img with contours', morph)

    cv2.waitKey(0)
    cv2.destroyAllWindows()


