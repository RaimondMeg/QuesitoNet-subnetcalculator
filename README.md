# QuesitoNet-subnetcalculator
Subnet calculator with qmake in c++


# Subnet Calculator in C++

This repository contains a **Subnet Calculator** implemented in C++ with a graphical user interface (GUI) built using the `Qt` framework and `qmake`. The application helps users perform subnetting operations by calculating subnet addresses, subnet masks, IP ranges, and more. It's designed to simplify the process of subnetting and provide quick and accurate results for networking tasks.

## Features

- **Subnet Calculation**: Automatically calculates the subnet mask, network address, broadcast address, and usable IP ranges.
- **GUI Interface**: Intuitive and user-friendly interface built with `Qt`, making it easy to input data and view results.
- **Support for Variable-Length Subnet Masks (VLSM)**: Allows users to calculate subnetting for networks of different sizes.
- **Live Calculation**: As users input information, the application dynamically displays results such as network address, first and last usable IP, and the broadcast address.

## How to Use

1. Open the application and input an IP address along with the subnet quantity required or the CIRD /XX 
2. The tool will automatically calculate the subnet details, including:
   - Network address
   - Broadcast address
   - First and last usable IP addresses in the subnet
3. The results are displayed in the GUI for easy reference and understanding.

