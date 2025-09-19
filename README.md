# HVeV simulation

This is a HVeV-like detector simulation package.

## Detector configuration
The silicon substrate is $10 cm\times10 cm \times4 cm$, which is assigned as the "sensitive detector".

Al films cover both the top and bottom surfaces of the Si substrate.

The surfaces between Si and Al are attached with phonon electrodes, where phonon gets probability to be absorbed and depost energy.


## Physics List
- G4CMPPhysics
- FEFT_BERT 
- EmStandardPhysics


## Generators
General Particle Source (GPS) is used as the primary generator. To simulate the electron capture process of $^7$Be, the G4RadioDecay class is invoked.
