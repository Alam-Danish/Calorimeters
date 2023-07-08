# Calorimeters simulation in Geant4 framework

## Introduction
This repository contains a simulation code of a simple Calorimeter system with Electromagnetic Calometer (ECAL) and Hadronic (HCAL)Calorimeter in the [Geant4 simulation framework](https://doi.org/10.1016/S0168-9002(03)01368-8)

The main aim to simulate this detector system to see the shower developement and energy deposits for differnet type of particles such as electrons, muons, and pions.

Electomagnetic calorimeter is a homogeneous and made CsI. It is placed before the Hadronic calorimeter as the arrangements in some of the popular experiments. Hadronic calorimeter made of lead as passive absorber and divided into the cells. Then plastic scintillators are placed at the centre of these cells.

### Calorimeters response:
ECAL measures the energy deposition for the particles that interact via electromagnetic interation such as electron, positron and photons.

HCAL measure the energy deposition for the particels that interact via strong interaction such as proton, neutron, pions and kaons.

Muons are minimum ionizoing particles and lose energy only through ionization. So, they will penetrate the both the calorimeters and leave no shower.

For simplicity, I choose electrons, pions and muons as incident particles out of all. The events images for these particles are shown below.

5 GeV Electron event
![5 GeV Electron event](electron.png)

5 GeV Pion event
![5 GeV Pion event](pion.png)

5 GeV Muon event
![5 GeV Muon event](muon.png)
