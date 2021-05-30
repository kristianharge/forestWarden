# forestWarden

This document contains the useful information to add our AI in your QuickFeather devboard.

## Requirements

- You should have a 64 bit Windows PC with windows 10 embedded.
- Follow the instructions in the **Getting started on Quickfeather board** and **Pre-requisites** instructions that can be found in the next link : https://github.com/QuickLogic-Corp/qorc-sdk.
- Open a bash or command prompt terminal in the cloned directory.
- Go to the next directory : qf_apps . Clone our repository in there by opening the comand prompt and executing : 

```bash
cd qf_apps
git clone https://github.com/kristianharge/forestWarden.git
```

## Build

- Enter the forestWarden directory, go to the GCC_Project and build the executable :

```bash
cd forestWarden/GCC_Project
make
```

- Now, the executable is in the output files. We will copy it in the TinyFPGA-Programmer-Application :

```bash
cp ./output/bin/qf_ssi_ai_app.bin ../../../TinyFPGA-Programmer-Application/
```

## Upload

- Connect the Quickfeather devboard to your computer and push the reset button followed by the user button (for more precise information see the **Program** section at : 
https://github.com/QuickLogic-Corp/TinyFPGA-Programmer-Application/tree/29f3da80d38bf928548ee31897faf924bf30f009)
- Go to the TinyFPGA-Programmer-Application directory and execute the following commands :
```bash
python tinyfpga-programmer-gui.py --port COMX --mode m4 --m4app ./qf_ssi_ai_app.bin
```

Now, the code is embedded in your Quickfeather, enjoy!!
