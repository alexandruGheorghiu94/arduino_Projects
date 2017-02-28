Anduino
========

This application allows the users of Android devices to learn about the Arduino ecosystem and how to use the core functions of the board: the use of analog & digital signals and also implementation of the most known example used on the Arduino board (Blink of an LED and the fade in & out of an LED).

##Installation
In order to get the app on your phone you have 2 option:
* Import the project into Android Studio and run it on the device you with. Note that you must have USB debugging active in the developers options tab.
* Download the project and search in its folder the "app-debug.apk" file. Transfer in onto your device and install it. Make sure to [enable loading apps from unknown sources](http://developer.android.com/distribute/open.html#unknown-sources) first.

##Additional info
This app has its whole content in french. The reason of that is because my bachelor thesis was based on this app and had to be in french for demonstration purposes.

In order for this app to fully work you require an Arduino board and a [Bluefruit LE - Bluetooth Low Energy (BLE 4.0) - nRF8001 Breakout - v1.0](https://www.adafruit.com/product/1697) connected to the board. Also you require to load a specific program onto the Arduino board that can be found into my arduino_projects repository.
For more details on how to hook up the bluetooth board to the Arduino check [here](https://learn.adafruit.com/getting-started-with-the-nrf8001-bluefruit-le-breakout/hooking-everything-up) for more details.


##GUI

At startup you enter in the welcome screen where you have only 1 option: to enter in the list containing the tutorials.

| ![](description_images/img10.png?raw=true "img1") | ![](description_images/img12.png?raw=true "img1") |
| :---: | :---: |
| Fig. 1 Intro screen | Fig. 2 List of tutorial activity |

The tutorial activity is composed of sub-menus that lead to their respective tutorial where the user can do a certain task. The **Introduction** activity represented by the __"Avant de commencer"__ sub-menu contains info about Arduino and the things required in order to use the practical part.

| ![](description_images/img2.png?raw=true "img1") | ![](description_images/img3.png?raw=true "img1") |
| :---: | :---: |
| Fig. 3 Introduction activity | Fig. 4 Connexion monitor |

All the activities that are lauched from the list menu exept the Introduction activity contain a bluetooth connexion protocol. In order to see if the bluetooth connexion is establised each activity also contains a bluetooth connexion monitor (Fig. 5) that has the role of informing the user if the Android device is connected to the Arduino board.

Make sure bluetooth is enabled, then load the BLETest application (has a generic Android icon).  Once started the app will immediately search for BTLE devices and connect to the first one it finds with the UART service.  Status messages will be displayed in a text view on the screen.  
