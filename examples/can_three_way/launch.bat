start cmd.exe /C "klnexus.exe .\config.ini"
timeout /T 2 /NOBREAK
start cmd.exe /C ".\units\processA\a.exe"
start cmd.exe /C ".\units\processB\b.exe"
start cmd.exe /C "py .\units\processCpy\c.py"