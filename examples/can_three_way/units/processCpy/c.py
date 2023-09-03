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

def send(can_adapter, id_, data):
    hex_values_formatted = [f"{value:02X}" for value in data]
    print("-> "+f"{id_:02X}"+" "+str(hex_values_formatted))
    can_adapter.send(id_, data)

def receive(can_adapter):
    while can_adapter.frames_available():
        msg = can_adapter.receive()
        hex_values_formatted = [f"{value:02X}" for value in msg.data]
        print("<- "+f"{msg.id:02X}"+" "+str(hex_values_formatted))
    
def step(unit, t, can_adapter, id_, data):
    unit.sync(t)
    print("t = "+f"{t:.7f}")
    send(can_adapter, id_, data)
    receive(can_adapter)
    

def run():
    shared_header_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..\\..\\shared\\nexus_shared_data.h")
    unit = Unit(shared_header_path=shared_header_path,
                 slot=2,
                 dll_path=None)
    
    can_adapter = CanAdapter(unit, "can2")
    can_adapter.can_init()
    can_adapter.connect("bus0")
    
    id_ = 0x99
    
    step(unit, 0.0, can_adapter,  id_,  [1 , 2, 3, 4, 5, 6, 7, 8])
    step(unit, 1e-3, can_adapter, id_,  [2 , 2, 3, 4, 5, 6, 7, 8])
    step(unit, 2e-3, can_adapter, id_,  [3 , 2, 3, 4, 5, 6, 7, 8])
    step(unit, 3e-3, can_adapter, id_,  [4 , 2, 3, 4, 5, 6, 7, 8])
    step(unit, 4e-3, can_adapter, id_,  [5 , 2, 3, 4, 5, 6, 7, 8])
    step(unit, 5e-3, can_adapter, id_,  [6 , 2, 3, 4, 5, 6, 7, 8])
    step(unit, 6e-3, can_adapter, id_,  [7 , 2, 3, 4, 5, 6, 7, 8])
    step(unit, 7e-3, can_adapter, id_,  [8 , 2, 3, 4, 5, 6, 7, 8])
    step(unit, 8e-3, can_adapter, id_,  [9 , 2, 3, 4, 5, 6, 7, 8])
    step(unit, 9e-3, can_adapter, id_,  [10, 2, 3, 4, 5, 6, 7, 8])
    step(unit, 10.0, can_adapter, id_,  [11, 2, 3, 4, 5, 6, 7, 8])
    
    print("Simulation finished.")
    
        

if __name__ == "__main__":
    run()
