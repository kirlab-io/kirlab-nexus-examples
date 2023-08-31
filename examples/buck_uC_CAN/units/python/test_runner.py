"""
Copyright (C) 2023 Kirlab
All rights reserved.

This file is part of KirLab Nexus.

This file is distributed under the terms of KirLab Nexus license.
Please see the EULA.txt file for the full license text.
"""


#Remove this block once it is working
try:
    from KirLabNexus import Unit
    from KirLabNexus import CanAdapter
except ImportError:
    print("KirLabNexus module not found. To install it:")
    color_green = "\033[92m"
    color_default = "\033[0m"
    print(color_green+"your/python.exe -m pip install %KLNEXUS_PATH%/python/kirlabnexus-base/"+color_default)
    exit(1)

import os   

def test():
    shared_header_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..\\..\\shared\\nexus_shared_data.h")
    unit = Unit(shared_header_path=shared_header_path,
                 slot=2,
                 dll_path=None)
    
    t = 0.0
    can_adapter = CanAdapter(unit, "can1")
    can_adapter.can_init()
    can_adapter.connect("bus0")
    print (can_adapter.receive())
    
    id_to_send = 0x99
    data_to_send = [0, 0, 0, 0, 1, 0, 0, 0]
    
    for i in range(5):
        t+= 10e-3
        data_to_send[4] = data_to_send[4]+1
        hex_values_formatted = [f"{value:02X}" for value in data_to_send]
        print("-> "+f"{id_to_send:02X}"+" "+str(hex_values_formatted))
        can_adapter.send(id_to_send, data_to_send)
        
        unit.sync(t)
        print("t = "+f"{t:.7f}")
        
        while True:
            received, id, data = can_adapter.receive()
            if not received:
                break
            hex_values_formatted = [f"{value:02X}" for value in data]
            print("<- "+f"{id:02X}"+" "+str(hex_values_formatted))
        
    
    t = 1
    unit.sync(t)
    input("Press enter to finish...")
    
        

if __name__ == "__main__":
    test()
