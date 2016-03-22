import numpy as np
import cv2
from PIL import Image
import pytesseract
import sys
from matplotlib import pyplot as plt

if __name__ == '__main__':
    #### Initial Tesseract
    filename = 'traff2.jpg'
    message = pytesseract.image_to_string(Image.open(filename))
    print "=====Colored Image, tesseract output======"
    print message
    
    #### read image
    src = cv2.imread(filename, cv2.IMREAD_COLOR)
    blur = np.ones((src.shape[0],src.shape[1]), np.uint8)
    cv2.medianBlur(src, 3, src)
    cv2.imshow('blurred', src)
    
    dst = cv2.cvtColor(src, cv2.COLOR_RGB2HSV) 
    

    
    ## Use this to find coordinates #####
    plt.imshow(dst, cmap = 'gray', interpolation = 'bicubic')
    plt.xticks([]), plt.yticks([])  # to hide tick values on X and Y axis
    plt.show()    

    #### Extract green color from HSV

    
    # This is how you look for HSV values
    print dst[200, 400]
    print dst[350, 580]
    print dst[358, 284]
    
    print dst[245, 600]
    print dst[254, 260]
    print dst[260, 397]
    print dst[362, 422]

    lower_green = np.array([30, 170, 67])
    upper_green = np.array([50, 255, 160])
    green_mask = cv2.inRange(dst, lower_green, upper_green)
    res = cv2.bitwise_and(src, src, mask= green_mask)
  
    
    # cv2.imshow('src',src)
    cv2.imshow('mask', green_mask)
    # cv2.imshow('res', res)
    # cv2.waitKey(0)
    # cv2.destroyAllWindows()

    
    
    
    #### Morphology
    
    ## FUTURE WORK TODO: scale the kernel by size of traffic sign
    cv2.findContours
    
    
    cv2.imwrite('mask.jpg', green_mask)

    message = pytesseract.image_to_string(Image.open('mask.jpg'))
    print "=====Before morphology, tesseract output======"
    print message
    
    kernel = np.ones((5,5),np.uint8)
    morph = cv2.dilate(green_mask, kernel, iterations = 1)
    kernel = np.ones((3,3),np.uint8)
    morph = cv2.erode(morph, kernel, iterations = 1)
    cv2.imshow('eraer', morph)
        
    #### Filter
    
    ## BLUR : TODO, maybe move this before masking.
    # blur = np.ones((dst.shape[0],dst.shape[1]), np.uint8)
    # cv2.medianBlur(morph, 5, blur)
    # cv2.imshow('blurred', blur)
    
    #### Extract traffic sign shape
    
    
    #### run tesseract on traffic sign

    cv2.imwrite('morphed_image.jpg', morph)
    message = pytesseract.image_to_string(Image.open('morphed_image.jpg'))
    print "=====After morphology, tesseract output======"
    print message

    
    cv2.waitKey(0)
    cv2.destroyAllWindows()    
    
