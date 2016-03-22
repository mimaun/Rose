# -*- coding: utf-8 -*-

import pytesseract 
from PIL import Image
import sys

img = Image.open(sys.argv[1])
# print img
message = pytesseract.image_to_string(img)
print message


