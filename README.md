<h1 align="center">Mesh-Integrated Network of Traffic Sensors (MINTS)</h1>

<a id="readme-top"></a>

<!-- PROJECT SHIELDS -->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

MINTS is a network of small, energy-efficient measurement stations with sensors for monitoring air quality and noise pollution at a local scale. The stations can be placed around a city, where they report data to a central hub. The hub can, in turn, generate real-time heatmaps and visualizations, converting data into insights.

The goal is to create a plug-and-play system that can identify problematic areas and enable the rerouting of traffic to reduce pollution and congestion in local communities. By continually monitoring several streets, it is possible to notice traffic patterns, which can be used to plan future development better and improve the quality of life in affected areas. Moreover, ongoing construction work, such as the tram in Uppsala, causes traffic disruptions. The MINTS system will give authorities the means to track these traffic jams.

The primary beneficiaries of this project are the municipalities and the people, who are troubled by pollution and disturbances caused by traffic. Further, it provides the tools for responsive urbanism, making the day-to-day lives of citizens easier.


<!-- [![Product Name Screen Shot][product-screenshot]](https://example.com) -->

### Built With

### Hardware used

// temp <br />
    https://www.electrokit.com/optisk-damm-partikelsensor-2.5/5/10-um-hm3301 <br />
    https://www.electrokit.com/en/sound-detector <br />
    https://www.electrokit.com/en/arduino-nano-esp32-with-headers <br />
    https://www.electrokit.com/en/lora-modul-868mhz-core1262-hf <br />

<!-- GETTING STARTED -->
## Getting Started
To get a local copy up and running follow these steps.

### Prerequisites

To run the project you need to have npm, NodeJS and TypeScript installed. Below is an example of how to set them up in Ubuntu using Windows Subsystem for Linux (WSL) if they are not yet installed.

### Step 1
Install Node Version Manager (nvm) using the following command.
```
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/master/install.sh | bash
```

Restart your terminal and then verify installation by typing:
```
nvm -v
```

### Step 2
Use nvm to install npm and NodeJS LTS by using the following command. At the time of writing the version of node is "v24.14.1" and npm is version "11.11.0".

```
nvm install --lts
```

### Step 3
Install TypeScript using npm by using the command:
```
npm install -g typescript
```

Verify by typing 
´´´
tsc --v
´´´


### Installation

Navigate to the part of the project you want to run and follow the specific instructions in the respective README:s.

<!-- USAGE EXAMPLES -->
## Usage

<!-- ROADMAP -->
## Roadmap

See the [Gantt chart/roadmap](https://github.com/users/TimSchonning/projects/2) for a full view of the project development.

See also the [open issues](https://github.com/TimSchonning/MINTS/issues) for a full list of proposed features (and known issues).

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- LICENSE -->
## License

Distributed under the project_license. See `LICENSE.txt` for more information.

<!-- CONTACT -->
## Contact
For questions, support, or collaboration, reach out to the team:

**Filip Hellgren**  
Email:    filip.hellgren04@gmail.com <br />
Github:   https://github.com/Filip-Shellbranch <br />
LinkedIn: www.linkedin.com/in/filip-hellgren <br />

**Jenny Nilsson**  
Email:    nilssonjennylinnea@gmail.com <br />
Github:  https://github.com/jeni1263 <br />
LinkedIn: <br />

**David Olmedo**  
Email:    david@olmedo.se <br />
Github:   https://github.com/DaOl6717 <br />
LinkedIn: www.linkedin.com/in/davolm/ <br />

**Tim Schönning**  
Email:    timschonning@gmail.com <br />
Github:   https://github.com/TimSchonning <br />
LinkedIn: https://se.linkedin.com/in/tim-sch%C3%B6nning <br />

Project Link: [https://github.com/TimSchonning/MINTS](https://github.com/TimSchonning/MINTS)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

* []()
* []()
* []()

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/TimSchonning/MINTS.svg?style=for-the-badge
[contributors-url]: https://github.com/TimSchonning/MINTS/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/TimSchonning/MINTS.svg?style=for-the-badge
[forks-url]: https://github.com/TimSchonning/MINTS/network/members
[stars-shield]: https://img.shields.io/github/stars/TimSchonning/MINTS.svg?style=for-the-badge
[stars-url]: https://github.com/TimSchonning/MINTS/stargazers
[issues-shield]: https://img.shields.io/github/issues/TimSchonning/MINTS.svg?style=for-the-badge
[issues-url]: https://github.com/TimSchonning/MINTS/issues
[license-shield]: https://img.shields.io/github/license/TimSchonning/MINTS.svg?style=for-the-badge
[license-url]: https://github.com/TimSchonning/MINTS/blob/main/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/linkedin_username
[product-screenshot]: images/screenshot.png
<!-- Shields.io badges. You can a comprehensive list with many more badges at: https://github.com/inttter/md-badges -->
[Next.js]: https://img.shields.io/badge/next.js-000000?style=for-the-badge&logo=nextdotjs&logoColor=white
[Next-url]: https://nextjs.org/
[React.js]: https://img.shields.io/badge/React-20232A?style=for-the-badge&logo=react&logoColor=61DAFB
[React-url]: https://reactjs.org/
[Vue.js]: https://img.shields.io/badge/Vue.js-35495E?style=for-the-badge&logo=vuedotjs&logoColor=4FC08D
[Vue-url]: https://vuejs.org/
[Angular.io]: https://img.shields.io/badge/Angular-DD0031?style=for-the-badge&logo=angular&logoColor=white
[Angular-url]: https://angular.io/
[Svelte.dev]: https://img.shields.io/badge/Svelte-4A4A55?style=for-the-badge&logo=svelte&logoColor=FF3E00
[Svelte-url]: https://svelte.dev/
[Laravel.com]: https://img.shields.io/badge/Laravel-FF2D20?style=for-the-badge&logo=laravel&logoColor=white
[Laravel-url]: https://laravel.com
[Bootstrap.com]: https://img.shields.io/badge/Bootstrap-563D7C?style=for-the-badge&logo=bootstrap&logoColor=white
[Bootstrap-url]: https://getbootstrap.com
[JQuery.com]: https://img.shields.io/badge/jQuery-0769AD?style=for-the-badge&logo=jquery&logoColor=white
[JQuery-url]: https://jquery.com 
