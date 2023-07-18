# esp-idf-time-logging
Show the current date and time in the logging.   

esp-idf has a Logging library.   
The Logging library contains the "esp_log_set_vprintf" function.   
This function allows you to customize the logging display.   
By default the log shows the number of ticks since the start, but you can change it to the current date and time.   

![ScreenShot](https://github.com/nopnop2002/esp-idf-time-logging/assets/6020549/47d30fe7-b382-4fcd-9c71-62fee601557f)

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
![config-top](https://github.com/nopnop2002/esp-idf-time-logging/assets/6020549/9ee1861a-d778-446b-95d5-948b1365a1df)

This project requires a network connection and NTP Server.
![config-logging](https://github.com/nopnop2002/esp-idf-time-logging/assets/6020549/a914cf25-5519-4620-9c20-908d09624e1f)


# API   
- Enable date & time.   
 Display the date and time using the strftime function.   
 The format is the same as the strftime function.   
 Illegal formats are not considered.   
 Unfortunately the format of the strftime function does not have milliseconds.   
```
time_logging_init("%Y/%m/%d %H:%M:%S");
```

- Disable date & time.   
```
time_logging_init(NULL);
```

- Return to default.   
```
time_logging_init("");
```


