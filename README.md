# esp-idf-time-logging
Show the current date and time in the logging.   

esp-idf has a Logging library.   
The Logging library contains the "esp_log_set_vprintf" function.   
This function allows you to customize the logging display.   
By default the log shows the tick count, but you can change it to the current date and time.   

![ScreenShot](https://github.com/nopnop2002/esp-idf-time-logging/assets/6020549/9af8a4d1-b987-4b51-9655-fd8c8c2cc29b)

# Software requirements
esp-idf v4.4/v5.x.   


# Installation
```Shell
git clone https://github.com/nopnop2002/esp-idf-time-logging
cd esp-idf-time-logging
idf.py menuconfig
idf.py flash
```

# Configuration   
![config-top](https://github.com/nopnop2002/esp-idf-time-logging/assets/6020549/64fe4ac1-862d-4b90-8a19-9a911a05b201)

## Configuration for Network
This project requires a network connection.
![config-network](https://github.com/nopnop2002/esp-idf-time-logging/assets/6020549/b8ddeb00-b554-467b-b3de-f3aec63d16c1)

## Configuration for NTP Server
This project requires a NTP Server.
![config-ntp](https://github.com/nopnop2002/esp-idf-time-logging/assets/6020549/21a953af-6555-405d-8944-893cf5d28b3c)

# API   
- Enable logging with current date & time.   
 The format is the same as the strftime function.   
 Formatting errors are not taken into account.   
 Unfortunately the format of the strftime function does not have milliseconds.   
```
time_logging_init("%Y/%m/%d %H:%M:%S");
```

- Disable logging with current date & time.   
 Return to tick display.   
```
time_logging_init("");
```
