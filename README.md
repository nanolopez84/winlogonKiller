# winlogonKiller
As part of a Cybersecurity R+D project we needed to test different Credential Providers and Security Packages for wanted or unwanted online updates, so I came up with this simple yet efficient idea of forcing a login while loading the new configuration by killing `winlogon.exe`.
This way we avoided the need to restart the OS each time we changed the configuration, hence our workflow became way faster.

## Procedure
* After building the solution, set permissions on `winlogonKiller.exe` like in "Set permissions.png".
* By executing `winlogonKiller.exe`, the login prompt will appear immediately