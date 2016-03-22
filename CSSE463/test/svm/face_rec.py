#! /usr/bin/env python
# -*- coding: utf-8 -*-

import numpy as np
import cv2
import sys

face_path = '/usr/local/Cellar/opencv/2.4.12_2/share/OpenCV/haarcascades/haarcascade_frontalface_default.xml'
eye_path = '/usr/local/Cellar/opencv/2.4.12_2/share/OpenCV/haarcascades/haarcascade_eye.xml'
face_cascade = cv2.CascadeClassifier(face_path)
eye_cascade = cv2.CascadeClassifier(eye_path)

img = cv2.imread(sys.argv[1])
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

# if it finds face, cascade returns Rect(x,y,w,h)
faces = face_cascade.detectMultiScale(gray, 1.3, 5)
for(x, y, w, h) in faces:
    # rectangle(img, pt1, pt2, color[, thickness[, lineType[, shift]]])
    # pt2 – Vertex of the rectangle opposite to pt1 .
    cv2.rectangle(img, (x, y), (x+w, y+h), (255, 0, 0), 2)

    # ROI about faec (ROI : Ragnge of Interest)
    # roi_gray = gray[y:y+h, x:x+w]
    # eyes = eye_cascade.detectMultiScale(roi_gray)
    # for(ex, ey, ew, eh) in eyes:
    #     cv2.rectangle(img, (ex, ey), (ex+ew, ey+eh), (0, 255, 0), 2)

cv2.imshow('img', img)
cv2.waitKey(0)
cv2.destroyAllWindows()

