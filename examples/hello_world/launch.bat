start cmd.exe /C "klnexus.exe .\config.ini"
timeout /T 2 /NOBREAK
start cmd.exe /C ".\units\a\a.exe"
start cmd.exe /C ".\units\b\b.exe"

