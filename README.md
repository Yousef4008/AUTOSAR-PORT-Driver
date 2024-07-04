# Autosar Full Layered Architecture Project for TivaC

## Introduction
This project implements the AUTOSAR (AUTomotive Open System ARchitecture) Full Layered Architecture (FLA) on the TivaC TM4C123GXL microcontroller platform. AUTOSAR FLA provides a standardized software architecture for automotive embedded systems, enabling modularity, scalability, and reusability.

## Project Overview
The project follows the AUTOSAR FLA structure, consisting of several layers and modules that collectively manage the vehicle's functions and applications.

### Layers Implemented
1. **Application Layer:** Contains application-specific software components.
2. **RTE (Run-Time Environment) Layer:** Manages communication between the application software components and the Basic Software (BSW) modules.
3. **BSW (Basic Software) Layer:** Provides standardized services, such as communication, diagnostics, and operating system abstraction.
4. **MCAL (Microcontroller Abstraction Layer):** Abstracts hardware-specific details and provides standardized interfaces for the TivaC microcontroller peripherals.

