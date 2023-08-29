start cmd.exe /C "klnexus.exe .\config.ini"
timeout /T 2 /NOBREAK
start cmd.exe /C ".\units\processA\app.exe"
start cmd.exe /C ".\units\processB\app.exe"
start cmd.exe /C "py .\units\processCpy\test_runner.py"