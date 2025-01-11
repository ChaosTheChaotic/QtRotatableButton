# QtRotatableButton
A rotatable button for Qt in C+ since QPushButtons cant be rotated without some stupid trickery

#Adding
To add this to your Qt project just create new files and paste the code in. Then go to your CMakeLists.txt and add the files to qt_add_executable. I have no idea how to do this for qmake as I have only very recently started using qt.

#Usage
Just add the button like you would add a QPushButton and use it like one. To rotate it, make use of QPropertyAnimation.

#Simple snippet
```cpp
auto* rotationAnim = new QPropertyAnimation(button, "rotation");
rotationAnim->setDuration(200);
rotationAnim->setStartValue(0);
rotationAnim->setEndValue(45);
rotationAnim->start(QAbstractAnimation::DeleteWhenStopped);
```
