<h1 align="center">Modular Integrated Network of Traffic Sensors (MINTS)</h1>
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
## About the Project
***NOTE:** This project was a part of the authors bachelor thesis at Uppsala university.* <br>
*The thesis can be found at:*

MINTS is a network of small, energy-efficient measurement stations with sensors for monitoring ground-level air quality and noise pollution at a local scale. The stations can be placed around a city, where they report data to a central gateway. From the gateway, the data takes a streamlined path to reach the public-facing website, transforming raw numbers into an intuitive, real-time heatmap.

The goal is to create a plug-and-play system that can identify problematic areas and enable the rerouting of traffic to reduce pollution and congestion in local communities. By continually monitoring several streets, it is possible to notice traffic patterns, which can be used to plan future development better and improve the quality of life in affected areas.

The primary beneficiaries of this project are the municipalities and the people, who are troubled by pollution and disturbances caused by traffic. Further, it provides the tools for responsive urbanism, making the day-to-day lives of citizens easier.

### Key Features
* **Ground-level measurements:**    measures ground level PM and noise pollution.
* **Real-Time Heatmap Generation:** Real-time visualisations of pollution data.
* **Low-Cost system:**              ~100 USD per node.
* **Low-Power LoRa Communication:** Optimized for long-range, battery-efficient data transmissions within an urban, ground-level environment.

<!-- [![Product Name Screen Shot][product-screenshot]](https://example.com) -->
### System Architecture

*For further details, please see chapter 3.3 and 3.4 in the thesis.*

#### Hardware Architecture

The measuring station is designed to be compact, energy-efficient, and easily expandable. It is powered by a 9V supply, providing a 4V overhead to handle battery degradation and protect voltage-sensitive components.

<img width="700" alt="node_circuit" src="https://github.com/user-attachments/assets/270738e1-6b0a-460a-b97a-2418bbfe84ac" />

#### Software Architecture
The software architecture consists of four parts working together: frontend,
database, gateway, and node (Figure 8). The goal is to collect data from
the connected sensors, transmit it to the gateway, which uploads it to the
database, which can be read from the frontend to update the heatmap.

<img width="400" alt="sysarc" src="https://github.com/user-attachments/assets/32bf94a7-8212-41a6-887e-9e92bd2d4194" />

### Tech Stack and Hardware Components

*For further details, please see chapter 3.2 in the thesis.*

#### Hardware
| Component | Model / Details | Purpose & Key Specifications |
| :--- | :--- | :--- |
| **Particle Sensor** | SEN-HM3301 | Monitors airborne fine particle concentrations ($PM_{1}$ and $PM_{2.5}$). |
| **Sound Sensor** | Waveshare (LM386 Amp) | Captures acoustic data (50–20,000 Hz range, 52 dB sensitivity). |
| **LoRa Module** | Core1262-HF (TCXO) | Handles wireless communication between nodes and the gateway. |
| **Microcontroller** | Arduino Nano (ESP32-S3 SoC) | Serves as the main processing board for each individual node. |
| **Gateway** | Raspberry Pi 3 Model B (1GB) | Bridges communication between the node network and the server. |
| **LoRa HAT** | Waveshare LoRa & GNSS | Gateway add-on board based on the SX1262 radio chip. |
| **Antennas** | 2J0C15-868-C885G & Bundled HAT Antenna | **Nodes:** 868MHz antenna via SMA to U.FL adapters.<br>**Gateway:** High-gain antenna bundled with the HAT. |
| **Misc. Electronics** | Capacitors, Resistors, Regulators | • 2x Electrolytic capacitors (10uF, 16V/50V)<br>• Resistors: 200Ω, 140Ω, 20Ω<br>• LD1117V33 voltage regulator (steps down to 3.3V, up to 0.95A). |
| **Power Supply** | 6x AA Batteries per node | Dual AA battery holder configuration per measurement station. |
| **Enclosure** | Custom 3D Printed Case | Custom PLA plastic chassis featuring an integrated PM10 insect/debris filter. |

#### Software & Libraries
| Tool / Library | Type | Function |
| :--- | :--- | :--- |
| **RadioLib** | Open-source Library | Provides low-level control and configuration for the SX1262 LoRa module. |
| **MapBox API** | Mapping Platform | Powering the interactive, customizable heatmap and layer handling. |
| **Firestore** | Database | Cloud-hosted NoSQL database used for storing and syncing station data. |

<!-- GETTING STARTED -->
## Getting Started
To get a local copy up and running follow these steps.

### Prerequisites

Before running the backend or frontend web application, ensure you have the following installed:
* **Node.js** (LTS version `v24.x` or higher recommended)
* **npm** (v11.x or higher)
* **TypeScript**
* **C++**

### Installation

Navigate to the part of the project you want to run and follow the specific instructions in the respective README:s.

### Repository Structure

```text
├── database/          # Firestore security rules and configurations
├── frontend/          # Web application source code and components (built with Svelte)
├── gateway/           # Packet forwarder configurations and gateway management scripts
├── node/              # Arduino/C++ firmware and PIN layouts for the LoRa sensor nodes
└── README.md          # Main project documentation and overview
```

<!-- ROADMAP -->
## Roadmap

See the [Gantt chart/roadmap](https://github.com/users/TimSchonning/projects/2) for a full view of the project development.

See also the [open issues](https://github.com/TimSchonning/MINTS/issues) for a full list of proposed features (and known issues).

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- LICENSE -->
## License

Distributed under the project_license. See `LICENSE.txt` for more information.

<!-- CONTACT -->
## Authors, Acknowledgments and Contact Information

For questions, support, or collaboration, reach out to the team:

**Filip Hellgren** <br />
Frontend and database developer <br />
Email:    filip.hellgren04@gmail.com <br />
Github:   https://github.com/Filip-Shellbranch <br />
LinkedIn: www.linkedin.com/in/filip-hellgren <br />

**Jenny Nilsson** <br />
Frontend and database developer <br />
Email:   nilssonjennylinnea@gmail.com <br />
Github:  https://github.com/jeni1263 <br />
LinkedIn: <br />

**David Olmedo** <br />
Node and gateway developer <br />
Email:    david@olmedo.se <br />
Github:   https://github.com/DaOl6717 <br />
LinkedIn: www.linkedin.com/in/davolm/ <br />

**Tim Schönning** <br />
Node and gateway developer <br />
Email:    timschonning@gmail.com <br />
Github:   https://github.com/TimSchonning <br />
LinkedIn: https://se.linkedin.com/in/tim-sch%C3%B6nning <br />

Project Link: [https://github.com/TimSchonning/MINTS](https://github.com/TimSchonning/MINTS)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- SCREENSHOTS AND DEMONSTRATIONS -->
## Screenshots & Demos

<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

* Special thanks to our thesis advisor, Docent Calkin Suero Montero.

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
