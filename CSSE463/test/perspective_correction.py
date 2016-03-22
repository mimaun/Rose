#! /usr/bin/env python
# -*- coding; utf-8 -*-

import numpy as np
import cv2
from PIL import Image
import pytesseract
import sys
from matplotlib import pyplot as plt
import math

if __name__ == '__main__':
    #### Initial Tesseract
    filename = 'traff3.jpg'
    img = cv2.imread(filename, cv2.IMREAD_COLOR)
    
    ## Perspective Correction
    # upper left
    Q1 = np.array([int(192), int(136)])
    # upper right
    Q2 = np.array([int(607), int(115)])
    # lower right
    Q3 = np.array([int(658), int(382)])
    # lower left
    Q4 = np.array([int(230), int(408)])

    ratio = 1.6
    newRecHeihgt = int(math.sqrt((Q3[0]-Q2[0])*(Q3[0]-Q2[0]) + (Q3[1]-Q2[1])*(Q3[1]-Q2[1])))
    newRecWidth = int(ratio * newRecHeihgt)

    R1 = Q1
    R2 = np.array([R1[0]+newRecWidth, R1[1]])
    R3 = np.array([R1[0]+newRecWidth, R1[1]+newRecHeihgt])
    R4 = np.array([R1[0], R1[1]+newRecHeihgt])

    rec = cv2.imread(filename, cv2.IMREAD_COLOR)
    cv2.rectangle(rec, (R1[0],R1[1]), (R3[0],R3[1]), (0, 0, 255), 3)
    cv2.imshow('rectangle', rec)

    src = np.array([Q1,Q2,Q3,Q4], np.float32)
    dst = np.array([R1,R2,R3,R4], np.float32)
    print src
    print dst
    
    transmtx = cv2.getPerspectiveTransform(src,dst)
    offsetSize = int(150)
    # transformed = np.zeros((newRecHeihgt+offsetSize, newRecHeihgt+offsetSize))
    warp = cv2.warpPerspective(img, transmtx, (newRecWidth+offsetSize, newRecHeihgt+offsetSize))
    cv2.imshow('warp', warp) 

    cv2.imwrite('warp.jpg', warp)

    cv2.waitKey(0)
    cv2.destroyAllWindows()    
    
