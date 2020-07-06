import cv2
import numpy as np

bs = cv2.createBackgroundSubtractorKNN(detectShadows=True)
camera = cv2.VideoCaptrue("/path/to/movie.flv")

while True:
    ret,frame=camera.read()
    fgmask=bs.apply(frame)
    th = cv2.threshold(fgmask.copy(),244,255,cv2.THRESH_BINARY )
    dialated = cv2.dialte(th,cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (3,3)),iterations=2)

image,contours,hier=cv2.findContours(dilated,cv2.PETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)
for c in contours:
    if cv2.contourArea(c)>1600:
        (x,y,w,h)=cv2.boundingRect(c)
        cv2.rectangle(frame,(x,y),(x+w,y+h),(255,255,0),2)

cv2.imshow("mog",fgmask)
cv2.imshow("thresh",th)
cv2.imshow("detection",frame)
if cv2.waitKey(30)&oxff==27:
    break
    camera.release()
    cv2.destroyAllWindows()
