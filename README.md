# esp-idf-time-logging
Show the current date and time in the logging.   

esp-idf has a Logging library.   
You can choose from the following two logging formats.   
- Milleseconds Since Boot(Default format)   
![Image](https://github.com/user-attachments/assets/71cd9c9a-29e3-4eb6-8e9b-647653a87e60)

- System Time   
![Image](https://github.com/user-attachments/assets/e114dcb9-5a75-4eba-b60d-a2205d691f0d)

The Logging library contains the "esp_log_set_vprintf" function.   
This function allows you to customize the logging display.   
You can display the local date and time in the timestamps displayed in the logs.   
![ScreenShot](https://github.com/nopnop2002/esp-idf-time-logging/assets/6020549/47d30fe7-b382-4fcd-9c71-62fee601557f)

# Software requirements
ESP-IDF V5.0 or later.   
ESP-IDF V4.4 release branch reached EOL in July 2024.   

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


