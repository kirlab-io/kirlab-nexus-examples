"""
Copyright (C) 2024 Kirlab
All rights reserved.

This file is part of KirLab Nexus.

This file is distributed under the terms of KirLab Nexus license.
Please see the EULA.txt file for the full license text.
"""


#Remove this block once it is working
try:
    from KirLabNexus import Unit
except ImportError:
    print("KirLabNexus module not found. To install it:")
    color_green = "\033[92m"
    color_default = "\033[0m"
    print(color_green+"your/python.exe -m pip install %KLNEXUS_PATH%/python/kirlabnexus-base/"+color_default)
    exit(1)

import os   

def read_print(unit, name):
    print(name+"="+str(unit.read(name)))

def report_status(unit, signal_list, t):
    print("*"*30)
    print("Status (t="+str(t)+")")
    for signal in signal_list:
        read_print(unit, signal)
    print("*"*30)
    print("")

def test_case():
    shared_header_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..\\..\\shared\\nexus_shared_data.h")
    unit = Unit(shared_header_path=shared_header_path,
                 slot=2,
                 dll_path=None)
            
    
    signals_to_report = ["measured_frequency", \
                         "measured_amplitude", \
                         "requested_frequency",\
                         "requested_amplitude"]
    
    print("Request 2kHz and 120\n")
    unit.write("requested_frequency", 2e3)
    unit.write("requested_amplitude", 120*(2**0.5))
    
    #Sync at 1ms
    t = 1e-3
    unit.sync(t)
    
    #Print status
    report_status(unit, signals_to_report, t)
    
    #Sync at 10ms
    t = 10e-3
    unit.sync(t)
    
    #Print status
    report_status(unit, signals_to_report, t)
    
    #Change requested frequency and amplitude
    print("Request 1kHz and 230\n")
    unit.write("requested_frequency", 1e3)
    unit.write("requested_amplitude", 230*(2**0.5))
    
    #Sync at 11ms
    t = 11e-3
    unit.sync(t)
    
    #Print status
    report_status(unit, signals_to_report, t)
    
    #Sync at 20ms
    t = 20e-3
    unit.sync(t)
    
    #Print status
    report_status(unit, signals_to_report, t)
    
    #Sync till end
    t = 1
    unit.sync(t)
    print("Simulation finished.")
    
    

if __name__ == "__main__":
    test_case()
