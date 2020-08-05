
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![LinkedIn][linkedin-shield]][linkedin-url]



<!-- PROJECT LOGO -->
<br />
<p align="center">
  <a href="https://github.com/haitham-chabayta/blind-spot-detection">
     <img src="images/logo.png" alt="Logo" width="80" height="80">
 </a>

  <h3 align="center">Blind spot object detection system</h3>

  <p align="center">
    A system that detects objects in the driver's blind spot and alerts the user of the threat through an ionic application.
    <br />
    <a href="https://github.com/haitham-chabayta/blind-spot-detection"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/haitham-chabayta/blind-spot-detection/demo-videos">View Demo</a>
    ·
    <a href="https://github.com/haitham-chabayta/blind-spot-detection/issues">Report Bug</a>
    ·
    <a href="https://github.com/haitham-chabayta/blind-spot-detection/issues">Request Feature</a>
  </p>
</p>



<!-- TABLE OF CONTENTS -->
## Table of Contents

* [About the Project](#about-the-project)
  * [Built With](#built-with)
  * [Features](#features)
* [Getting Started](#getting-started)
  * [Prerequisites](#prerequisites)
  * [Installation](#installation)
* [Contributing](#contributing)
* [Contact](#contact)
* [Acknowledgements](#acknowledgements)



<!-- ABOUT THE PROJECT -->
## About The Project

[![Screen Shot][product-screenshot]](https://github.com/haitham-chabayta/blind-spot-detection/)

Blind spot detection is an cross-platform ionic application that alerts users for a threat in his blind spot while driving if detected. The application gathers data from the database to know if there is an object in the blind spot. The info in the database is constantly updated by an arduino that has an ultrasonic connected to it to detect objects. When an object is detected the application alerts the user of the threat visually and by producing an alarming sound.

A list of commonly used resources that I find helpful are listed in the acknowledgements.

### Features
* Mute button for the alert sound
* Visual representation to threats in blind spots
* Ability to turn off detection when moving below a certain speed.


### Built With
* [Arduino IDE](https://www.arduino.cc/en/main/software)
* [Ionic framework](https://ionicframework.com/)

## Getting Started


### Prerequisites

*3 Arduino microcontroller 

*2 Ultrasonic sensors

*Arduino IDE / Download from : https://www.arduino.cc/en/main/software

*Git / Check if you have Git using:
```sh
npm --version
```
If not install git from https://git-scm.com/downloads

*Andriod studio and Java JDK 8 if you have an android device

*Xcode 7 or higher and IOS 9 if you have an IOS device



### Installation

1. Clone the Repo 
```sh
git clone https://github.com/haitham-chabayta/blind-spot-detection.git
```
2. Import the ardunio codes from the repo into arduino IDE and install the codes on the arduinos

3. Connect the ultrasonic sensors to the arduinos as suitable

4. Install the ionic app on your phone following the guide at: https://ionicframework.com/docs/v3/intro/deploying/


<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request


<!-- CONTACT -->
## Contact

Haitham Chabayta - haithamchabayta@gmail.com

LinkedIn: https://www.linkedin.com/in/haitham-chabayta-0654681b1/



<!-- ACKNOWLEDGEMENTS -->
## Acknowledgements
* [GitHub Emoji Cheat Sheet](https://www.webpagefx.com/tools/emoji-cheat-sheet)
* [GitHub Pages](https://pages.github.com)
* [Firebase](https://firebase.google.com/)
* [Ionic documentation](https://ionicframework.com/docs)
* [Arduino WIFI library](https://www.arduino.cc/en/Reference/WiFi)



[contributors-shield]: https://img.shields.io/github/contributors/haitham-chabayta/blind-spot-detection.svg?style=flat-square
[contributors-url]: https://github.com/haitham-chabayta/blind-spot-detection/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/haitham-chabayta/blind-spot-detection.svg?style=flat-square
[forks-url]: https://github.com/haitham-chabayta/blind-spot-detection/network/members
[stars-shield]: https://img.shields.io/github/stars/haitham-chabayta/blind-spot-detection.svg?style=flat-square
[stars-url]: https://github.com/haitham-chabayta/blind-spot-detection/stargazers
[issues-shield]: https://img.shields.io/github/issues/haitham-chabayta/blind-spot-detection.svg?style=flat-square
[issues-url]: https://github.com/haitham-chabayta/blind-spot-detection/issues
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=flat-square&logo=linkedin&colorB=555
[linkedin-url]: https://www.linkedin.com/in/haitham-chabayta-0654681b1/
[product-screenshot]: images/screenshot.png
