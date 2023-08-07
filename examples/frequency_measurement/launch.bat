start cmd.exe /C "klnexus.exe .\config.ini"
timeout /T 2 /NOBREAK
start cmd.exe /C ".\units\meter\meter.exe"
start cmd.exe /C ".\units\signal_generator\signal_generator.exe"
start cmd.exe /C "py .\units\py_test_runner\test_runner.py"

