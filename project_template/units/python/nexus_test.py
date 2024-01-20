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


def test_case():
    unit = Unit(shared_header_path="..\\..\\shared\\nexus_shared_data.h",
                 slot=0,
                 dll_path=None)         
    
    # Test the sync function to 1ms
    sync_result = unit.sync(0.001)
    print("Sync result:", sync_result)

    #Write 
    unit.write("b.signal_0", 100e3)
    
    #Read
    read_result = unit.read("a.signal_0")
    print("Read after write result:", read_result)

    

if __name__ == "__main__":
    test_case()
