set(component_srcs "time_logging.c")

idf_component_register(SRCS "${component_srcs}"
                       INCLUDE_DIRS ".")
