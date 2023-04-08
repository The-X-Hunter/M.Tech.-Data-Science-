import cv2
import time

image = cv2.imread('Input.png')
cv2.imshow('image', image)
cv2.waitKey(1)
time.sleep(3)
cv2.destroyAllWindows()
cv2.imwrite('Output.png', image)
image = cv2.putText(image, 'Julfikaraehmad', (500, 500), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 0, 0), 2)
cv2.imshow('image', image)
cv2.waitKey(1)
time.sleep(3)
cv2.destroyAllWindows()
